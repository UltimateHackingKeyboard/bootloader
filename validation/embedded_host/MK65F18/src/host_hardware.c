/*
 * Copyright (c) 2013 - 2014, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "host_hardware.h"
#include "fsl_device_registers.h"
#include "port/fsl_port.h"
#include "flexcan/fsl_flexcan.h"
#include "dspi/fsl_dspi.h"
#include "uart/fsl_uart.h"
#include "i2c/fsl_i2c.h"
#include "utilities/fsl_rtos_abstraction.h"

#include "pin_mux.h"
#include "board.h"
#include "disk.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#define k_uartBufferSize 256
#define HOST_UART_INSTANCE 2

/*!
 * @brief Internal driver state information.
 *
 * @note The contents of this structure are internal to the driver and should not be
 *      modified by users. Also, contents of the structure are subject to change in
 *      future releases.
 */
typedef struct FlexCANState
{
    volatile uint32_t rx_mb_idx; /*!< Index of the message buffer for receiving*/
    volatile uint32_t tx_mb_idx; /*!< Index of the message buffer for transmitting*/
    semaphore_t txIrqSync;       /*!< Used to wait for ISR to complete its TX business.*/
    semaphore_t rxIrqSync;       /*!< Used to wait for ISR to complete its RX business.*/
} flexcan_state_t;

/*! @brief FlexCAN data info from user*/
typedef struct FlexCANDataInfo
{
    flexcan_frame_format_t msg_id_type; /*!< Type of message ID (standard or extended)*/
    uint32_t data_length;               /*!< Length of Data in Bytes*/
} flexcan_data_info_t;

/*! @brief FlexCAN operation modes*/
typedef enum _flexcan_operation_modes
{
    kFlexCanNormalMode,     /*!< Normal mode or user mode*/
    kFlexCanListenOnlyMode, /*!< Listen-only mode*/
    kFlexCanLoopBackMode,   /*!< Loop-back mode*/
    kFlexCanFreezeMode,     /*!< Freeze mode*/
    kFlexCanDisableMode,    /*!< Module disable mode*/
} flexcan_operation_modes_t;

/*!
 * @brief flexCAN common information structure
 */
typedef struct _flexcan_transfer_info
{
    flexcan_state_t state;       //!< state
    flexcan_data_info_t rx_info; //!< tx info
    flexcan_data_info_t tx_info; //!< tx info
    uint32_t rxId;               //!< rx id
    uint32_t txId;               //!< tx id
    uint32_t rx_mailbox_num;     //!< rx mb number
    uint32_t tx_mailbox_num;     //!< tx mb number
    uint8_t rx_buf[64];          //!< rx buffer
    uint8_t rx_buf_write_index;  //!< rx buffer write index
    uint8_t rx_buf_read_index;   //!< rx buffer read index
} flexcan_transfer_info_t;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*!
 * @brief uart byte receive callback.
 */
static void s_uart_byte_receive_callback(uint8_t byte);

/*!
 * @brief I2C transfer callback.
 */
static void i2c_master_callback(I2C_Type *base, i2c_master_handle_t *handle, status_t status, void *userData);

/*!
 * @brief Return specified UART clock, LPUART0 is not supported here.
 */
static uint32_t get_uart_clock(uint32_t instance);

/*! @brief init uart functions. */
static void init_suarts(void);

/*! @brief dspi initialization. */
static void init_dspi(void);

/*! @brief i2c initialization. */
static void init_i2c(uint32_t instance);

/*! @brief flexcan initialization. */
static void init_flexcan(void);

static void read_can_data(uint8_t data, uint32_t instance);

static status_t FLEXCAN_Send(uint8_t instance,
                             uint32_t mb_idx,
                             flexcan_data_info_t *tx_info,
                             uint32_t msg_id,
                             uint8_t *mb_data,
                             uint32_t timeout_ms);

//! @brief flexCAN reset buffer process
static void reset_can_buffer(void);
/*******************************************************************************
 * Variables
 ******************************************************************************/

/*! @brief Variable for DSPI setup information */
static dspi_master_config_t g_dspiConfig;
static dspi_transfer_t g_dspi_masterXfer;
const static uint32_t g_dspiBaseAddr[] = SPI_BASE_ADDRS;
dspi_master_handle_t g_dspi_masterHandle;

/*! @brief Variable for I2C setup information */
static i2c_master_config_t s_i2cMasterConfig;
static i2c_master_transfer_t s_i2c_masterXfer;
const static uint32_t g_i2cBaseAddr[] = I2C_BASE_ADDRS;
i2c_master_handle_t g_i2c_masterHandle = { 0 };
volatile bool g_I2C_MasterCompletionFlag = false;

/* Uart1 */
static uint8_t *s_uart_rxData;
static uint32_t s_uart_bytesRx;
/* Uart1 buffer */
static uint8_t s_uartBuffer[k_uartBufferSize];
static uint8_t *s_uartPtr = s_uartBuffer;
static uint32_t s_uartBufferOffset = 0;

/* Array of UART peripheral base address. */
static UART_Type *const s_uartBase[] = UART_BASE_PTRS;
/* Array of UART IRQ number. */
static const IRQn_Type s_uartIRQ[] = UART_RX_TX_IRQS;

/* FlexCan */
const static uint32_t g_flexcanBaseAddr[] = CAN_BASE_ADDRS;

/* Tables to save CAN IRQ enum numbers defined in CMSIS header file. */
const IRQn_Type g_flexcanRxWarningIrqId[] = CAN_Rx_Warning_IRQS;
const IRQn_Type g_flexcanTxWarningIrqId[] = CAN_Tx_Warning_IRQS;
const IRQn_Type g_flexcanWakeUpIrqId[] = CAN_Wake_Up_IRQS;
const IRQn_Type g_flexcanErrorIrqId[] = CAN_Error_IRQS;
const IRQn_Type g_flexcanBusOffIrqId[] = CAN_Bus_Off_IRQS;
const IRQn_Type g_flexcanOredMessageBufferIrqId[] = CAN_ORed_Message_buffer_IRQS;

/*!
 * @brief flexCAN timing table (120Mhz)contains propseg, pseg1, pseg2, pre_divider, rjw
 */
flexcan_timing_config_t bit_rate_table[] = {
    { 47, 1, 3, 2, 1 }, /* 125 kHz */
    { 23, 1, 3, 2, 1 }, /* 250 kHz */
    { 11, 1, 3, 2, 1 }, /* 500 kHz */
    { 7, 1, 3, 2, 1 },  /* 750 kHz */
    { 5, 1, 3, 2, 1 },  /* 1   MHz */
};

/*!
 * @brief flexCAN instance used for bus pal
 */
uint8_t flexcanInstance = 0;

//! @brief Global state for the FlexCAN peripheral interface.
flexcan_transfer_info_t s_flexcanInfo;
/*******************************************************************************
 * Code
 ******************************************************************************/

void hardware_init(void)
{
    uint32_t count = 0;
    uint32_t regPrimask = 0U;

    /* Disable the MPU otherwise USB cannot access the bus */
    MPU->CESR = 0;

    BOARD_InitPins();
    BOARD_InitLED();
    BOARD_InitSwitch();

    microseconds_init();
    init_suarts();
    init_dspi();
    init_flexcan();
    init_i2c(I2C_INSTANCE);

    /* Wait to hardware stable */
    microseconds_delay(500000);
    microseconds_shutdown();

    for (uint32_t i = 0; i < 100; i++)
    {
        if (BOARD_ReadSwitch(kSwitch3))
        {
            count++;
        }
    }
    if (count > 60)
    {
        disk_init();
        FLASH_Init(&s_flashInstance);

        /* Disable IRQ, protect ring buffer. */
        regPrimask = __get_PRIMASK();
        __disable_irq();

        /* 1M flash region to store flash image */
        FLASH_Erase(&s_flashInstance, MSD_FLASH_BASE, 1024 * 1024, kFLASH_ApiEraseKey);

        /* Recover PRIMASK, enable IRQ if previously enabled. */
        __set_PRIMASK(regPrimask);
    }

    PORT_SetPinInterruptConfig(BOARD_SW2_PORT, BOARD_SW2_GPIO_PIN, kPORT_InterruptFallingEdge);
    EnableIRQ(BOARD_SW2_IRQ);
    PORT_SetPinInterruptConfig(BOARD_SW3_PORT, BOARD_SW3_GPIO_PIN, kPORT_InterruptFallingEdge);
    EnableIRQ(BOARD_SW3_IRQ);
}

uint32_t get_bus_clock(void)
{
    uint32_t busClockDivider = ((SIM->CLKDIV1 & SIM_CLKDIV1_OUTDIV2_MASK) >> SIM_CLKDIV1_OUTDIV2_SHIFT) + 1;
    return (SystemCoreClock / busClockDivider);
}

uint32_t get_fast_peripheral_clock(void)
{
    uint32_t busClockDivider = ((SIM->CLKDIV1 & SIM_CLKDIV1_OUTDIV2_MASK) >> SIM_CLKDIV1_OUTDIV2_SHIFT) + 1;
    return (SystemCoreClock / busClockDivider);
}

bool usb_clock_init(void)
{
    SIM->CLKDIV2 = (uint32_t)0x0UL; /* Update USB clock prescalers */
                                    /* Select MCGPLLCLK clock */
    SIM->SOPT2 &= ~SIM_SOPT2_PLLFLLSEL_MASK;
    SIM->SOPT2 |= (SIM_SOPT2_USBSRC_MASK | SIM_SOPT2_PLLFLLSEL(0x01U));
    SIM->CLKDIV2 = (uint32_t)0x09UL; /* Update USB clock prescalers */
    /* Enable USB-OTG IP clocking */
    SIM->SCGC4 |= (SIM_SCGC4_USBOTG_MASK);

    /* Configure enable USB regulator for device */
    SIM->SOPT1 |= SIM_SOPT1_USBREGEN_MASK;
    /* SIM_SOPT1: OSC32KSEL=0 */
    SIM->SOPT1 &=
        (uint32_t)~SIM_SOPT1_OSC32KSEL_MASK; /* System oscillator drives 32 kHz clock for various peripherals */

    return true;
}

static void init_suarts(void)
{
    /* UART2 for OpenSDA and UART4 for Kibble */
    uart_config_t config;

    UART_GetDefaultConfig(&config);
    config.baudRate_Bps = kUART_DEFAULT_BAUD;
    config.enableTx = true;
    config.enableRx = true;

    UART_Init(s_uartBase[HOST_UART_INSTANCE], &config, get_uart_clock(HOST_UART_INSTANCE));

    EnableIRQ(s_uartIRQ[UART_INSTANCE]);
    UART_Init(s_uartBase[UART_INSTANCE], &config, get_uart_clock(UART_INSTANCE));
    UART_EnableInterrupts(s_uartBase[UART_INSTANCE], kUART_RxDataRegFullInterruptEnable);
}

static uint32_t get_uart_clock(uint32_t instance)
{
    switch (instance)
    {
        case 0:
        case 1:
            /* UART0 and UART1 always use the system clock */
            return SystemCoreClock;
        case 2:
            return get_bus_clock();
        case 3:
        case 4:
            /* UART2-4 always use the bus clock. */
            return get_bus_clock();
        default:
            return 0;
    }
}

static void init_dspi(void)
{
    uint32_t baseAddr = g_dspiBaseAddr[SPI_INSTANCE];

    DSPI_MasterGetDefaultConfig(&g_dspiConfig);
    g_dspiConfig.whichCtar = kDSPI_Ctar1;
    g_dspiConfig.ctarConfig.cpol = kDSPI_ClockPolarityActiveLow;
    g_dspiConfig.ctarConfig.cpha = kDSPI_ClockPhaseSecondEdge;
    g_dspiConfig.ctarConfig.baudRate = 100000U;

    DSPI_MasterInit((SPI_Type *)baseAddr, &g_dspiConfig, get_bus_clock());

    g_dspi_masterXfer.configFlags = kDSPI_MasterCtar1 | kDSPI_MasterPcs0 | kDSPI_MasterPcsContinuous;
}

static void init_i2c(uint32_t instance)
{
    I2C_MasterGetDefaultConfig(&s_i2cMasterConfig);

    I2C_MasterInit((I2C_Type *)g_i2cBaseAddr[instance], &s_i2cMasterConfig, get_bus_clock());
    I2C_MasterTransferCreateHandle((I2C_Type *)g_i2cBaseAddr[instance], &g_i2c_masterHandle, i2c_master_callback, NULL);

    s_i2c_masterXfer.slaveAddress = 0x10;
    s_i2c_masterXfer.subaddress = 0;
    s_i2c_masterXfer.subaddressSize = 0;
    s_i2c_masterXfer.flags = kI2C_TransferDefaultFlag;
}

static void init_flexcan(void)
{
    flexcan_config_t config;
    uint32_t baseAddr = g_flexcanBaseAddr[FLEXCAN_INSTANCE];

    FLEXCAN_GetDefaultConfig(&config);
    config.clkSrc = kFLEXCAN_ClkSrcPeri;
    config.baudRate = 125000;

    /* Select mailbox number */
    s_flexcanInfo.rx_mailbox_num = 8;
    s_flexcanInfo.tx_mailbox_num = 9;

    /* make bootloader as node 'b' for testing */
    s_flexcanInfo.rxId = 0x123;
    s_flexcanInfo.txId = 0x321;

    s_flexcanInfo.rx_buf_write_index = 0;
    s_flexcanInfo.rx_buf_read_index = 0;

    /* Init the interrupt sync object.*/
    OSA_SemaCreate(&s_flexcanInfo.state.txIrqSync, 0);
    OSA_SemaCreate(&s_flexcanInfo.state.rxIrqSync, 0);
    s_flexcanInfo.state.rx_mb_idx = 8;
    s_flexcanInfo.state.tx_mb_idx = 9;

    /* also need to get clock selection config data */
    FLEXCAN_Init((CAN_Type *)baseAddr, &config, get_bus_clock());

    FLEXCAN_Enable((CAN_Type *)baseAddr, true);

    FLEXCAN_EnableInterrupts((CAN_Type *)baseAddr, kFLEXCAN_ErrorInterruptEnable);

    /* using setting table */
    FLEXCAN_SetTimingConfig((CAN_Type *)baseAddr, &bit_rate_table[0]);

    /* FlexCAN reveive config */
    s_flexcanInfo.rx_info.msg_id_type = kFLEXCAN_FrameFormatStandard;
    s_flexcanInfo.rx_info.data_length = 8;

    /* Configure RX MB fields */
    flexcan_rx_mb_config_t mbConfig;
    mbConfig.format = kFLEXCAN_FrameFormatStandard;
    mbConfig.id = CAN_ID_STD(s_flexcanInfo.rxId);
    mbConfig.type = kFLEXCAN_FrameTypeData;
    FLEXCAN_SetRxMbConfig((CAN_Type *)baseAddr, 8, &mbConfig, true);

    FLEXCAN_EnableMbInterrupts((CAN_Type *)baseAddr, 1 << 8);

    /* FlexCAN transfer config */
    s_flexcanInfo.tx_info.msg_id_type = kFLEXCAN_FrameFormatStandard;
    s_flexcanInfo.tx_info.data_length = 8;

    FLEXCAN_SetTxMbConfig((CAN_Type *)baseAddr, 9, false);

    NVIC_EnableIRQ(g_flexcanErrorIrqId[FLEXCAN_INSTANCE]);
    NVIC_EnableIRQ(g_flexcanBusOffIrqId[FLEXCAN_INSTANCE]);
    NVIC_EnableIRQ(g_flexcanOredMessageBufferIrqId[FLEXCAN_INSTANCE]);
}

bool wait_uart_char(uint8_t *data)
{
    /* If has data */
    if (s_uartBase[HOST_UART_INSTANCE]->RCFIFO)
    {
        *data = UART_ReadByte(s_uartBase[HOST_UART_INSTANCE]);
        return true;
    }
    else
    {
        return false;
    }
}

uint8_t wait_uart_char_blocking(void)
{
    uint8_t byte = 0;

    UART_ReadBlocking(s_uartBase[HOST_UART_INSTANCE], &byte, 1);

    return byte;
}

void configure_spi_speed(uint32_t speedkhz)
{
    uint32_t bitsPerSec = speedkhz * 1000;
    DSPI_MasterSetBaudRate((SPI_Type *)g_dspiBaseAddr[SPI_INSTANCE], kDSPI_Ctar1, bitsPerSec, get_bus_clock());
}

status_t send_spi_data(uint8_t *src, uint32_t writeLength)
{
    g_dspi_masterXfer.txData = src;
    g_dspi_masterXfer.rxData = NULL;
    g_dspi_masterXfer.dataSize = writeLength;

    DSPI_MasterTransferBlocking((SPI_Type *)g_dspiBaseAddr[SPI_INSTANCE], &g_dspi_masterXfer);

    return kStatus_Success;
}

status_t receive_spi_data(uint8_t *dest, uint32_t readLength)
{
    g_dspi_masterXfer.txData = NULL;
    g_dspi_masterXfer.rxData = dest;
    g_dspi_masterXfer.dataSize = readLength;

    DSPI_MasterTransferBlocking((SPI_Type *)g_dspiBaseAddr[SPI_INSTANCE], &g_dspi_masterXfer);

    return kStatus_Success;
}

void configure_i2c_speed(uint32_t speedkhz)
{
    I2C_MasterSetBaudRate((I2C_Type *)g_i2cBaseAddr[I2C_INSTANCE], speedkhz * 1000, get_bus_clock());
}

status_t send_i2c_data(uint8_t *src, uint32_t writeLength)
{
    s_i2c_masterXfer.direction = kI2C_Write;
    s_i2c_masterXfer.data = src;
    s_i2c_masterXfer.dataSize = writeLength;

    I2C_MasterTransferBlocking((I2C_Type *)g_i2cBaseAddr[I2C_INSTANCE], &s_i2c_masterXfer);

    return kStatus_Success;
}

static void i2c_master_callback(I2C_Type *base, i2c_master_handle_t *handle, status_t status, void *userData)
{
    /* Signal transfer success when received success status. */
    if (status == kStatus_Success)
    {
        g_I2C_MasterCompletionFlag = true;
    }
}

status_t receive_i2c_data(uint8_t *dest, uint32_t readLength)
{
    uint16_t timeout = UINT16_MAX;

    s_i2c_masterXfer.direction = kI2C_Read;
    s_i2c_masterXfer.data = dest;
    s_i2c_masterXfer.dataSize = readLength;

    I2C_MasterTransferNonBlocking((I2C_Type *)g_i2cBaseAddr[I2C_INSTANCE], &g_i2c_masterHandle, &s_i2c_masterXfer);

    /*  Reset master completion flag to false. */
    g_I2C_MasterCompletionFlag = false;

    /*  Wait for transfer completed. */
    while ((!g_I2C_MasterCompletionFlag) && (--timeout))
    {
    }
    if (timeout == 0)
    {
        return kStatus_Timeout;
    }

    g_I2C_MasterCompletionFlag = false;

    return kStatus_Success;
}

void configure_can_speed(uint32_t speedkhz)
{
    /* Just support 125K, 250K, 500K, 750K, and 1000K */
    uint32_t speed_index = 0;

    switch (speedkhz)
    {
        case kFLEXCAN_125K:
            speed_index = 0;
            break;
        case kFLEXCAN_250K:
            speed_index = 1;
            break;
        case kFLEXCAN_500K:
            speed_index = 2;
            break;
        case kFLEXCAN_750K:
            speed_index = 3;
            break;
        case kFLEXCAN_1000K:
            speed_index = 4;
            break;
    }

    if (speed_index < 5)
    {
        /* using setting table */
        FLEXCAN_SetTimingConfig((CAN_Type *)g_flexcanBaseAddr[FLEXCAN_INSTANCE], &bit_rate_table[speed_index]);
    }
}

status_t send_can_data(uint8_t *src, uint32_t writeLength)
{
    uint32_t sentCnt = 0;
    uint8_t *sendPtr = src;

    while (sentCnt < writeLength)
    {
        if ((writeLength - sentCnt) <= 8)
        {
            /* number of bytes to be sent */
            s_flexcanInfo.tx_info.data_length = writeLength - sentCnt;
            sentCnt += writeLength - sentCnt;
        }
        else
        {
            /* number of bytes to be sent */
            s_flexcanInfo.tx_info.data_length = 8;
            sentCnt += 8;
        }

        FLEXCAN_Send(FLEXCAN_INSTANCE, 9, &s_flexcanInfo.tx_info, s_flexcanInfo.txId, (uint8_t *)sendPtr, 1000);

        sendPtr += s_flexcanInfo.tx_info.data_length;
    }

    reset_can_buffer();

    return kStatus_Success;
}

status_t FLEXCAN_Send(uint8_t instance,
                      uint32_t mb_idx,
                      flexcan_data_info_t *tx_info,
                      uint32_t msg_id,
                      uint8_t *mb_data,
                      uint32_t timeout_ms)
{
    uint32_t baseAddr = g_flexcanBaseAddr[instance];
    osa_status_t syncStatus;
    uint8_t i;
    flexcan_frame_t frame;
    flexcan_mb_transfer_t xfer;
    xfer.mbIdx = mb_idx;
    frame.format = tx_info->msg_id_type;
    frame.length = tx_info->data_length;
    frame.id = CAN_ID_STD(msg_id);
    frame.type = kFLEXCAN_FrameTypeData;
    xfer.frame = &frame;

    /* Copy user's buffer into the message buffer data area*/
    if (mb_data != NULL)
    {
        xfer.frame->dataWord0 = 0x0;
        xfer.frame->dataWord1 = 0x0;

        for (i = 0; i < tx_info->data_length; i++)
        {
            uint32_t temp, temp1;
            temp1 = (*(mb_data + i));
            if (i < 4)
            {
                temp = temp1 << ((3 - i) * 8);
                xfer.frame->dataWord0 |= temp;
            }
            else
            {
                temp = temp1 << ((7 - i) * 8);
                xfer.frame->dataWord1 |= temp;
            }
        }
    }

    if (kStatus_Success == FLEXCAN_WriteTxMb((CAN_Type *)baseAddr, mb_idx, xfer.frame))
    {
        /* Enable Message Buffer Interrupt. */
        FLEXCAN_EnableMbInterrupts((CAN_Type *)baseAddr, 1 << mb_idx);

        do
        {
            syncStatus = OSA_SemaWait(&s_flexcanInfo.state.txIrqSync, timeout_ms);
        } while (syncStatus == kStatus_OSA_Idle);

        /* Disable message buffer interrupt*/
        FLEXCAN_DisableMbInterrupts((CAN_Type *)baseAddr, 1 << mb_idx);

        /* Wait for the interrupt*/
        if (syncStatus != kStatus_OSA_Success)
        {
            return kStatus_Timeout;
        }
        else
        {
            return kStatus_Success;
        }
    }
    else
    {
        return kStatus_Fail;
    }
}

void FLEXCAN_IRQHandler(uint8_t instance)
{
    volatile uint32_t flag_reg;
    uint32_t temp;
    CAN_Type *baseAddr = (CAN_Type *)g_flexcanBaseAddr[instance];

    /* Get the interrupts that are enabled and ready */
    flag_reg = (baseAddr->IFLAG1 & baseAddr->IMASK1);

    /* Check Tx/Rx interrupt flag and clear the interrupt */
    if (flag_reg)
    {
        temp = (1 << s_flexcanInfo.state.rx_mb_idx);
        if (flag_reg & temp)
        {
            OSA_SemaPost(&s_flexcanInfo.state.rxIrqSync);

            flexcan_frame_t rxFrame;
            /* Get RX MB field values*/
            if (!FLEXCAN_ReadRxMb(baseAddr, s_flexcanInfo.state.rx_mb_idx, &rxFrame))
            {
                uint8_t i;
                uint8_t sink_byte = 0;
                for (i = 0; i < rxFrame.length; i++)
                {
                    switch (i)
                    {
                        case 0:
                            sink_byte = rxFrame.dataByte0;
                            break;
                        case 1:
                            sink_byte = rxFrame.dataByte1;
                            break;
                        case 2:
                            sink_byte = rxFrame.dataByte2;
                            break;
                        case 3:
                            sink_byte = rxFrame.dataByte3;
                            break;
                        case 4:
                            sink_byte = rxFrame.dataByte4;
                            break;
                        case 5:
                            sink_byte = rxFrame.dataByte5;
                            break;
                        case 6:
                            sink_byte = rxFrame.dataByte6;
                            break;
                        case 7:
                            sink_byte = rxFrame.dataByte7;
                            break;
                        default:
                            break;
                    }
                    read_can_data(sink_byte, instance);
                }
            }
        }

        temp = (1 << s_flexcanInfo.state.tx_mb_idx);
        if (flag_reg & temp)
        {
            OSA_SemaPost(&s_flexcanInfo.state.txIrqSync);
        }

        baseAddr->IFLAG1 = flag_reg;
    }

    /* Clear all other interrupts in ERRSTAT register (Error, Busoff, Wakeup) */
    FLEXCAN_ClearStatusFlags(baseAddr, kFLEXCAN_ErrorFlag | CAN_ESR1_ERRINT_MASK);

    return;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXCAN_IRQBusoffHandler
 * Description   : Busoff interrupt handler
 *
 *END**************************************************************************/
void FLEXCAN_IRQBusoffHandler(uint8_t instance)
{
    uint32_t baseAddr = g_flexcanBaseAddr[instance];
    FLEXCAN_ClearStatusFlags((CAN_Type *)baseAddr, kFLEXCAN_ErrorFlag | CAN_ESR1_ERRINT_MASK);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXCAN_DRV_IRQ_Error_Handler
 * Description   : flexCAN general error interrupt handler
 *
 *END**************************************************************************/
void FLEXCAN_IRQErrorHandler(uint8_t instance)
{
    uint32_t baseAddr = g_flexcanBaseAddr[instance];
    FLEXCAN_ClearStatusFlags((CAN_Type *)baseAddr, kFLEXCAN_ErrorFlag | CAN_ESR1_ERRINT_MASK);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : receive_can_data
 * Description   : flexCAN receiving data process
 *
 *END**************************************************************************/
static void read_can_data(uint8_t data, uint32_t instance)
{
    s_flexcanInfo.rx_buf[s_flexcanInfo.rx_buf_write_index++] = data;
    s_flexcanInfo.rx_buf_write_index &= 0x3f;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : reset_can_buffer
 * Description   : flexCAN reset buffer process
 *
 *END**************************************************************************/
static void reset_can_buffer(void)
{
    s_flexcanInfo.rx_buf_write_index = 0;
    s_flexcanInfo.rx_buf_read_index = 0;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : read_can_data
 * Description   : flexCAN read data process
 *
 *END**************************************************************************/
status_t receive_can_data(uint8_t *dest, uint32_t readLength)
{
    uint8_t received_cnt = 0;
    uint16_t timeout = UINT16_MAX;

    while ((received_cnt < readLength) && (--timeout))
    {
        if (s_flexcanInfo.rx_buf_read_index != s_flexcanInfo.rx_buf_write_index)
        {
            dest[received_cnt++] = s_flexcanInfo.rx_buf[s_flexcanInfo.rx_buf_read_index++];
            s_flexcanInfo.rx_buf_read_index &= 0x3f;
        }
    }

    if (timeout == 0)
    {
        init_flexcan();
        return kStatus_Timeout;
    }

    return kStatus_Success;
}

void configure_uart_speed(uint32_t baud)
{
    uart_config_t config;

    UART_GetDefaultConfig(&config);
    config.baudRate_Bps = baud;
    config.enableTx = true;
    config.enableRx = true;

    UART_Init(s_uartBase[UART_INSTANCE], &config, get_bus_clock());
}

status_t send_uart_data(uint8_t *src, uint32_t writeLength)
{
    UART_WriteBlocking(s_uartBase[UART_INSTANCE], src, writeLength);

    return kStatus_Success;
}

status_t receive_uart_data(uint8_t *dest, uint32_t readLength)
{
    uint16_t timeout = UINT16_MAX;

    while ((((s_uart_bytesRx + k_uartBufferSize - s_uartBufferOffset) % k_uartBufferSize) < readLength) && (--timeout))
    {
    }

    if (timeout == 0)
    {
        return kStatus_Timeout;
    }

    for (uint32_t i = 0; i < readLength; i++)
    {
        dest[i] = s_uartPtr[(s_uartBufferOffset + i) % k_uartBufferSize];
    }
    s_uartBufferOffset = (s_uartBufferOffset + sizeof(uint8_t) * readLength) % k_uartBufferSize;

    return kStatus_Success;
}

void UART4_RX_TX_IRQHandler(void)
{
    if (UART4->S1 & UART_S1_RDRF_MASK)
    {
        s_uart_byte_receive_callback(UART4->D);
    }
}

static void s_uart_byte_receive_callback(uint8_t byte)
{
    s_uart_rxData = s_uartPtr;
    if (s_uart_rxData)
    {
        s_uart_rxData[s_uart_bytesRx] = byte;
        s_uart_bytesRx = (s_uart_bytesRx + 1) % k_uartBufferSize;
    }
    s_uart_rxData = 0;
}

void CAN0_ORed_Message_buffer_IRQHandler(void)
{
    FLEXCAN_IRQHandler(0);
}

/* Implementation of CAN0 handler named in startup code. */
void CAN0_Bus_Off_IRQHandler(void)
{
    FLEXCAN_IRQBusoffHandler(0);
}

/* Implementation of CAN0 handler named in startup code. */
void CAN0_Error_IRQHandler(void)
{
    FLEXCAN_IRQErrorHandler(0);
}

void CAN0_Wake_Up_IRQHandler(void)
{
    FLEXCAN_IRQHandler(0);
}

#if __ICCARM__

size_t __write(int handle, const unsigned char *buf, size_t size)
{
    while (size--)
    {
        UART_WriteBlocking(s_uartBase[HOST_UART_INSTANCE], (uint8_t const *)buf++, 1);
    }
    return size;
}

#endif /* __ICCARM__ */
