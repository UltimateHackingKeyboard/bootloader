/*
** ###################################################################
**     Processors:          MKL25Z128FM4
**                          MKL25Z128FT4
**                          MKL25Z128LH4
**                          MKL25Z128VLK4
**
**     Compilers:           ARM Compiler
**                          Freescale C/C++ for Embedded ARM
**                          GNU C Compiler
**                          IAR ANSI C/C++ Compiler for ARM
**
**     Reference manual:    KL25P80M48SF0RM, Rev.3, Sep 2012
**     Version:             rev. 1.3, 2012-10-04
**
**     Abstract:
**         Provides a system configuration function and a global variable that
**         contains the system frequency. It configures the device and initializes
**         the oscillator (PLL) that is part of the microcontroller device.
**
**     Copyright: 2012 Freescale, Inc. All Rights Reserved.
**
**     http:                 www.freescale.com
**     mail:                 support@freescale.com
**
**     Revisions:
**     - rev. 1.0 (2012-06-13)
**         Initial version.
**     - rev. 1.1 (2012-06-21)
**         Update according to reference manual rev. 1.
**     - rev. 1.2 (2012-08-01)
**         Device type UARTLP changed to UART0.
**     - rev. 1.3 (2012-10-04)
**         Update according to reference manual rev. 3.
**
** ###################################################################
*/

/**
 * @file MKL25Z4
 * @version 1.3
 * @date 2012-10-04
 * @brief Device specific configuration file for MKL25Z4 (implementation file)
 *
 * Provides a system configuration function and a global variable that contains
 * the system frequency. It configures the device and initializes the oscillator
 * (PLL) that is part of the microcontroller device.
 */

#include <stdint.h>
#include "system_MKL28Z7.h"
#include "fsl_device_registers.h"
#include "wdog32/fsl_wdog32.h"

#ifndef DISABLE_WDOG
#define DISABLE_WDOG 1
#endif // DISABLE_WDOG

/*----------------------------------------------------------------------------
  Define clock source values
 *----------------------------------------------------------------------------*/
#define DEFAULT_SYSTEM_CLOCK 8000000u /* Default System clock value */

/* ----------------------------------------------------------------------------
   -- Core clock
   ---------------------------------------------------------------------------- */
uint32_t SystemCoreClock = DEFAULT_SYSTEM_CLOCK;
/* ----------------------------------------------------------------------------
   -- SystemInit()
   ---------------------------------------------------------------------------- */

void SystemInit(void)
{
#if (DISABLE_WDOG)
    wdog32_config_t config;
    WDOG32_GetDefaultConfig(&config);
    config.enableWdog32 = false;
    WDOG32_Init(WDOG0, &config);
#endif /* (DISABLE_WDOG) */

#if defined(BL_TARGET_ROM)
    // Set Force ROM bits in RCM. We only set bit 2, so the RCM_MR register doesn't
    // falsely show that the ROM was booted via boot pin assertion.
    RCM_WR_FM_FORCEROM(RCM, 2);
#else
    RCM->FM &= RCM_FM_FORCEROM_MASK;
#endif
}

/* ----------------------------------------------------------------------------
   -- SystemCoreClockUpdate()
   ---------------------------------------------------------------------------- */

void SystemCoreClockUpdate(void)
{
}
