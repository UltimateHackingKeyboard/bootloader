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

#include <stdint.h>
#include "system_MKL25Z4.h"
#include "fsl_device_registers.h"
#include "target_config.h"

#ifndef DISABLE_WDOG
#define DISABLE_WDOG 0
#endif

/* ----------------------------------------------------------------------------
   -- Core clock
   ---------------------------------------------------------------------------- */

uint32_t SystemCoreClock = kDefaultMcgOutWithoutUsb;

/* ----------------------------------------------------------------------------
   -- SystemInit()
   ---------------------------------------------------------------------------- */

void SystemInit(void)
{
#if (DISABLE_WDOG)
    /* Disable the WDOG module */
    /* SIM_COPC: COPT=0,COPCLKS=0,COPW=0 */
    SIM->COPC = (uint32_t)0x00u;
#endif /* (DISABLE_WDOG) */
}

uint32_t GetSystemMCGPLLClock(void)
{
#if (CLOCK_SETUP == 0)
    // 0 ... Multipurpose Clock Generator (MCG) in FLL Engaged Internal (FEI) mode
    //       Reference clock source for MCG module is the slow internal clock source 32.768kHz
    //       Core clock = 41.94MHz, BusClock = 13.98MHz
    // FLL engaged internal (FEI) is the default mode of operation and is entered when all the following
    //     condtions occur:
    //     • C1[CLKS] bits are written to 00
    //     • C1[IREFS] bit is written to 1
    //     • C6[PLLS] bit is written to 0
    //     In FEI mode, MCGOUTCLK is derived from the FLL clock (DCOCLK) that is controlled by the 32
    //     kHz Internal Reference Clock (IRC). The FLL loop will lock the DCO frequency to the FLL factor, as
    //     selected by C4[DRST_DRS] and C4[DMX32] bits, times the internal reference frequency. See the
    //     C4[DMX32] bit description for more details. In FEI mode, the PLL is disabled in a low-power state
    //     unless C5[PLLCLKEN0] is set.
    // MCG->C1 = (uint8_t)0x06U; IREFS = 1 IRCLKEN = 1, slow interal clock selected
    // MCG->C2 = (uint8_t)0x00U;
    // MCG->C4 = (uint8_t)((MCG->C4 & (uint8_t)~(uint8_t)0xC0U) | (uint8_t)0x20U); DRST_DRS = 1, DMX32 = 0 FLL Factor =
    // 1280
    // MCG->C5 = (uint8_t)0x00U; PLL Disabled
    // MCG->C6 = (uint8_t)0x00U; FLL Selected

    return 0;

#elif(CLOCK_SETUP == 1)
    // 1 ... Multipurpose Clock Generator (MCG) in PLL Engaged External (PEE) mode
    //       Reference clock source for MCG module is an external crystal 8MHz
    //       Core clock = 48MHz, BusClock = 24MHz
    // PLL Engaged External (PEE) mode is entered when all the following conditions occur:
    //     • C1[CLKS] bits are written to 00
    //     • C1[IREFS] bit is written to 0
    //     • C6[PLLS] bit is written to 1
    //     In PEE mode, the MCGOUTCLK is derived from the PLL clock, which is controlled by the external
    //     reference clock. The PLL clock frequency locks to a multiplication factor, as specified by C6[VDIV0],
    //               times the external reference frequency, as specified by C5[PRDIV0]. The PLL's programmable
    //                   reference divider must be configured to produce a valid PLL reference clock. The FLL is
    //                   disabled in
    //                   a low-power state.
    // MCG->C2: LOCRE0=0,??=0,RANGE0=2,HGO0=0,EREFS0=1,LP=0,IRCS=0
    // MCG->C1: CLKS=2,FRDIV=3,IREFS=0,IRCLKEN=1,IREFSTEN=0
    // MCG->C4: DMX32=0,DRST_DRS=0
    // MCG->C5: ??=0,PLLCLKEN0=0,PLLSTEN0=0,PRDIV0=1
    // MCG->C6: LOLIE0=0,PLLS=0,CME0=0,VDIV0=0
    // MCG->C6: LOLIE0=0,PLLS=1,CME0=0,VDIV0=0
    // MCG->C1: CLKS=0,FRDIV=3,IREFS=0,IRCLKEN=1,IREFSTEN=0
    // C6[VDIV0] = 24x
    // C5[PRDIV0] = /2
    // MCG PLL output then /2 again

    return (((CPU_XTAL_CLK_HZ * 24) / 2) / 2);

#elif(CLOCK_SETUP == 2)
    // 2 ... Multipurpose Clock Generator (MCG) in Bypassed Low Power External (BLPE) mode
    //       Core clock/Bus clock derived directly from an external crystal 8MHz with no multiplication
    //       Core clock = 8MHz, BusClock = 8MHz
    // Bypassed Low Power External (BLPE) mode is entered when all the following conditions occur:
    //     • C1[CLKS] bits are written to 10
    //     • C1[IREFS] bit is written to 0
    //     • C2[LP] bit is written to 1
    //     In BLPE mode, MCGOUTCLK is derived from the external reference clock. The FLL is disabled and
    //     PLL is disabled even if the C5[PLLCLKEN0] is set to 1.

    return 0;

#endif // (CLOCK_SETUP == 2)
}

uint32_t GetSystemMCGFLLClock(void)
{
#if (CLOCK_SETUP == 0)
    // 0 ... Multipurpose Clock Generator (MCG) in FLL Engaged Internal (FEI) mode
    //       Reference clock source for MCG module is the slow internal clock source 32.768kHz
    //       Core clock = 41.94MHz, BusClock = 13.98MHz
    // MCG->C1 = (uint8_t)0x06U; IREFS = 1 IRCLKEN = 1, slow interal clock selected
    // MCG->C2 = (uint8_t)0x00U;
    // MCG->C4 = (uint8_t)((MCG->C4 & (uint8_t)~(uint8_t)0xC0U) | (uint8_t)0x20U); DRST_DRS = 1, DMX32 = 0 FLL Factor =
    // 1280
    // MCG->C5 = (uint8_t)0x00U; PLL Disabled
    // MCG->C6 = (uint8_t)0x00U; FLL Selected

    return (CPU_INT_SLOW_CLK_HZ * 1280);

#elif(CLOCK_SETUP == 1)
    // FLL Clock disabled

    return 0;

#elif(CLOCK_SETUP == 2)
    // 2 ... Multipurpose Clock Generator (MCG) in Bypassed Low Power External (BLPE) mode
    //       Core clock/Bus clock derived directly from an external crystal 8MHz with no multiplication
    //       Core clock = 8MHz, BusClock = 8MHz
    // Bypassed Low Power External (BLPE) mode is entered when all the following conditions occur:
    //     • C1[CLKS] bits are written to 10
    //     • C1[IREFS] bit is written to 0
    //     • C2[LP] bit is written to 1
    //     In BLPE mode, MCGOUTCLK is derived from the external reference clock. The FLL is disabled and
    //     PLL is disabled even if the C5[PLLCLKEN0] is set to 1.

    return 0;

#endif // (CLOCK_SETUP == 2)
}

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
