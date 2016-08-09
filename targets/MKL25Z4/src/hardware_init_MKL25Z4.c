/*
 * Copyright (c) 2013-2015, Freescale Semiconductor, Inc.
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

#include "bootloader_common.h"
#include "bootloader/bl_context.h"
#include "fsl_device_registers.h"
#include "uart/fsl_uart.h"
#include "drivers/systick/systick.h"
#include "drivers/watchdog/fsl_watchdog.h"
#include "utilities/fsl_rtos_abstraction.h"
#include "smc/smc.h"

////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////

#define BOOT_PIN_NUMBER 3
#define BOOT_PIN_PORT PORTC
#define BOOT_PIN_GPIO GPIOC
#define BOOT_PIN_ALT_MODE 1
#define BOOT_PIN_DEBOUNCE_READ_COUNT 500

////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////

void init_hardware(void)
{
    exit_vlpr();

    SIM->SCGC5 |= (SIM_SCGC5_PORTA_MASK | SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTC_MASK | SIM_SCGC5_PORTD_MASK |
                   SIM_SCGC5_PORTE_MASK);

    SIM->SOPT2 = SIM_SOPT2_PLLFLLSEL_MASK // set PLLFLLSEL to select the PLL for this clock source
                 | SIM_SOPT2_UART0SRC(1); // select the PLLFLLCLK as UART0 clock source

#if DEBUG
    // Enable the pins for the debug UART1
    PORTC->PCR[3] = PORT_PCR_MUX(3); // UART1_RX is PTC3 in ALT3
    PORTC->PCR[4] = PORT_PCR_MUX(3); // UART1_TX is PTC4 in ALT3
#endif
}

void deinit_hardware(void)
{
    SIM->SCGC5 &= (uint32_t) ~(SIM_SCGC5_PORTA_MASK | SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTC_MASK |
                               SIM_SCGC5_PORTD_MASK | SIM_SCGC5_PORTE_MASK);

    // Restore SIM_SOPTx related bits being changed
    SIM->SOPT1 &= (uint32_t) ~(SIM_SOPT1_USBREGEN_MASK);
    SIM->SOPT2 &= (uint32_t) ~(SIM_SOPT2_UART0SRC_MASK | SIM_SOPT2_USBSRC_MASK | SIM_SOPT2_PLLFLLSEL_MASK);
}

uint32_t get_bus_clock(void)
{
    uint32_t busClockDivider = ((SIM->CLKDIV1 & SIM_CLKDIV1_OUTDIV4_MASK) >> SIM_CLKDIV1_OUTDIV4_SHIFT) + 1;
    return SystemCoreClock / busClockDivider;
}

// Keep this function here to ensure compatibility, all usb related configuration
// is maintained by usb stack itself.
bool usb_clock_init(void)
{
    SIM->SCGC4 |= SIM_SCGC4_USBOTG_MASK;
    SIM->SOPT2 |= (SIM_SOPT2_USBSRC_MASK | SIM_SOPT2_PLLFLLSEL_MASK);

    SIM->SOPT1CFG |= SIM_SOPT1CFG_URWE_MASK;
    SIM->SOPT1 |= SIM_SOPT1_USBREGEN_MASK;
    /* reset USB CTRL register */
    USB0->USBCTRL = 0;

    /* Enable internal pull-up resistor */
    USB0->CONTROL = USB_CONTROL_DPPULLUPNONOTG_MASK;
    USB0->USBTRC0 |= 0x40; /* Software must set this bit to 1 */
    return true;
}

uint32_t get_uart_clock(uint32_t instance)
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

bool is_boot_pin_asserted(void)
{
#if defined(BL_TARGET_FLASH) & !defined(FREEDOM)
    // Initialize boot pin for GPIO
    BOOT_PIN_PORT->PCR[BOOT_PIN_NUMBER] |= PORT_PCR_MUX(BOOT_PIN_ALT_MODE);

    // Set boot pin as an input
    BOOT_PIN_GPIO->PDDR &= (uint32_t) ~(1 << BOOT_PIN_NUMBER);
    // Set boot pin pullup enabled, pullup select, filter enable
    BOOT_PIN_PORT->PCR[BOOT_PIN_NUMBER] |= (PORT_PCR_PE_MASK | PORT_PCR_PS_MASK | PORT_PCR_PFE_MASK);

    uint32_t readCount = 0;

    // Sample the pin a number of times
    for (uint32_t i = 0; i < BOOT_PIN_DEBOUNCE_READ_COUNT; i++)
    {
        readCount += ((BOOT_PIN_GPIO->PDIR) >> BOOT_PIN_NUMBER) & 1;
    }

    // boot pin is pulled high so we are measuring lows, make sure most of our measurements
    // registered as low
    return (readCount < (BOOT_PIN_DEBOUNCE_READ_COUNT / 2));
#else
    // Boot pin for Flash only target
    return false;
#endif
}

void dummy_byte_callback(uint8_t byte)
{
    (void)byte;
}

void update_available_peripherals()
{
}

// @brief Initialize watchdog
void bootloader_watchdog_init(void)
{
    systick_init(SystemCoreClock / 64);
    systick_set_hook(bootloader_watchdog_service);
}

void bootloader_watchdog_service(void)
{
    lock_acquire();
    fsl_watchdog_service();
    lock_release();
}

void bootloader_watchdog_deinit(void)
{
    systick_shutdown();
}

#if __ICCARM__

size_t __write(int handle, const unsigned char *buf, size_t size)
{
    return size;
}

#endif // __ICCARM__

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
