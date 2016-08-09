/*
 * Copyright (c) 2014, Freescale Semiconductor, Inc.
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
#include "bootloader/bl_peripheral_interface.h"
#include "packet/serial_packet.h"

extern void uart_pinmux_config(uint32_t instance, pinmux_type_t pinmux);
extern void i2c_pinmux_config(uint32_t instance, pinmux_type_t pinmux);
extern void spi_pinmux_config(uint32_t instance, pinmux_type_t pinmux);
////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////

#if !BL_CONFIG_LPUART && !BL_CONFIG_I2C && !BL_CONFIG_DSPI && !BL_CONFIG_USB_HID
#error At least one peripheral must be enabled!
#endif

//! @brief Peripheral array for KL25Z4.
const peripheral_descriptor_t g_peripherals[] = {
#if BL_CONFIG_LPUART_0
    // LPUART0
    {.typeMask = kPeripheralType_UART,
     .instance = 0,
     .pinmuxConfig = uart_pinmux_config,
     .controlInterface = &g_lpuartControlInterface,
     .byteInterface = &g_lpuartByteInterface,
     .packetInterface = &g_framingPacketInterface },
#endif // BL_CONFIG_LPUART_0
#if BL_CONFIG_LPUART_1
    // LPUART1
    {.typeMask = kPeripheralType_UART,
     .instance = 1,
     .pinmuxConfig = uart_pinmux_config,
     .controlInterface = &g_lpuartControlInterface,
     .byteInterface = &g_lpuartByteInterface,
     .packetInterface = &g_framingPacketInterface },
#endif // BL_CONFIG_LPUART_1
#if BL_CONFIG_LPUART_2
    // LPUART2
    {.typeMask = kPeripheralType_UART,
     .instance = 2,
     .pinmuxConfig = uart_pinmux_config,
     .controlInterface = &g_lpuartControlInterface,
     .byteInterface = &g_lpuartByteInterface,
     .packetInterface = &g_framingPacketInterface },
#endif // BL_CONFIG_LPUART_2
#if BL_CONFIG_LPUART_4
    // LPUART4
    {.typeMask = kPeripheralType_UART,
     .instance = 4,
     .pinmuxConfig = uart_pinmux_config,
     .controlInterface = &g_lpuartControlInterface,
     .byteInterface = &g_lpuartByteInterface,
     .packetInterface = &g_framingPacketInterface },
#endif // BL_CONFIG_LPUART_4

#if BL_CONFIG_I2C_0
    // I2C0
    {.typeMask = kPeripheralType_I2CSlave,
     .instance = 0,
     .pinmuxConfig = i2c_pinmux_config,
     .controlInterface = &g_i2cControlInterface,
     .byteInterface = &g_i2cByteInterface,
     .packetInterface = &g_framingPacketInterface },
#endif // BL_CONFIG_I2C_0

#if BL_CONFIG_I2C_1
    // I2C1
    {.typeMask = kPeripheralType_I2CSlave,
     .instance = 1,
     .pinmuxConfig = i2c_pinmux_config,
     .controlInterface = &g_i2cControlInterface,
     .byteInterface = &g_i2cByteInterface,
     .packetInterface = &g_framingPacketInterface },
#endif // BL_CONFIG_I2C_1

#if BL_CONFIG_DSPI_0
    // SPI0
    {.typeMask = kPeripheralType_SPISlave,
     .instance = 0,
     .pinmuxConfig = spi_pinmux_config,
     .controlInterface = &g_dspiControlInterface,
     .byteInterface = &g_dspiByteInterface,
     .packetInterface = &g_framingPacketInterface },
#endif // BL_CONFIG_DSPI_0
#if BL_CONFIG_DSPI_1
    // SPI1
    {.typeMask = kPeripheralType_SPISlave,
     .instance = 1,
     .pinmuxConfig = spi_pinmux_config,
     .controlInterface = &g_dspiControlInterface,
     .byteInterface = &g_dspiByteInterface,
     .packetInterface = &g_framingPacketInterface },
#endif // BL_CONFIG_DSPI_1
#if (BL_CONFIG_USB_HID || BL_CONFIG_USB_MSC)
    // USB HID
    {.typeMask = kPeripheralType_USB_HID,
     .instance = 0,
     .pinmuxConfig = NULL,
     .controlInterface = &g_usbHidControlInterface,
     .byteInterface = NULL,
     .packetInterface = &g_usbHidPacketInterface },
#endif    // BL_CONFIG_USB_HID
    { 0 } // Terminator
};

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
