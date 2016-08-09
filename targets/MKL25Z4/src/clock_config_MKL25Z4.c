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
    kClockMode_FBI = 2,
    kClockMode_FBE = 3,
    kClockMode_PEE = 4,
    kClockMode_PBE = 5,
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
#if BL_TARGET_FLASH
    static uint32_t s_defaultClockDivider;
    static target_clock_mode_t s_currentClockMode = kClockMode_FEI;

    if (option == kClockOption_EnterBootloader)
    {
        s_defaultClockDivider = SIM->CLKDIV1;

        // General procedure to be implemented:
        // 1. Read clock flags and divider from bootloader config in property store
        bootloader_configuration_data_t *config = &g_bootloaderContext.propertyInterface->store->configurationData;
        uint8_t options = config->clockFlags;

        // Check if the USB HID peripheral is enabled. If it is enabled, we always
        // use the external OSC.
        bool isUsbEnabled = config->enabledPeripherals & kPeripheralType_USB_HID;

        // 2. If NOT High Speed and USB is NOT enabled, do nothing (use reset clock config)
        if ((options & kClockFlag_HighSpeed) && !isUsbEnabled)
        {
            // High speed flag is set (meaning disabled), so just use default clocks.
            uint32_t coreClockDivider = (((SIM->CLKDIV1 & SIM_CLKDIV1_OUTDIV1_MASK) >> SIM_CLKDIV1_OUTDIV1_SHIFT) + 1);
            SystemCoreClock = kDefaultMcgOutWithoutUsb / coreClockDivider;
            SIM->SOPT2 &=
                (uint32_t)~SIM_SOPT2_PLLFLLSEL_MASK; // USe the FLL clock for various peripheral clocking options.
            return;
        }

        // 3. Set OUTDIV1 based on divider in config. OUTDIV4 starts out at /1.
        // The divider values are masked by the maximum bits per divider.
        uint32_t div1 = ((~config->clockDivider) & (SIM_CLKDIV1_OUTDIV1_MASK >> SIM_CLKDIV1_OUTDIV1_SHIFT)) + 1;
        uint32_t div4 = 1;

        // 4. Calculate MCGOUTCLK
        uint32_t McgOutClk = kDefaultMcgOutkWithUsb;

        // 5. Keep core clock up kMinCoreClockWithUsbSupport if usb is supported.
        uint32_t freq = McgOutClk;
        // If USB is enabled, the CPU clock must not be allowed to go below 20 MHz
        if (isUsbEnabled)
        {
            while ((freq / div1) < kMinCoreClockWithUsbSupport)
            {
                --div1;
            }
        }

        // 6. Keep core clock <= Max supported core clock
        while ((freq / div1) > kMaxCoreClock)
        {
            ++div1;
        }

        // 7. Update SystemCoreClock global.
        assert((div1 >= kDivider1_Min) && (div1 <= kDivider1_Max));
        SystemCoreClock = McgOutClk / div1;

        // 8. Keep bus freq below max.
        //
        // The bus clock is divided by OUTDIV4 in addition to OUTDIV1:
        //      MCGOUTCLK -> OUTDIV1 -> OUTDIV4 -> bus_clk
        freq = SystemCoreClock;
        while ((freq / div4) > kMaxBusClock)
        {
            // Increase bus/flash clock divider.
            ++div4;
        }
        assert((div4 >= kDivider4_Min) && (div4 <= kDivider4_Max));

        // 9. Now set the dividers
        SIM->CLKDIV1 = SIM_CLKDIV1_OUTDIV1(div1 - 1) | SIM_CLKDIV1_OUTDIV4(div4 - 1); /* Update system prescalers */

        // Switch to PEE mode
        clock_mode_switch(s_currentClockMode, kClockMode_PEE);

        s_currentClockMode = kClockMode_PEE;
    }
    else if (option == kClockOption_ExitBootloader)
    {
        // Restore from PEE mode to FEI mode
        clock_mode_switch(s_currentClockMode, kClockMode_FEI);

        // Restore clock divider
        SIM->CLKDIV1 = s_defaultClockDivider;
    }

#endif // BL_TARGET_FLASH
}

void clock_mode_switch(const target_clock_mode_t currentMode, const target_clock_mode_t expectedMode)
{
    // Note: here only implements clock switch between FEI and PEE,
    // The other modes are not supported.
    assert(currentMode == kClockMode_PEE || currentMode == kClockMode_FEI);
    assert(expectedMode == kClockMode_PEE || expectedMode == kClockMode_FEI);

    if (currentMode == expectedMode)
    {
        return;
    }

    if (expectedMode == kClockMode_PEE)
    {
        /* SIM->SCGC5: PORTA=1 */
        SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK; /* Enable clock gate for ports to enable pin routing */
        /* PORTA->PCR18: ISF=0,MUX=0 */
        PORTA->PCR[18] &= (uint32_t)~0x01000700UL;
        /* PORTA->PCR19: ISF=0,MUX=0 */
        PORTA->PCR[19] &= (uint32_t)~0x01000700UL;
        /* Switch to FBE Mode */
        /* OSC0->CR: ERCLKEN=1,??=0,EREFSTEN=0,??=0,SC2P=1,SC4P=0,SC8P=0,SC16P=1 */
        OSC0->CR = (uint8_t)0x89U;
        /* MCG->C2: LOCRE0=0,??=0,RANGE0=2,HGO0=0,EREFS0=1,LP=0,IRCS=0 */
        MCG->C2 = (uint8_t)0x24U;
        /* MCG->C1: CLKS=2,FRDIV=3,IREFS=0,IRCLKEN=1,IREFSTEN=0 */
        MCG->C1 = (uint8_t)0x9AU;
        /* MCG->C4: DMX32=0,DRST_DRS=0 */
        MCG->C4 &= (uint8_t) ~(uint8_t)0xE0U;
        /* MCG->C5: ??=0,PLLCLKEN0=0,PLLSTEN0=0,PRDIV0=1 */
        MCG->C5 = (uint8_t)0x01U;
        /* MCG->C6: LOLIE0=0,PLLS=0,CME0=0,VDIV0=0 */
        MCG->C6 = (uint8_t)0x00U;
        while ((MCG->S & MCG_S_IREFST_MASK) != 0x00U)
        { /* Check that the source of the FLL reference clock is the external reference clock. */
        }
        while ((MCG->S & 0x0CU) != 0x08U)
        { /* Wait until external reference clock is selected as MCG output */
        }
        /* Switch to PBE Mode */
        /* MCG->C6: LOLIE0=0,PLLS=1,CME0=0,VDIV0=0 */
        MCG->C6 = (uint8_t)0x40U;
        while ((MCG->S & 0x0CU) != 0x08U)
        { /* Wait until external reference clock is selected as MCG output */
        }
        while ((MCG->S & MCG_S_LOCK0_MASK) == 0x00U)
        { /* Wait until locked */
        }
        /* Switch to PEE Mode */
        /* MCG->C1: CLKS=0,FRDIV=3,IREFS=0,IRCLKEN=1,IREFSTEN=0 */
        MCG->C1 = (uint8_t)0x1AU;
        while ((MCG->S & 0x0CU) != 0x0CU)
        { /* Wait until output of the PLL is selected */
        }
    }
    else if (expectedMode == kClockMode_FEI)
    {
        /* Switch to PBE mode */
        /* MCG->C1: CLKS=2,FRDIV=3,IREFS=0,IRCLKEN=1,IREFSTEN=0 */
        MCG->C1 = (uint8_t)0x9AU;
        /* MCG->C6: LOLIE0=0,PLLS=1,CME0=0,VDIV0=0 */
        MCG->C6 = (uint8_t)0x40U;
        /* MCG->C2: LOCRE0=0,??=0,RANGE0=2,HGO0=0,EREFS0=1,LP=0,IRCS=0 */
        MCG->C2 = (uint8_t)0x24U;
        while ((MCG->S & 0x0CU) != 0x08U) /* Wait until external reference clock is selected */
        {
        }

        /* Switch to FBE mode */
        /* MCG->C6: LOLIE0=0,PLLS=0,CME0=0,VDIV0=0 */
        MCG->C6 = (uint8_t)0x00U;

        while ((MCG->S & MCG_S_PLLST_MASK) != 0x00U) /* Wait until source of PLLS clock is FLL clock */
        {
        }

        /* Switch to FEI mode */
        /* MCG->C1: CLKS=0,FRDIV=3,IREFS=1,IRCLKEN=1,IREFSTEN=0 */
        MCG->C1 = (uint8_t)0x1EU;
        while ((MCG->S & MCG_S_IREFST_MASK) == 0x0U)
        {
        }

        while ((MCG->S & 0x0CU) != 0x00U) /* Wait until output of FLL is selected */
        {
        }

        OSC0->CR = (uint8_t)0x0U;
        while ((MCG->S & MCG_S_OSCINIT0_MASK) != 0x00U) /* Wait until OSC is off */
        {
        }

        /* Restore Registers */
        /* MCG->C2: LOCRE0=1,??=0,RANGE0=0,HGO0=0,EREFS0=0,LP=0,IRCS=0 */
        MCG->C2 = (uint8_t)0x80U;
        MCG->C1 = (uint8_t)0x04U;
        MCG->C5 = (uint8_t)0x00U;
    }
}

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
