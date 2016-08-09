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

#include "bootloader/bl_context.h"
#include "memory/memory.h"

////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////

//! @brief Memory map for KL28T512.
//!
//! This map is not const because it is updated at runtime with the actual sizes of
//! flash and RAM for the chip we're running on.
memory_map_entry_t g_memoryMap[] = {
    { 0x00000000, 0x0007ffff, kMemoryIsExecutable, &g_flashMemoryInterface },   // 512kB Flash array
    { 0x1fff8000, 0x20017fff, kMemoryIsExecutable, &g_normalMemoryInterface },  // 128kB SRAM
    { 0x40000000, 0x4007ffff, kMemoryNotExecutable, &g_deviceMemoryInterface }, // AIPS0 peripherals
    { 0x40080000, 0x400fffff, kMemoryNotExecutable, &g_deviceMemoryInterface }, // AIPS1 peripherals
    { 0x44000000, 0x5fffffff, kMemoryNotExecutable, &g_deviceMemoryInterface }, // BME
    { 0xf0000000, 0xf0006fff, kMemoryNotExecutable, &g_deviceMemoryInterface }, // M0+ Private Peripheral Bus 0 (CPU0)
    { 0xf8000000, 0xffffffff, kMemoryNotExecutable, &g_deviceMemoryInterface }, // IOPORT (single-cycle GPIO)
    { 0 }                                                                       // Terminator
};

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
