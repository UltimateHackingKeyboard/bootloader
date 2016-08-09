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

#include "bootloader/bl_context.h"
#include "bootloader_common.h"
#include "autobaud/autobaud.h"
#include "packet/serial_packet.h"
#include "fsl_device_registers.h"
#include "lpsci/fsl_lpsci.h"
#include "utilities/fsl_assert.h"

#if BL_CONFIG_UART

//! @addtogroup uart0_peripheral
//! @{

////////////////////////////////////////////////////////////////////////////////
// Prototypes
////////////////////////////////////////////////////////////////////////////////

static bool uart0_poll_for_activity(const peripheral_descriptor_t *self);
static status_t uart0_full_init(const peripheral_descriptor_t *self, serial_byte_receive_func_t function);
static void uart0_full_shutdown(const peripheral_descriptor_t *self);

static status_t uart0_write(const peripheral_descriptor_t *self, const uint8_t *buffer, uint32_t byteCount);

static const uint32_t g_lpsciBaseAddr[] = UART0_BASE_ADDRS;

////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////

const peripheral_control_interface_t g_uart0ControlInterface = {
    .pollForActivity = uart0_poll_for_activity, .init = uart0_full_init, .shutdown = uart0_full_shutdown, .pump = 0
};

const peripheral_byte_inteface_t g_uart0ByteInterface = {.init = NULL, .write = uart0_write };

static serial_byte_receive_func_t s_uart0_byte_receive_callback;
static bool s_uart0_init = false;

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////

uint32_t uart0_get_clock(uint32_t instance)
{
    switch (instance)
    {
        case 0:
        {
            uint32_t coreClockDivider = ((SIM->CLKDIV1 & SIM_CLKDIV1_OUTDIV1_MASK) >> SIM_CLKDIV1_OUTDIV1_SHIFT) + 1;
            uint32_t McgOutClk = SystemCoreClock * coreClockDivider;

            // if PLL/2 is the UART0 clock
            if (MCG->S & MCG_S_PLLST_MASK)
            {
                return McgOutClk / 2;
            }
            else
            {
                return McgOutClk;
            }
        }
        case 1:
        {
            // UART1 always uses the system clock / OUTDIV4
            const uint32_t busClockDivider =
                ((SIM->CLKDIV1 & SIM_CLKDIV1_OUTDIV4_MASK) >> SIM_CLKDIV1_OUTDIV4_SHIFT) + 1;
            return (SystemCoreClock / busClockDivider);
        }
        case 2:
        {
            // UART2 always uses the system clock / OUTDIV4
            uint32_t busClockDivider = ((SIM->CLKDIV1 & SIM_CLKDIV1_OUTDIV4_MASK) >> SIM_CLKDIV1_OUTDIV4_SHIFT) + 1;
            return (SystemCoreClock / busClockDivider);
        }
        default:
            return 0;
    }
}

bool uart0_poll_for_activity(const peripheral_descriptor_t *self)
{
    uint32_t baud;
    status_t autoBaudCompleted = autobaud_get_rate(self->instance, &baud);

    if (autoBaudCompleted == kStatus_Success)
    {
        lpsci_config_t config;
        uint32_t baseAddr = g_lpsciBaseAddr[self->instance];

        LPSCI_GetDefaultConfig(&config);

        config.baudRate_Bps = baud;
        config.enableRx = true;
        config.enableTx = true;

        if (LPSCI_Init((UART0_Type *)baseAddr, &config, uart0_get_clock(self->instance)) == kStatus_Success)
        {
            LPSCI_EnableInterrupts((UART0_Type *)baseAddr, kLPSCI_RxDataRegFullInterruptEnable);
            NVIC_EnableIRQ(UART0_IRQn);

            // Configure selected pin as uart peripheral interface
            self->pinmuxConfig(self->instance, kPinmuxType_Peripheral);

            // This was the byte pattern identified in autobaud detection, inform the command layer
            s_uart0_byte_receive_callback(kFramingPacketStartByte);
            s_uart0_byte_receive_callback(kFramingPacketType_Ping);

            s_uart0_init = true;

            return true;
        }
        else
        {
            autobaud_init(self->instance);
        }
    }

    return false;
}

status_t uart0_full_init(const peripheral_descriptor_t *self, serial_byte_receive_func_t function)
{
    s_uart0_byte_receive_callback = function;

    // Since we are using autobaud once the detection is completed
    // it will call the UART initialization and remux the pins when it completes
    self->pinmuxConfig(self->instance, kPinmuxType_GPIO);

    // Init autobaud detector.
    autobaud_init(self->instance);

    return kStatus_Success;
}

void uart0_full_shutdown(const peripheral_descriptor_t *self)
{
    uint32_t baseAddr = g_lpsciBaseAddr[self->instance];

    if (s_uart0_init)
    {
        LPSCI_DisableInterrupts((UART0_Type *)baseAddr, UART0_C2_RIE_MASK);
        LPSCI_Deinit((UART0_Type *)baseAddr);
        NVIC_DisableIRQ(UART0_IRQn);
        s_uart0_init = false;
    }
//! Note: if not deinit autobaud(IRQ method), user app may encounters hardfault
//! if it doesn't provide related pin interrupt service routine.
#if BL_FEATURE_UART_AUTOBAUD_IRQ
    // De-init autobaud detector.
    autobaud_deinit(self->instance);
#endif
    // Restore selected pin to default state to reduce IDD.
    self->pinmuxConfig(self->instance, kPinmuxType_Default);
}

status_t uart0_write(const peripheral_descriptor_t *self, const uint8_t *buffer, uint32_t byteCount)
{
    uint32_t baseAddr = g_lpsciBaseAddr[self->instance];

    LPSCI_TransferSendBlocking((UART0_Type *)baseAddr, buffer, byteCount);

    return kStatus_Success;
}

/********************************************************************/
/*
 * UART0 IRQ Handler
 *
 */
void UART0_IRQHandler(void)
{
    s_uart0_byte_receive_callback(UART0->D);
}

//! @}

#endif // BL_CONFIG_UART

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
