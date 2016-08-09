/*
** ###################################################################
**     Processors:          MK82FN256CAx15
**                          MK82FN256VDC15
**                          MK82FN256VLL15
**                          MK82FN256VLQ15
**
**     Compilers:           Keil ARM C/C++ Compiler
**                          Freescale C/C++ for Embedded ARM
**                          GNU C Compiler
**                          GNU C Compiler - CodeSourcery Sourcery G++
**                          IAR ANSI C/C++ Compiler for ARM
**
**     Reference manual:    K82P121M150SF5RM, Rev. 0, May 2015
**     Version:             rev. 1.1, 2015-05-28
**     Build:               b150626
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
**     - rev. 1.0 (2015-04-09)
**         Initial version
**     - rev. 1.1 (2015-05-28)
**         Update according to the reference manual Rev. 0.
**
** ###################################################################
*/

/*!
 * @file MK82F25615
 * @version 1.1
 * @date 2015-05-28
 * @brief Device specific configuration file for MK82F25615 (implementation file)
 *
 * Provides a system configuration function and a global variable that contains
 * the system frequency. It configures the device and initializes the oscillator
 * (PLL) that is part of the microcontroller device.
 */

#include <stdint.h>
#include "fsl_device_registers.h"

/*!
 * @brief Defines the structure to set the Bootloader Configuration Area
 *
 * This type of variable is used to set the Bootloader Configuration Area
 * of the chip.
 */
typedef struct SystemBootloaderConfig
{
    uint32_t tag;               /*!< Magic number to verify bootloader configuration is valid. Must be set to 'kcfg'. */
    uint32_t crcStartAddress;   /*!< Start address for application image CRC check. If the bits are all set then Kinetis
                                   bootloader by default will not perform any CRC check. */
    uint32_t crcByteCount;      /*!< Byte count for application image CRC check. If the bits are all set then Kinetis
                                   bootloader by default will not prform any CRC check. */
    uint32_t crcExpectedValue;  /*!< Expected CRC value for application CRC check. If the bits are all set then Kinetis
                                   bootloader by default will not perform any CRC check.*/
    uint8_t enabledPeripherals; /*!< Bitfield of peripherals to enable.
                                     bit 0 - LPUART, bit 1 - I2C, bit 2 - SPI, bit 4 - USB
                                     Kinetis bootloader will enable the peripheral if corresponding bit is set to 1. */
    uint8_t i2cSlaveAddress;    /*!< If not 0xFF, used as the 7-bit I2C slave address. If 0xFF, defaults to 0x10 for I2C
                                   slave address */
    uint16_t peripheralDetectionTimeoutMs; /*!< Timeout in milliseconds for active peripheral detection. If 0xFFFF,
                                              defaults to 5 seconds. */
    uint16_t usbVid; /*!< Sets the USB Vendor ID reported by the device during enumeration. If 0xFFFF, it defaults to
                        0x15A2. */
    uint16_t usbPid; /*!< Sets the USB Product ID reported by the device during enumeration. */
    uint32_t usbStringsPointer; /*!< Sets the USB Strings reported by the device during enumeration. */
    uint8_t clockFlags;   /*!< The flags in the clockFlags configuration field are enabled if the corresponding bit is
                             cleared (0).
                              bit 0 - HighSpeed Enable high speed mode (i.e., 48 MHz).	*/
    uint8_t clockDivider; /*!< Inverted value of the divider to use for core and bus clocks when in high speed mode */
    uint8_t bootFlags; /*!< If bit 0 is cleared, then Kinetis bootloader will jump to either Quad SPI Flash or internal
                          flash image depending on FOPT BOOTSRC_SEL bits.
                           If the bit is set, then Kinetis bootloader will prepare for host communication over serial
                          peripherals. */
    uint8_t RESERVED1;
    uint32_t mmcauConfigPointer; /*!< A pointer to the MMCAU configuration structure in memory. */
    uint32_t keyBlobPointer;     /*!< A pointer to the keyblob data in memory. */
    uint8_t RESERVED2[8];
    uint32_t qspiConfigBlockPtr; /*!< A pointer to the QSPI config block in internal flash array. */
    uint8_t RESERVED3[12];
} system_bootloader_config_t;

/* Bootlader configuration area */
#if defined(__IAR_SYSTEMS_ICC__)
/* Pragma to place the Bootloader Configuration Array on correct location defined in linker file. */
#pragma language = extended
#pragma location = "BootloaderConfig"
__root const system_bootloader_config_t BootloaderConfig @"BootloaderConfig" =
#elif defined(__GNUC__)
__attribute__((section(".BootloaderConfig"))) const system_bootloader_config_t BootloaderConfig =
#elif defined(__CC_ARM)
__attribute__((section("BootloaderConfig"))) const system_bootloader_config_t BootloaderConfig __attribute__((used)) =
#else
#error Unsupported compiler!
#endif
    {
      .tag = 0x6766636BU,                   /* Magic Number */
      .crcStartAddress = 0xFFFFFFFFU,       /* Disable CRC check */
      .crcByteCount = 0xFFFFFFFFU,          /* Disable CRC check */
      .crcExpectedValue = 0xFFFFFFFFU,      /* Disable CRC check */
      .enabledPeripherals = 0x17,           /* Enable all peripherals */
      .i2cSlaveAddress = 0xFF,              /* Use default I2C address */
      .peripheralDetectionTimeoutMs = 3000, /* timeout: 3000ms */
      .usbVid = 0xFFFFU,                    /* Use default USB Vendor ID */
      .usbPid = 0xFFFFU,                    /* Use default USB Product ID */
      .usbStringsPointer = 0xFFFFFFFFU,     /* Use default USB Strings */
      .clockFlags = 0x01,                   /* Enable High speed mode */
      .clockDivider = 0xFF,                 /* Use clock divider 1 */
      .bootFlags = 0x01,                    /* Enable communication with host */
      .mmcauConfigPointer = 0xFFFFFFFFU,    /* No MMCAU configuration */
      .keyBlobPointer = 0x000001000,        /* keyblob data is at 0x1000 */
      .qspiConfigBlockPtr = 0x2000,         /* QCB is placed at 0x2000 */
    };

/* ----------------------------------------------------------------------------
   -- Core clock
   ---------------------------------------------------------------------------- */

uint32_t SystemCoreClock = 96000000ul;

/**
 *  A section located at 0x410 used for storing ROM patch code
 *
 * pseudo-code:
 *    int rom_patch(qspi_config_t *base)
 *    {
 *        volatile uint32_t *qspi_flshcr_reg = (volatile uint32_t*)QuadSPI0_FLSHCR_BASE;
 *
 *        // Set QuadSPI_FLSHCR[TDH] to given parameters.
 *        *qspi_flshcr_reg &= (uint32_t)~QuadSPI_FLSHCR_TDH_MASK;
 *        *qspi_flshcr_reg |= (base->data_hold_time)<<QuadSPI0_FLSHCR_TDH_SHIFT;
 *
 *        return kStatus_Success;
    }
 */

#if defined(__IAR_SYSTEMS_ICC__)
/* Pragma to place the rom patch code on correct location defined in linker file. */
#pragma language = extended
#pragma section = "rom_patch_code"
const uint8_t s_rom_patch[124] @"rom_patch_code" =
#elif defined(__GNUC__)
__attribute__((section("rom_patch_code"))) const uint8_t s_rom_patch[124] __attribute__((used)) =

#elif defined(__CC_ARM)
__attribute__((section("rom_patch_code"))) const uint8_t s_rom_patch[124] __attribute__((used)) =
#else
#error Unsupported compiler!
#endif
    { 0x10, 0xB5, 0x01, 0x00, 0x17, 0x4A, 0x10, 0x00, 0x18, 0x30, 0x17, 0x4B, 0x1B, 0x68, 0xDB, 0x00, 0x02, 0xD5,
      0x16, 0x4A, 0x10, 0x00, 0x18, 0x30, 0x13, 0x68, 0x15, 0x4C, 0x1C, 0x40, 0x14, 0x60, 0x13, 0x68, 0x0C, 0x69,
      0x24, 0x04, 0x1C, 0x43, 0x14, 0x60, 0x02, 0x68, 0x11, 0x4B, 0x13, 0x40, 0x03, 0x60, 0xDA, 0x22, 0x52, 0x00,
      0x89, 0x18, 0x02, 0x68, 0x0B, 0x68, 0x1B, 0x04, 0xFC, 0x24, 0xA4, 0x03, 0x1C, 0x40, 0x14, 0x43, 0x04, 0x60,
      0x02, 0x68, 0x0B, 0x4B, 0x13, 0x40, 0x03, 0x60, 0x02, 0x68, 0x49, 0x68, 0x09, 0x06, 0xFC, 0x23, 0x9B, 0x05,
      0x0B, 0x40, 0x13, 0x43, 0x03, 0x60, 0x00, 0x20, 0x10, 0xBD, 0x0C, 0xA0, 0x0D, 0x40, 0x24, 0x80, 0x04, 0x40,
      0x0C, 0xA0, 0x05, 0x40, 0xFF, 0xFF, 0xFC, 0xFF, 0xFF, 0xFF, 0xC0, 0xFF, 0xFF, 0xFF, 0xFF, 0xC0 };

/*
 *   ROM patch handler for ROM patch code execution.
 */
#if defined(__IAR_SYSTEMS_ICC__)
/* Pragma to place the ROM_PatchHandler on correct location defined in linker file. */
#pragma language = extended
#pragma section = "BootloaderPatchHandler"
void ROM_PatchHandler(void) @"BootloaderPatchHandler"
#elif defined(__GNUC__)
__attribute__((section("BootloaderPatchHandler"))) void ROM_PatchHandler(void)
#elif defined(__CC_ARM)
__attribute__((section("BootloaderPatchHandler"))) void ROM_PatchHandler(void)
#else
#error Unsupported compiler!
#endif
{
    typedef int (*patch_handler_t)(uint32_t);

#if defined(__IAR_SYSTEMS_ICC__)
    uint32_t s_rom_patch_start = (uint32_t)__section_begin("rom_patch_code");
#elif defined(__CC_ARM)
    extern uint32_t Load$$EXEC_m_rom_patch_code$$Base[];
    uint32_t s_rom_patch_start = (uint32_t)&Load$$EXEC_m_rom_patch_code$$Base;
#elif defined(__GNUC__)
    extern uint32_t rom_patch_code_start[];
    uint32_t s_rom_patch_start = (uint32_t)&rom_patch_code_start;
#endif

    uint32_t patch_start = s_rom_patch_start + 1;
    patch_handler_t patch_run = (patch_handler_t)patch_start;
    patch_run(BootloaderConfig.qspiConfigBlockPtr);
}

/* ----------------------------------------------------------------------------
   -- SystemInit()
   ---------------------------------------------------------------------------- */
void SystemInit(void)
{
#if ((__FPU_PRESENT == 1) && (__FPU_USED == 1))
    SCB->CPACR |= ((3UL << 10 * 2) | (3UL << 11 * 2)); /* set CP10, CP11 Full Access */
#endif                                                 /* ((__FPU_PRESENT == 1) && (__FPU_USED == 1)) */
}
