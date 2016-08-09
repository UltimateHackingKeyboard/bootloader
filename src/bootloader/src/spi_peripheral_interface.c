/*
 * Copyright (c) 2013, Freescale Semiconductor, Inc.
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

#include "utilities/fsl_assert.h"
#include "bootloader/bl_context.h"
#include "bootloader_common.h"
#include "bootloader/bl_irq_common.h"
#include "packet/command_packet.h"
#include "spi/fsl_spi.h"
#include "fsl_device_registers.h"
#include "packet/serial_packet.h"

#if BL_CONFIG_SPI
//! @addtogroup spi_peripheral
//! @{

////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////

//! @brief Synchronization state between SPI ISR and read/write functions.
typedef struct _spi_transfer_info
{
    const uint8_t *writeData;                                //!< The applications data to write
    volatile uint32_t bytesToTransfer;                       //!< The total number of bytes to be transmitted
    void (*data_source)(uint8_t *source_byte);               // !< Callback used to get byte to transmit.
    void (*data_sink)(uint8_t sink_byte, uint16_t instance); // !< Callback used to put received byte.
} spi_transfer_info_t;

////////////////////////////////////////////////////////////////////////////////
// Prototypes
////////////////////////////////////////////////////////////////////////////////

//! @brief SPI slave poll for activity function
static bool spi_poll_for_activity(const peripheral_descriptor_t *self);
//! @brief SPI slave init function
static status_t spi_full_init(const peripheral_descriptor_t *self, serial_byte_receive_func_t function);
//! @brief SPI slave shutdown function
static void spi_full_shutdown(const peripheral_descriptor_t *self);
//! @brief SPI slave sending data function
static void spi_data_source(uint8_t *source_byte);
//! @brief SPI slave receiving first byte data function
static void spi_initial_data_sink(uint8_t sink_byte, uint16_t instance);
//! @brief SPI slave receiving data function
static void spi_data_sink(uint8_t sink_byte, uint16_t instance);
//! @brief SPI slave writing data function
static status_t spi_write(const peripheral_descriptor_t *self, const uint8_t *buffer, uint32_t byteCount);

////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////

/*!
 * @brief SPI slave control interface information
 */
const peripheral_control_interface_t g_spiControlInterface = {
    .pollForActivity = spi_poll_for_activity, .init = spi_full_init, .shutdown = spi_full_shutdown, .pump = 0
};

/*!
 * @brief SPI slave byte interface information
 */
const peripheral_byte_inteface_t g_spiByteInterface = {.init = NULL, .write = spi_write };

//! @brief Global state for the SPI slave peripheral interface.
static spi_transfer_info_t s_spiInfo = {
    .writeData = 0, .bytesToTransfer = 0, .data_source = spi_data_source, .data_sink = spi_initial_data_sink
};

//! @brief Flag for detecting device activity
static bool s_spiActivity[FSL_FEATURE_SOC_SPI_COUNT] = { false };
static bool s_spiIntialized[FSL_FEATURE_SOC_SPI_COUNT] = { false };

/*!
 * @brief SPI slave receiving data call back function
 */
static serial_byte_receive_func_t s_spi_app_data_sink_callback;

const static uint32_t g_spiBaseAddr[] = SPI_BASE_ADDRS;

static const IRQn_Type spi_irq_ids[FSL_FEATURE_SOC_SPI_COUNT] = {
#if defined(SPI0)
    SPI0_IRQn,
#else
    SPI_IRQn,
#endif
#if (FSL_FEATURE_SOC_SPI_COUNT > 1)
    SPI1_IRQn,
#endif
#if (FSL_FEATURE_SOC_SPI_COUNT > 2)
    SPI2_IRQn,
#endif
};

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////

void SPI_SetSystemIRQ(uint32_t instance, PeripheralSystemIRQSetting set)
{
    switch (instance)
    {
        case 0:
#if (FSL_FEATURE_SOC_DSPI_COUNT > 1)
        case 1:
#endif // #if (LPI2C_INSTANCE_COUNT > 1)
#if (FSL_FEATURE_SOC_DSPI_COUNT > 2)
        case 2:
#endif // #if (LPI2C_INSTANCE_COUNT > 2)
            if (set == kPeripheralEnableIRQ)
            {
                NVIC_EnableIRQ(spi_irq_ids[instance]);
            }
            else
            {
                NVIC_DisableIRQ(spi_irq_ids[instance]);
            }
            break;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : spi_poll_for_activity
 * Description   : Polling for SPI slave activities
 *
 *END**************************************************************************/
bool spi_poll_for_activity(const peripheral_descriptor_t *self)
{
    return s_spiActivity[self->instance];
}

/*FUNCTION**********************************************************************
 *
 * Function Name : spi_data_source
 * Description   : SPI slave sending data function
 *
 *END**************************************************************************/
void spi_data_source(uint8_t *source_byte)
{
    assert(source_byte);

    if (s_spiInfo.bytesToTransfer)
    {
        *source_byte = *s_spiInfo.writeData++;
        s_spiInfo.bytesToTransfer--;
    }
    else
    {
        *source_byte = 0;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : spi_initial_data_sink
 * Description   : SPI slave receiving first byte data function
 *
 *END**************************************************************************/
void spi_initial_data_sink(uint8_t sink_byte, uint16_t instance)
{
    if (sink_byte == kFramingPacketStartByte)
    {
        s_spiActivity[instance] = true;
        s_spiInfo.data_sink = spi_data_sink;
        s_spi_app_data_sink_callback(sink_byte);
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : spi_data_sink
 * Description   : SPI slave receiving data function
 *
 *END**************************************************************************/
void spi_data_sink(uint8_t sink_byte, uint16_t instance)
{
    s_spi_app_data_sink_callback(sink_byte);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : spi_full_init
 * Description   : SPI slave full init function
 *
 *END**************************************************************************/
status_t spi_full_init(const peripheral_descriptor_t *self, serial_byte_receive_func_t function)
{
    s_spi_app_data_sink_callback = function;

    spi_slave_config_t config;
    uint32_t baseAddr = g_spiBaseAddr[self->instance];

    SPI_SlaveGetDefaultConfig(&config);

    config.enableSlave = true;
    config.direction = kSPI_MsbFirst;
    config.polarity = kSPI_ClockPolarityActiveLow;
    config.phase = kSPI_ClockPhaseSecondEdge;

    s_spiInfo.data_source = spi_data_source;
    s_spiInfo.data_sink = spi_initial_data_sink;

    // Configure selected pin as spi peripheral interface
    self->pinmuxConfig(self->instance, kPinmuxType_Peripheral);

    SPI_SlaveInit((SPI_Type *)baseAddr, &config);
    SPI_EnableInterrupts((SPI_Type *)baseAddr, kSPI_RxFullAndModfInterruptEnable | kSPI_TxEmptyInterruptEnable);
    SPI_SetSystemIRQ(self->instance, kPeripheralEnableIRQ);

    s_spiIntialized[self->instance] = true;

    return kStatus_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : spi_full_shutdown
 * Description   : SPI slave full shutdown function
 *
 *END**************************************************************************/
void spi_full_shutdown(const peripheral_descriptor_t *self)
{
    if (s_spiIntialized[self->instance])
    {
        uint32_t baseAddr = g_spiBaseAddr[self->instance];
        SPI_SetSystemIRQ(self->instance, kPeripheralDisableIRQ);
        SPI_Deinit((SPI_Type *)baseAddr);

        // Restore selected pin to default state to reduce IDD.
        self->pinmuxConfig(self->instance, kPinmuxType_Default);

        s_spiIntialized[self->instance] = false;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : spi_write
 * Description   : SPI slave writing data function
 *
 *END**************************************************************************/
status_t spi_write(const peripheral_descriptor_t *self, const uint8_t *buffer, uint32_t byteCount)
{
    s_spiInfo.writeData = buffer;
    s_spiInfo.bytesToTransfer = byteCount;

    while (s_spiInfo.bytesToTransfer)
        ;

    return kStatus_Success;
}

void spi_slave_irq_handler(uint32_t instance)
{
    uint32_t baseAddr = g_spiBaseAddr[instance];

#if USE_ONLY_SPI(0)
    instance = 0;
#elif USE_ONLY_SPI(1)
    instance = 1;
#endif // USE_ONLY_SPI(0)

    if (((SPI_Type *)baseAddr)->S & SPI_S_SPRF_MASK)
    {
        // SPI receive interrupt
        uint8_t rd = ((SPI_Type *)baseAddr)->D;
        s_spiInfo.data_sink(rd, instance);
    }

    if (((SPI_Type *)baseAddr)->S & SPI_S_SPTEF_MASK)
    {
        // SPI transimit interrupt
        uint8_t source_byte = 0;
        s_spiInfo.data_source(&source_byte);

        // Write the data to data register
        ((SPI_Type *)baseAddr)->D = source_byte;
    }
}

#if defined(SPI0)
void SPI0_IRQHandler(void)
{
    spi_slave_irq_handler(0);
}
#endif

#if defined(SPI1)
void SPI1_IRQHandler(void)
{
    spi_slave_irq_handler(1);
}
#endif

#if defined(SPI2)
void SPI2_IRQHandler(void)
{
    spi_slave_irq_handler(2);
}
#endif

//! @}

#endif // BL_CONFIG_SPI
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
