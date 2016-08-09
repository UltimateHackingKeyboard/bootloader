/*
 * Copyright (c) 2014-2015, Freescale Semiconductor, Inc.
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
#include "property/property.h"
#include "fsl_device_registers.h"
#include "utilities/fsl_assert.h"

////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////

// Clock mode types
typedef enum _target_clock_mode
{
    kClockMode_FEI = 0,
    kClockMode_FEE = 1,
    kClockMode_Default = kClockMode_FEI,
} target_clock_mode_t;

////////////////////////////////////////////////////////////////////////////////
// Prototypes
////////////////////////////////////////////////////////////////////////////////

// This function implements clock mode switch between FEI and PEE mode used in this bootloader
void clock_mode_switch(const target_clock_mode_t currentMode, const target_clock_mode_t expectedMode);

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////

// See bootloader_common.h for documentation on this function.
void configure_clocks(bootloader_clock_option_t option)
{
#if defined(BL_TARGET_FLASH)

    static target_clock_mode_t s_currentClockMode = kClockMode_FEI;
    static uint32_t s_defaultClockDivider;

    if (option == kClockOption_EnterBootloader)
    {
        s_defaultClockDivider = SIM->CLKDIV1;

        // General procedure to be implemented:
        // 1. Read clock flags and divider from bootloader config in property store
        bootloader_configuration_data_t *config = &g_bootloaderContext.propertyInterface->store->configurationData;
        uint8_t options = config->clockFlags;

        // Check if the USB HID or CAN peripheral is enabled. If it is enabled, we always
        // use the 48MHz IRC.
        bool isUsbEnabled = config->enabledPeripherals & kPeripheralType_USB_HID;
        bool isCanEnabled = config->enabledPeripherals & kPeripheralType_CAN;

        // 2. Keep default clock if CAN, USB and HighSpeed Flag are not enabled.
        if ((options & kClockFlag_HighSpeed) && (!isUsbEnabled) && (!isCanEnabled))
        {
            // Get actual Core clock.
            SystemCoreClock =
                kDefaultClock / (((SIM->CLKDIV1 & SIM_CLKDIV1_OUTDIV1_MASK) >> SIM_CLKDIV1_OUTDIV1_SHIFT) + 1);

            // High speed flag is set (meaning disabled), so just use default clocks.
            return;
        }

        // 3. Set OUTDIV1 based on divider in config. OUTDIV4 starts out at /1.
        // The divider values are masked by the maximum bits per divider.
        uint32_t div1 = ((~config->clockDivider) & (SIM_CLKDIV1_OUTDIV1_MASK >> SIM_CLKDIV1_OUTDIV1_SHIFT)) + 1;

        // 4. Get MCGOUTCLK
        uint32_t McgOutClk = kHIRC;

        // If USB is enabled, the CPU clock must not be allowed to go below 20 MHz
        if (isUsbEnabled || isCanEnabled)
        {
            div1 = 1;
        }
        uint32_t div2 = div1;
        uint32_t div4 = (div1 < 2) ? 2 : div1;

        // 6. Now set the dividers
        SIM->CLKDIV1 = SIM_CLKDIV1_OUTDIV1(div1 - 1) | SIM_CLKDIV1_OUTDIV2(div2 - 1) |
                       SIM_CLKDIV1_OUTDIV4(div4 - 1); /* Update system prescalers */

        // 7. Update SystemCoreClock global.
        SystemCoreClock = McgOutClk / div1;

        clock_mode_switch(s_currentClockMode, kClockMode_FEE);
        s_currentClockMode = kClockMode_FEE;
    }
    else if (option == kClockOption_ExitBootloader)
    {
        // Restore from FEE mode to FEI mode
        clock_mode_switch(s_currentClockMode, kClockMode_FEI);

        // Restore clock divider
        SIM->CLKDIV1 = s_defaultClockDivider;
    }

#endif // BL_TARGET_FLASH
}

void clock_mode_switch(const target_clock_mode_t currentMode, const target_clock_mode_t expectedMode)
{
    // Note: here only implements clock switch between FEI and FEE,
    // The other modes are not supported.
    assert(currentMode == kClockMode_FEE || currentMode == kClockMode_FEI);
    assert(expectedMode == kClockMode_FEE || expectedMode == kClockMode_FEI);

    if (currentMode == expectedMode)
    {
        return;
    }

    if (expectedMode == kClockMode_FEE)
    {
        /* Switch to FEE mode */
        MCG->C7 = 2; // Select IRC48M as OSC
        // Wait about 50us until the OSCSEL switch completes.
        for (volatile uint32_t delayCnt = 0; delayCnt < 2000; delayCnt++)
        {
            __ASM("nop");
        }
        /* CLKS=0, FRDIV=6, IREFS=0, IRCLKEN=0, IREFSTEN=0 */
        MCG->C1 = 0x30u;
        // Wait until external reference clock is ready.
        while ((MCG->S & MCG_S_IREFST_MASK) == MCG_S_IREFST_MASK)
        {
        }

        // Multiply with 1280, MCGOUTCLK is 48Mhz
        uint8_t c4_val;
        c4_val = MCG->C4;
        c4_val &= (uint8_t) ~(MCG_C4_DRST_DRS_MASK | MCG_C4_DMX32_MASK);
        c4_val |= MCG_C4_DRST_DRS(1);
        MCG->C4 = c4_val;

        // Wait about 1ms until the clock frequency is stable.
        for (volatile uint32_t delayCnt = 0; delayCnt < 16000; delayCnt++)
        {
            __ASM("nop");
        }
    }
    else if (expectedMode == kClockMode_FEI)
    {
        MCG->C1 |= MCG_C1_IREFS_MASK; // Switch to internal reference clock.
        // Wait until Internal reference clock is ready.
        while ((MCG->S & MCG_S_IREFST_MASK) != MCG_S_IREFST_MASK)
        {
        }

        // Restore C7 to default
        MCG->C7 = 0;
        // Wait about 50us until the OSCSEL switch completes.
        for (volatile uint32_t delayCnt = 0; delayCnt < 2000; delayCnt++)
        {
            __ASM("nop");
        }
        // Restore Registers to default.
        MCG->C1 = 0x04;
        MCG->C4 &= (uint8_t) ~(MCG_C4_DRST_DRS_MASK);

        // Wait about 1ms until the clock frequency is stable.
        for (volatile uint32_t delayCnt = 0; delayCnt < 16000; delayCnt++)
        {
            __ASM("nop");
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
