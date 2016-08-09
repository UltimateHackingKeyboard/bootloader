/*
** ###################################################################
**     Processors:          MK02FN128VFM10
**                          MK02FN64VFM10
**                          MK02FN128VLF10
**                          MK02FN64VLF10
**                          MK02FN128VLH10
**                          MK02FN64VLH10
**
**     Compilers:           Keil ARM C/C++ Compiler
**                          Freescale C/C++ for Embedded ARM
**                          GNU C Compiler
**                          IAR ANSI C/C++ Compiler for ARM
**
**     Reference manual:    K02P64M100SFARM, Rev. 0, February 14, 2014
**     Version:             rev. 0.5, 2015-02-19
**     Build:               b151215
**
**     Abstract:
**         Provides a system configuration function and a global variable that
**         contains the system frequency. It configures the device and initializes
**         the oscillator (PLL) that is part of the microcontroller device.
**
**     Copyright (c) 2015 Freescale Semiconductor, Inc.
**     All rights reserved.
**
**     Redistribution and use in source and binary forms, with or without modification,
**     are permitted provided that the following conditions are met:
**
**     o Redistributions of source code must retain the above copyright notice, this list
**       of conditions and the following disclaimer.
**
**     o Redistributions in binary form must reproduce the above copyright notice, this
**       list of conditions and the following disclaimer in the documentation and/or
**       other materials provided with the distribution.
**
**     o Neither the name of Freescale Semiconductor, Inc. nor the names of its
**       contributors may be used to endorse or promote products derived from this
**       software without specific prior written permission.
**
**     THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**     ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**     WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**     DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**     ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**     (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**     LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
**     ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**     (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**     SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**
**     http:                 www.freescale.com
**     mail:                 support@freescale.com
**
**     Revisions:
**     - rev. 0.1 (2014-02-24)
**         Initial version
**     - rev. 0.2 (2014-07-15)
**         Module access macro module_BASES replaced by module_BASE_PTRS.
**         Update of system and startup files.
**     - rev. 0.3 (2014-08-28)
**         Update of system files - default clock configuration changed.
**         Update of startup files - possibility to override DefaultISR added.
**     - rev. 0.4 (2014-10-14)
**         Interrupt INT_LPTimer renamed to INT_LPTMR0, interrupt INT_Watchdog renamed to INT_WDOG_EWM.
**     - rev. 0.5 (2015-02-19)
**         Renamed interrupt vector LLW to LLWU.
**
** ###################################################################
*/

/*!
 * @file MK02F12810
 * @version 0.5
 * @date 2015-02-19
 * @brief Device specific configuration file for MK02F12810 (implementation file)
 *
 * Provides a system configuration function and a global variable that contains
 * the system frequency. It configures the device and initializes the oscillator
 * (PLL) that is part of the microcontroller device.
 */

#include <stdint.h>
#include "system_MK02F12810.h"
#include "fsl_device_registers.h"
#include "target_config.h"

#ifndef DISABLE_WDOG
#define DISABLE_WDOG 1
#endif

/* ----------------------------------------------------------------------------
   -- Core clock
   ---------------------------------------------------------------------------- */

uint32_t SystemCoreClock = kDefaultClock;

/* ----------------------------------------------------------------------------
   -- SystemInit()
   ---------------------------------------------------------------------------- */

void SystemInit(void)
{
#if ((__FPU_PRESENT == 1) && (__FPU_USED == 1))
    SCB->CPACR |= ((3UL << 10 * 2) | (3UL << 11 * 2)); /* set CP10, CP11 Full Access */
#endif                                                 /* ((__FPU_PRESENT == 1) && (__FPU_USED == 1)) */

#if (DISABLE_WDOG)
    /* WDOG->UNLOCK: WDOGUNLOCK=0xC520 */
    WDOG->UNLOCK = WDOG_UNLOCK_WDOGUNLOCK(0xC520); /* Key 1 */
    /* WDOG->UNLOCK: WDOGUNLOCK=0xD928 */
    WDOG->UNLOCK = WDOG_UNLOCK_WDOGUNLOCK(0xD928); /* Key 2 */
                                                   /* WDOG->STCTRLH:
                                                    * ?=0,DISTESTWDOG=0,BYTESEL=0,TESTSEL=0,TESTWDOG=0,?=0,?=1,WAITEN=1,STOPEN=1,DBGEN=0,ALLOWUPDATE=1,WINEN=0,IRQRSTEN=0,CLKSRC=1,WDOGEN=0
                                                    */
    WDOG->STCTRLH = WDOG_STCTRLH_BYTESEL(0x00) | WDOG_STCTRLH_WAITEN_MASK | WDOG_STCTRLH_STOPEN_MASK |
                    WDOG_STCTRLH_ALLOWUPDATE_MASK | WDOG_STCTRLH_CLKSRC_MASK | 0x0100U;
#endif /* (DISABLE_WDOG) */
}
