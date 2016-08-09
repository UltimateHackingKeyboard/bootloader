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
#include <assert.h>

////////////////////////////////////////////////////////////////////////////////
// Declarations
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////

// See bootloader_common.h for documentation on this function.
void configure_clocks(bootloader_clock_option_t option)
{
#if BL_TARGET_FLASH

    static uint32_t s_defaultClockDivider;
    if (option == kClockOption_EnterBootloader)
    {
        s_defaultClockDivider = SIM->CLKDIV1;

        // General procedure to be implemented:
        // 1. Read clock flags and divider from bootloader config in property store
        bootloader_configuration_data_t *config = &g_bootloaderContext.propertyInterface->store->configurationData;
        uint8_t options = config->clockFlags;

        // 2. If NOT High Speed, do nothing (use reset clock config)
        if (options & kClockFlag_HighSpeed)
        {
            // High speed flag is set (meaning disabled), so just use default clocks.
            uint32_t coreClockDivider = (((SIM->CLKDIV1 & SIM_CLKDIV1_OUTDIV1_MASK) >> SIM_CLKDIV1_OUTDIV1_SHIFT) + 1);
            SystemCoreClock = kDefaultClock / coreClockDivider;
            return;
        }

        // 3. Set OUTDIV1 based on divider in config. OUTDIV4 starts out at /1.
        // The divider values are masked by the maximum bits per divider.
        uint32_t div1 = ((~config->clockDivider) & (SIM_CLKDIV1_OUTDIV1_MASK >> SIM_CLKDIV1_OUTDIV1_SHIFT)) + 1;

        // 4. Get MCGOUTCLK
        uint32_t McgOutClk = kDefaultClock;

        // 5. Keep core clock up kMinCoreClockWithUsbSupport if usb is supported.
        uint32_t freq = McgOutClk;

        // 6. Keep core clock below kMaxCoreClock
        while ((freq / div1) > kMaxCoreClock)
        {
            ++div1;
        }

        assert((div1 >= kDivider_Min) && (div1 <= kDivider_Max));

        uint32_t div4 = ((SIM->CLKDIV1 & SIM_CLKDIV1_OUTDIV4_MASK) >> SIM_CLKDIV1_OUTDIV4_SHIFT) + 1;

        // 7. Keep bus freq/falsh freq below max.
        //
        // The bus/flash clock is (MCGOUTCLK/OUTDIV1/)OUTDIV4:
        //      MCGOUTCLK /div1 -> OUTDIV4 -> bus_clk
        freq = McgOutClk / div1;
        while ((freq / div4) > kMaxBusClock)
        {
            // Increase bus clock divider.
            ++div4;
        }
        assert((div4 >= kDivider_Min) && (div4 <= (kDivider_Max / 2)));

        if ((div1 == 1) && (div4 > 8))
        {
            return;
        }

        // 9. Now set the dividers
        SIM->CLKDIV1 = SIM_CLKDIV1_OUTDIV1(div1 - 1) | SIM_CLKDIV1_OUTDIV4(div4 - 1); // Update system prescalers

        // 10. Update SystemCoreClock global.
        SystemCoreClock = McgOutClk / div1;
    }
    else if (option == kClockOption_ExitBootloader)
    {
        SIM->CLKDIV1 = s_defaultClockDivider;
    }

#endif // BL_TARGET_FLASH
}

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
