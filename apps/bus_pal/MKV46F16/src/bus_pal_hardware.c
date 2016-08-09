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

#include "bus_pal_hardware.h"
#include "fpga_clock_registers.h"
#include "fsl_device_registers.h"
#include "i2c/fsl_i2c.h"
#include "microseconds/microseconds.h"
#include "dspi/fsl_dspi.h"
#include "flexcan/fsl_flexcan.h"
#include "uart/fsl_uart.h"
#include "utilities/fsl_rtos_abstraction.h"

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

////////////////////////////////////////////////////////////////////////////////
// Prototypes
////////////////////////////////////////////////////////////////////////////////

/*!
 * @brief init suart functions.
 */
static void init_scuarts(void);

/*!
 * @brief dspi initialization.
 */
static void init_dspi(void);

/*!
 * @brief flexcan initialization.
 */
static void init_flexcan(void);

/*!
 * @brief i2c initialization.
 */
static void init_i2c(uint32_t instance);

/*!
 * @brief i2c de-initialization.
 */
static void deinit_i2c(uint32_t instance);

/*!
 * @brief uart rx callback function.
 */
static void uart_rx_callback(uint8_t byte);

/*!
 * @brief get PORT base address function.
 */
static PORT_Type *getPortBaseAddrFromAscii(uint8_t port);

/*!
 * @brief get GPIO base address function.
 */
static GPIO_Type *getGpioBaseAddrFromAscii(uint8_t port);

/*!
 * @brief fpga write clock reg function.
 */
static void write_fpga_clock_reg(uint8_t reg, uint8_t val);

static status_t FLEXCAN_Send(uint8_t instance,
                             uint32_t mb_idx,
                             flexcan_data_info_t *tx_info,
                             uint32_t msg_id,
                             uint8_t *mb_data,
                             uint32_t timeout_ms);

////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////
//! @brief Variable for i2c host configuration information
static i2c_user_config_t s_i2cUserConfig = {.slaveAddress = 0x10, //!< The slave's 7-bit address
                                            .baudRate_kbps = 100 };

static i2c_user_config_t s_i2cFPGAUserConfig = {.slaveAddress = CY22393_ADDR, //!< The slave's 7-bit address
                                                .baudRate_kbps = 400 };

static dspi_user_config_t s_dspiUserConfig = {.polarity = kDSPI_ClockPolarityActiveLow, /*!< Clock polarity */
                                              .phase = kDSPI_ClockPhaseSecondEdge,      /*!< Clock phase */
                                              .direction = kDSPI_MsbFirst,              /*!< MSB or LSB */
                                              .baudRate_Bps = 100000,                   /*!< Baud Rate for SPI in Hz */
                                              .clock_Hz = 0 };

static dspi_master_handle_t s_dspiHandle;
static i2c_master_handle_t s_i2cHandle;

//! @brief Variable for host data receiving
static uint8_t *s_rxData;
static uint32_t s_bytesRx;

const static uint32_t g_dspiBaseAddr[] = SPI_BASE_ADDRS;
const static uint32_t g_i2cBaseAddr[] = I2C_BASE_ADDRS;
const static uint32_t g_uartBaseAddr[] = UART_BASE_ADDRS;
const static uint32_t g_flexcanBaseAddr[] = CAN_BASE_ADDRS;

/* Tables to save CAN IRQ enum numbers defined in CMSIS header file. */
const IRQn_Type g_flexcanRxWarningIrqId[] = CAN_Rx_Warning_IRQS;
const IRQn_Type g_flexcanTxWarningIrqId[] = CAN_Tx_Warning_IRQS;
const IRQn_Type g_flexcanWakeUpIrqId[] = CAN_Wake_Up_IRQS;
const IRQn_Type g_flexcanErrorIrqId[] = CAN_Error_IRQS;
const IRQn_Type g_flexcanBusOffIrqId[] = CAN_Bus_Off_IRQS;
const IRQn_Type g_flexcanOredMessageBufferIrqId[] = CAN_ORed_Message_buffer_IRQS;

#define FLEXCAN_USE_OSC_8M_CLOCK 0

#if FLEXCAN_USE_OSC_8M_CLOCK
/*!
 * @brief flexCAN timing table (8Mhz)contains propseg, pseg1, pseg2, pre_divider, rjw
 */
flexcan_timing_config_t bit_rate_table[] = {
    { 7, 2, 2, 2, 0 }, /* 125 kHz */
    { 3, 2, 2, 2, 0 }, /* 250 kHz */
    { 1, 1, 1, 1, 2 }, /* 500 kHz */
    { 0, 2, 2, 2, 2 }, /* 750 kHz */
    { 0, 1, 1, 1, 2 }  /* 1   MHz */
};

#else
/*!
 * @brief flexCAN timing table (20.9715Mhz)contains propseg, pseg1, pseg2, pre_divider, rjw
 */
flexcan_timing_config_t bit_rate_table[] = {
    { 7, 3, 7, 7, 3 }, /* 125 kHz */
    { 3, 3, 7, 7, 3 }, /* 250 kHz */
    { 1, 3, 7, 7, 3 }, /* 500 kHz */
    { 1, 3, 3, 3, 5 }, /* 750 kHz */
    { 0, 3, 5, 5, 7 }  /* 1   MHz */
};
#endif

/*!
 * @brief flexCAN instance used for bus pal
 */
uint8_t flexcanInstance = 0;

//! @brief Global state for the FlexCAN peripheral interface.
flexcan_transfer_info_t s_flexcanInfo;

uint32_t g_calculatedBaudRate;

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////

/*FUNCTION**********************************************************************
 *
 * Function Name : get_bus_clock
 * Description   : Gets bus clock
 *
 *END**************************************************************************/
uint32_t get_bus_clock(void)
{
    uint32_t busClockDivider = ((SIM->CLKDIV1 & SIM_CLKDIV1_OUTDIV4_MASK) >> SIM_CLKDIV1_OUTDIV4_SHIFT) + 1;
    return (SystemCoreClock / busClockDivider);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : get_fast_peripheral_clock
 * Description   : fast peripheral clock
 *
 *END**************************************************************************/
uint32_t get_fast_peripheral_clock(void)
{
    uint32_t busClockDivider = ((SIM->CLKDIV1 & SIM_CLKDIV1_OUTDIV2_MASK) >> SIM_CLKDIV1_OUTDIV2_SHIFT) + 1;
    return (SystemCoreClock / busClockDivider);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : init_hardware
 * Description   : hardware initialization
 *
 *END**************************************************************************/
void init_hardware(void)
{
    SIM->SCGC5 |= (SIM_SCGC5_PORTA_MASK | SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTC_MASK | SIM_SCGC5_PORTD_MASK |
                   SIM_SCGC5_PORTE_MASK);

    // Enable pins for UART1 on PTE0 - PTE1.
    PORTE->PCR[1] = PORT_PCR_MUX(3); // UART1_RX is ALT3 for pin PTC3
    PORTE->PCR[0] = PORT_PCR_MUX(3); // UART1_TX is ALT3 for pin PTC4

    // Enable pins for I2C0 on PTC14 - PTC15.
    PORTC->PCR[14] = PORT_PCR_MUX(3) | PORT_PCR_ODE_MASK; // I2C0_SCL is ALT3 for pin PTC14, I2C0_SCL set for open drain
    PORTC->PCR[15] = PORT_PCR_MUX(3) | PORT_PCR_ODE_MASK; // I2C0_SDA is ALT3 for pin PTC15, I2C0_SDA set for open drain

    // Enable pins for SPI0 on PTA14 - PTA17.
    PORTA->PCR[14] = PORT_PCR_MUX(2); // SPI0_PCS0 is ALT2 for pin PTA14
    PORTA->PCR[15] = PORT_PCR_MUX(2); // SPI0_SCK  is ALT2 for pin PTA15
    PORTA->PCR[16] = PORT_PCR_MUX(2); // SPI0_SOUT is ALT2 for pin PTA16
    PORTA->PCR[17] = PORT_PCR_MUX(2); // SPI0_SIN  is ALT2 for pin PTA17

    // Enable pins for FLEXCAN0 on PTA12 - PTA13.
    PORTA->PCR[12] = PORT_PCR_MUX(2); // FLEXCAN0_TX is ALT2 for pin PTA12
    PORTA->PCR[13] = PORT_PCR_MUX(2); // FLEXCAN0_RX is ALT2 for pin PTA13

    // Ungate clocks to the UART modules
    SIM->SCGC4 |= (SIM_SCGC4_UART0_MASK | SIM_SCGC4_UART1_MASK);

    microseconds_init();

    init_scuarts();
    init_dspi();
    init_flexcan();
    init_i2c(0);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : init_scuarts
 * Description   : Initialize UART ports
 *
 *END**************************************************************************/
static void init_scuarts(void)
{
    // UART1
    uart_config_t userConfig;
    uint32_t baseAddr = g_uartBaseAddr[1];
    UART_GetDefaultConfig(&userConfig);

    userConfig.baudRate_Bps = 57600;
    userConfig.enableTx = true;
    userConfig.enableRx = true;

    NVIC_EnableIRQ(UART1_RX_TX_IRQn);
    UART_Init((UART_Type *)baseAddr, &userConfig, get_fast_peripheral_clock());
    UART_EnableInterrupts((UART_Type *)baseAddr, kUART_RxDataRegFullInterruptEnable);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : init_dspi
 * Description   : Initialize dspi
 *
 *END**************************************************************************/
static void init_dspi(void)
{
    dspi_master_config_t config;
    uint32_t baseAddr = g_dspiBaseAddr[0];

    DSPI_MasterGetDefaultConfig(&config);

    config.whichCtar = kDSPI_Ctar1;
    config.ctarConfig.cpol = s_dspiUserConfig.polarity;
    config.ctarConfig.cpha = s_dspiUserConfig.phase;
    config.ctarConfig.baudRate = s_dspiUserConfig.baudRate_Bps;

    s_dspiUserConfig.clock_Hz = get_fast_peripheral_clock();

    DSPI_MasterInit((SPI_Type *)baseAddr, &config, s_dspiUserConfig.clock_Hz);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : init_flexcan
 * Description   : Initialize flexCAN
 *
 *END**************************************************************************/
static void init_flexcan(void)
{
    flexcan_config_t config;
    uint32_t baseAddr = g_flexcanBaseAddr[0];

    FLEXCAN_GetDefaultConfig(&config);
#if FLEXCAN_USE_OSC_8M_CLOCK
    config.clkSrc = kFLEXCAN_ClkSrcOsc;
#else
    config.clkSrc = kFLEXCAN_ClkSrcPeri;
#endif
    config.maxMbNum = 16;
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

    // also need to get clock selection config data
    FLEXCAN_Init((CAN_Type *)baseAddr, &config, 1000000 * 8 * 10);

    FLEXCAN_Enable((CAN_Type *)baseAddr, true);

    FLEXCAN_EnableInterrupts((CAN_Type *)baseAddr, kFLEXCAN_ErrorInterruptEnable);

    // using setting table
    FLEXCAN_SetTimingConfig((CAN_Type *)baseAddr, &bit_rate_table[0]);

    // FlexCAN reveive config
    s_flexcanInfo.rx_info.msg_id_type = kFLEXCAN_FrameFormatStandard;
    s_flexcanInfo.rx_info.data_length = 8;

    // Configure RX MB fields
    flexcan_rx_mb_config_t mbConfig;
    mbConfig.format = kFLEXCAN_FrameFormatStandard;
    mbConfig.id = CAN_ID_STD(s_flexcanInfo.rxId);
    mbConfig.type = kFLEXCAN_FrameTypeData;
    FLEXCAN_SetRxMbConfig((CAN_Type *)baseAddr, 8, &mbConfig, true);

    FLEXCAN_EnableMbInterrupts((CAN_Type *)baseAddr, 1 << 8);
    // FlexCAN transfer config
    s_flexcanInfo.tx_info.msg_id_type = kFLEXCAN_FrameFormatStandard;
    s_flexcanInfo.tx_info.data_length = 8;

    FLEXCAN_SetTxMbConfig((CAN_Type *)baseAddr, 9, false);

    NVIC_EnableIRQ(g_flexcanErrorIrqId[0]);
    NVIC_EnableIRQ(g_flexcanBusOffIrqId[0]);
    NVIC_EnableIRQ(g_flexcanOredMessageBufferIrqId[0]);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : write_fpga_clock_reg
 * Description   : fpga clock reg write function
 *
 *END**************************************************************************/
void write_fpga_clock_reg(uint8_t reg, uint8_t val)
{
    uint8_t packet[2] = { reg, val };
    uint32_t baseAddr = g_i2cBaseAddr[0];
    i2c_master_transfer_t send_data;
    send_data.slaveAddress = s_i2cFPGAUserConfig.slaveAddress;
    send_data.direction = kI2C_Write;
    send_data.data = packet;
    send_data.dataSize = 2;

    I2C_MasterTransferBlocking((I2C_Type *)baseAddr, &send_data);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : set_fpga_clock
 * Description   : fpga clock set function
 *
 *END**************************************************************************/
void set_fpga_clock(uint32_t clock)
{
    uint32_t i;
    uint32_t P, bestP;
    uint32_t Q, bestQ;
    uint32_t realClock;
    uint32_t diff, min_diff;
    uint32_t PHigh, P0;
    uint32_t pumpVal;
    uint32_t vcoClock;
    uint32_t postDiv;

    // Get the closest we can to the max VCO clock
    vcoClock = clock * (CY22393_MAX_VCO_CLK / clock);
    // Get the post divider we will need after setting to this high clock
    postDiv = vcoClock / clock;

    // The post div value cannot be above 31 for VCO clocks above 333MHZ
    if (postDiv > CY22393_POSTDIV_MAX_VAL)
    {
        uint32_t correction = postDiv - CY22393_POSTDIV_MAX_VAL;
        vcoClock = CY22393_MAX_VCO_CLK - (clock * correction);
        postDiv = CY22393_POSTDIV_MAX_VAL;
    }

    /* http://www.cypress.com/?id=4&rID=27709 */
    /* In all for loops, if min_diff = 0, exit for loop */
    /* F = (Ref * (P/Q)) / postDiv */
    /* Ref / Q must be >= 250khz */
    /* Q range can be between 2 and 257 */
    /* P range can be between 16 and 1600 */
    /* find combination of p0, p, and q resulting in clock closest to the requested value */
    min_diff = ~0;
    bestP = 0;
    bestQ = 0;

    for (Q = 2; ((CY22393_REF_CLK / Q) >= CY22393_MIN_REF_DIV_Q) && (Q < 257) && min_diff; Q++)
    {
        for (P = 16; (P <= 1600) && min_diff; P++)
        {
            realClock = (CY22393_REF_CLK / Q) * P;

            if (vcoClock >= realClock)
            {
                diff = vcoClock - realClock;
            }
            else
            {
                diff = realClock - vcoClock;
            }

            if (min_diff > diff)
            {
                /* a better match found */
                min_diff = diff;
                bestP = P;
                bestQ = Q;
            }

            // Since we are just increasing our multiplier in this loop if its past our desired clock
            // we can break to start increasing the quotient
            if (realClock > vcoClock)
            {
                break;
            }
        }
    }

    P0 = bestP & 1;
    PHigh = (bestP / 2) - 3;
    bestQ -= 2;

    if ((bestP >= 16) && (bestP <= 231))
    {
        pumpVal = 0;
    }
    else if ((bestP >= 232) && (bestP <= 626))
    {
        pumpVal = 1;
    }
    else if ((bestP >= 627) && (bestP <= 834))
    {
        pumpVal = 2;
    }
    else if ((bestP >= 835) && (bestP <= 1043))
    {
        pumpVal = 3;
    }
    else
    {
        pumpVal = 4;
    }

    // Clear any existing values
    for (i = CY22393_REG_LOW; i <= CY22393_REG_HIGH; i++)
    {
        write_fpga_clock_reg(i, 0);
    }

    // Disable PLL3
    write_fpga_clock_reg(CY22393_REG_PLL3E, 0);

    // Enable Clock A
    write_fpga_clock_reg(CY22393_REG_CLKA_DIVIDE, 1);

    // Set the CLK A post divider
    write_fpga_clock_reg(CY22393_REG_CLKA_DIVIDE, postDiv);

    // Disable the other clock outputs
    write_fpga_clock_reg(CY22393_REG_CLKB_DIVIDE, CY22393_DIVIDE_OFF); // clkb
    write_fpga_clock_reg(CY22393_REG_CLKC_DIVIDE, CY22393_DIVIDE_OFF); // clkc
    write_fpga_clock_reg(CY22393_REG_CLKD_DIVIDE, CY22393_DIVIDE_OFF); // clkd

    // Set all clock sources from PLL3
    write_fpga_clock_reg(CY22393_REG_SOURCE, 0xFF);

    // Set All clocks ACAdj to nominal (b01) with pulldowns enabled and xbuf output enable
    write_fpga_clock_reg(CY22393_REG_AC, 0x5C);
    // Set all clocks to use nominal drive strength
    write_fpga_clock_reg(CY22393_REG_DC, CY22393_DC);

    write_fpga_clock_reg(CY22393_REG_PLL3P, PHigh);
    write_fpga_clock_reg(CY22393_REG_PLL3Q, bestQ);

    // B6 enables PLL3
    // B5:B3 is the pump value
    // B2 is for P0 value
    // B1:0 is for B9:8 of P
    write_fpga_clock_reg(CY22393_REG_PLL3E, (1 << 6) | (pumpVal << 3) | (P0 << 2) | ((PHigh & 0x300) >> 8));
}

/*FUNCTION**********************************************************************
 *
 * Function Name : init_i2c
 * Description   : I2C init function
 *
 *END**************************************************************************/
void init_i2c(uint32_t instance)
{
    uint32_t baseAddr = g_i2cBaseAddr[instance];
    i2c_master_config_t config;

    I2C_MasterGetDefaultConfig(&config);

    I2C_MasterInit((I2C_Type *)baseAddr, &config, get_bus_clock());
    I2C_MasterTransferCreateHandle((I2C_Type *)baseAddr, &s_i2cHandle, NULL, NULL);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : deinit_i2c
 * Description   : I2C de-init function
 *
 *END**************************************************************************/
void deinit_i2c(uint32_t instance)
{
    uint32_t baseAddr = g_i2cBaseAddr[instance];
    I2C_MasterDeinit((I2C_Type *)baseAddr);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : host_start_command_rx
 * Description   : receiving host start command process
 *
 *END**************************************************************************/
void host_start_command_rx(uint8_t *dest, uint32_t length)
{
    s_rxData = dest;
    s_bytesRx = 0;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : host_stop_command_rx
 * Description   : receiving host stop command process
 *
 *END**************************************************************************/
void host_stop_command_rx(void)
{
    s_rxData = 0;
    s_bytesRx = 0;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : get_bytes_received_from_host
 * Description   : receiving host get bytes command process
 *
 *END**************************************************************************/
uint32_t get_bytes_received_from_host(void)
{
    return s_bytesRx;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : write_bytes_to_host
 * Description   : sending host bytes command process
 *
 *END**************************************************************************/
void write_bytes_to_host(uint8_t *src, uint32_t length)
{
    uint32_t baseAddr = g_uartBaseAddr[1];

    UART_WriteBlocking((UART_Type *)baseAddr, src, length);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : configure_i2c_address
 * Description   : i2c config address process
 *
 *END**************************************************************************/
void configure_i2c_address(uint8_t address)
{
    s_i2cUserConfig.slaveAddress = address;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : configure_i2c_speed
 * Description   : i2c config speed process
 *
 *END**************************************************************************/
void configure_i2c_speed(uint32_t speedkhz)
{
    s_i2cUserConfig.baudRate_kbps = speedkhz;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : send_spi_data
 * Description   : spi send data proces
 *
 *END**************************************************************************/
void send_spi_data(uint8_t *src, uint32_t writeLength)
{
    uint32_t baseAddr = g_dspiBaseAddr[0];
    dspi_transfer_t send_data;
    send_data.txData = src;
    send_data.dataSize = writeLength;
    send_data.rxData = NULL;
    send_data.configFlags = kDSPI_MasterCtar1 | kDSPI_MasterPcs0 | kDSPI_MasterPcsContinuous;
    DSPI_MasterTransferBlocking((SPI_Type *)baseAddr, &send_data);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : receive_spi_data
 * Description   : spi receiving data process
 *
 *END**************************************************************************/
void receive_spi_data(uint8_t *dest, uint32_t readLength)
{
    uint32_t baseAddr = g_dspiBaseAddr[0];
    dspi_transfer_t receive_data;
    receive_data.rxData = dest;
    receive_data.dataSize = readLength;
    receive_data.txData = NULL;
    receive_data.configFlags = kDSPI_MasterCtar1 | kDSPI_MasterPcs0 | kDSPI_MasterPcsContinuous;
    DSPI_MasterTransferBlocking((SPI_Type *)baseAddr, &receive_data);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : configure_spi_speed
 * Description   : spi config speed process
 *
 *END**************************************************************************/
void configure_spi_speed(uint32_t speedkhz)
{
    uint32_t baseAddr = g_dspiBaseAddr[0];
    s_dspiUserConfig.baudRate_Bps = speedkhz * 1000;
    DSPI_MasterSetBaudRate((SPI_Type *)baseAddr, kDSPI_Ctar1, s_dspiUserConfig.baudRate_Bps,
                           get_fast_peripheral_clock());
}

/*FUNCTION**********************************************************************
 *
 * Function Name : configure_spi_settings
 * Description   : spi config settings process
 *
 *END**************************************************************************/
void configure_spi_settings(dspi_clock_polarity_t polarity, dspi_clock_phase_t phase, dspi_shift_direction_t direction)
{
    s_dspiUserConfig.polarity = polarity;
    s_dspiUserConfig.phase = phase;
    s_dspiUserConfig.direction = direction;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : configure_can_txid
 * Description   : flexCAN config tx id
 *
 *END**************************************************************************/
void configure_can_txid(uint32_t txid)
{
    s_flexcanInfo.txId = txid & 0x7ff; // support 11 bit std id
}

/*FUNCTION**********************************************************************
 *
 * Function Name : configure_can_rxid
 * Description   : flexCAN config rx id
 *
 *END**************************************************************************/
void configure_can_rxid(uint32_t rxid)
{
    uint32_t baseAddr = g_flexcanBaseAddr[0];
    s_flexcanInfo.rxId = rxid & 0x7ff; // support 11 bit std id

    // Configure RX MB fields
    flexcan_rx_mb_config_t mbConfig;
    mbConfig.format = kFLEXCAN_FrameFormatStandard;
    mbConfig.id = CAN_ID_STD(s_flexcanInfo.rxId);
    mbConfig.type = kFLEXCAN_FrameTypeData;
    FLEXCAN_SetRxMbConfig((CAN_Type *)baseAddr, 8, &mbConfig, true);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : configure_can_speed
 * Description   : flexCAN config speed process
 *
 *END**************************************************************************/
void configure_can_speed(uint32_t speed)
{
    uint32_t baseAddr = g_flexcanBaseAddr[0];

    if (speed < 5)
    {
        // using setting table
        FLEXCAN_SetTimingConfig((CAN_Type *)baseAddr, &bit_rate_table[speed]);
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : send_can_data
 * Description   :  flexCAN sending data process
 *
 *END**************************************************************************/
void send_can_data(uint8_t *src, uint32_t writeLength)
{
    uint32_t sentCnt = 0;
    uint8_t *sendPtr = src;

    while (sentCnt < writeLength)
    {
        if ((writeLength - sentCnt) <= 8)
        {
            // number of bytes to be sent
            s_flexcanInfo.tx_info.data_length = writeLength - sentCnt;
            sentCnt += writeLength - sentCnt;
        }
        else
        {
            // number of bytes to be sent
            s_flexcanInfo.tx_info.data_length = 8;
            sentCnt += 8;
        }

        FLEXCAN_Send(0, 9, &s_flexcanInfo.tx_info, s_flexcanInfo.txId, (uint8_t *)sendPtr, 1000);

        sendPtr += s_flexcanInfo.tx_info.data_length;
    }

    reset_can_buffer();
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
                    receive_can_data(sink_byte, instance);
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
void receive_can_data(uint8_t data, uint32_t instance)
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
void reset_can_buffer(void)
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
void read_can_data(uint8_t *dest, uint32_t readLength)
{
    uint8_t received_cnt = 0;
    uint64_t timeoutTicks = microseconds_get_ticks() + 20875 * 500; // 5ms time out

    while ((received_cnt < readLength) && (microseconds_get_ticks() < timeoutTicks))
    {
        if (s_flexcanInfo.rx_buf_read_index != s_flexcanInfo.rx_buf_write_index)
        {
            dest[received_cnt++] = s_flexcanInfo.rx_buf[s_flexcanInfo.rx_buf_read_index++];
            s_flexcanInfo.rx_buf_read_index &= 0x3f;
        }
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : send_i2c_data
 * Description   : i2c sending data process
 *
 *END**************************************************************************/
status_t send_i2c_data(uint8_t *src, uint32_t writeLength)
{
    i2c_master_transfer_t send_data;
    uint32_t baseAddr = g_i2cBaseAddr[0];
    send_data.slaveAddress = s_i2cUserConfig.slaveAddress;
    send_data.direction = kI2C_Write;
    send_data.data = src;
    send_data.dataSize = writeLength;
    send_data.subaddress = 0;
    send_data.subaddressSize = 0;
    send_data.flags = kI2C_TransferDefaultFlag;

    I2C_MasterTransferBlocking((I2C_Type *)baseAddr, &send_data);

    return kStatus_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : receive_i2c_data
 * Description   : i2c receiving data process
 *
 *END**************************************************************************/
status_t receive_i2c_data(uint8_t *dest, uint32_t readLength)
{
    i2c_master_transfer_t receive_data;
    uint32_t baseAddr = g_i2cBaseAddr[0];
    receive_data.slaveAddress = s_i2cUserConfig.slaveAddress;
    receive_data.direction = kI2C_Read;
    receive_data.data = dest;
    receive_data.dataSize = readLength;
    receive_data.subaddress = 0;
    receive_data.subaddressSize = 0;
    receive_data.flags = kI2C_TransferDefaultFlag;

    I2C_MasterTransferBlocking((I2C_Type *)baseAddr, &receive_data);

    return kStatus_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : uart_rx_callback
 * Description   : uart callback function
 *
 *END**************************************************************************/
void uart_rx_callback(uint8_t byte)
{
    if (s_rxData)
    {
        s_rxData[s_bytesRx++] = byte;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : getPortBaseAddrFromAscii
 * Description   : PORT get base address function
 *
 *END**************************************************************************/
PORT_Type *getPortBaseAddrFromAscii(uint8_t port)
{
    if ((port >= 'a') && (port <= 'e'))
    {
        port = port - 'a';
    }
    else if ((port >= 'A') && (port <= 'E'))
    {
        port = port - 'A';
    }

    switch (port)
    {
        default:
        case 0:
            return PORTA;
        case 1:
            return PORTB;
        case 2:
            return PORTC;
        case 3:
            return PORTD;
        case 4:
            return PORTE;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : getGpioBaseAddrFromAscii
 * Description   : GPIO get base address function
 *
 *END**************************************************************************/
GPIO_Type *getGpioBaseAddrFromAscii(uint8_t port)
{
    if ((port >= 'a') && (port <= 'e'))
    {
        port = port - 'a';
    }
    else if ((port >= 'A') && (port <= 'E'))
    {
        port = port - 'A';
    }

    switch (port)
    {
        default:
        case 0:
            return GPIOA;
        case 1:
            return GPIOB;
        case 2:
            return GPIOC;
        case 3:
            return GPIOD;
        case 4:
            return GPIOE;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : configure_gpio
 * Description   : GPIO config processing
 *
 *END**************************************************************************/
void configure_gpio(uint8_t port, uint8_t pinNum, uint8_t muxVal)
{
    PORT_Type *realPort = getPortBaseAddrFromAscii(port);
    realPort->PCR[pinNum] = ((~PORT_PCR_MUX_MASK) & realPort->PCR[pinNum]) | PORT_PCR_MUX(muxVal);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : set_gpio
 * Description   : GPIO set up function
 *
 *END**************************************************************************/
void set_gpio(uint8_t port, uint8_t pinNum, uint8_t level)
{
    GPIO_Type *realPort = getGpioBaseAddrFromAscii(port);

    realPort->PDDR |= 1 << pinNum;

    if (level)
    {
        realPort->PSOR |= 1 << pinNum;
    }
    else
    {
        realPort->PCOR |= 1 << pinNum;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name: UART1_RX_TX_IRQHandler
* Description  : UART1 IRQ Handler
 *
 *
 *END**************************************************************************/

void UART1_RX_TX_IRQHandler(void)
{
    uint8_t s1 = UART1->S1;
    uint8_t d;

    if (s1 & UART_S1_FE_MASK)
    {
        d = UART1->D;
    }
    else if (s1 & UART_S1_RDRF_MASK)
    {
        d = UART1->D;
        uart_rx_callback(d);
    }
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
/*FUNCTION**********************************************************************
 *
 * Function Name : __write
 * Description   : ICCARM write function implementation
 *
 *END**************************************************************************/
size_t __write(int handle, const unsigned char *buf, size_t size)
{
    return size;
}

#endif // __ICCARM__
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
