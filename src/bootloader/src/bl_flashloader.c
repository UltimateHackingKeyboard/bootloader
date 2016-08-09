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

#include <string.h>
#include "bootloader_common.h"
#include "fsl_device_registers.h"
#include "utilities/vector_table_info.h"
#include "bootloader/flashloader_image.h"

#if DEBUG
#include "debug/flashloader_image.c"
#else
#include "release/flashloader_image.c"
#endif

////////////////////////////////////////////////////////////////////////////////
// Prototypes
////////////////////////////////////////////////////////////////////////////////

void bootloader_cleanup(void);
void bootloader_run(void);
int main(void);

////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////

// Not used, but needed to resolve reference in startup.s.
uint32_t g_bootloaderTree;

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////

void bootloader_cleanup()
{
    // Turn off interrupts.
    __disable_irq();

    // Set the VTOR to default.
    SCB->VTOR = kDefaultVectorTableAddress;

    // Memory barriers for good measure.
    __ISB();
    __DSB();
}

// @brief Run the bootloader.
void bootloader_run(void)
{
    // Copy flashloader image to RAM.
    memcpy((void *)g_flashloaderBase, g_flashloaderImage, g_flashloaderSize);

    bootloader_cleanup();

    // Set main stack pointer and process stack pointer.
    __set_MSP(g_flashloaderStack);
    __set_PSP(g_flashloaderStack);

    // Jump to flashloader entry point, does not return.
    void (*entry)(void) = (void (*)(void))g_flashloaderEntry;
    entry();
}

// @brief Main bootloader entry point.
int main(void)
{
    bootloader_run();

    // Should never end up here.
    while (1)
        ;
}

// Needed to resolve library reference.
int __write(void)
{
    return 0;
}

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
