/*
 * Copyright (c) 2014, Freescale Semiconductor, Inc.
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
#include "memory/memory.h"
#if !defined(BOOTLOADER_HOST)
#include "fsl_device_registers.h"
#endif // BOOTLOADER_HOST
#include "utilities/fsl_assert.h"
#include "sram_init.h"

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////

//! @brief Initialize address ranges of SRAM for chips belongs to cm0plus family
status_t sram_init(void)
{
#if defined(__CORE_CM0PLUS_H_GENERIC)

    uint32_t ram_size = 0;

#if FSL_FEATURE_SIM_OPT_HAS_RAMSIZE
    uint32_t tmp = (SIM->SOPT1 & SIM_SOPT1_RAMSIZE_MASK) >> SIM_SOPT1_RAMSIZE_SHIFT;
    switch (tmp)
    {
        case 1:
            ram_size = 8 * 1024;
            break;
        case 3:
            ram_size = 16 * 1024;
            break;
        case 4:
            ram_size = 24 * 1024;
            break;
        case 5:
            ram_size = 32 * 1024;
            break;
        case 6:
            ram_size = 48 * 1024;
            break;
        case 7:
            ram_size = 64 * 1024;
            break;
        case 8:
            ram_size = 96 * 1024;
            break;
        case 9:
            ram_size = 128 * 1024;
            break;
        case 11:
            ram_size = 256 * 1024;
            break;
        default:
            break;
    }
#else
    uint32_t tmp = (SIM->SDID & SIM_SDID_SRAMSIZE_MASK) >> SIM_SDID_SRAMSIZE_SHIFT;

    if (tmp <= kMaxRamIndex)
    {
        ram_size = kMinKlRamSize << tmp;
    }
#endif

    assert(ram_size > 0);

    if (ram_size > 0)
    {
        // Update address range of SRAM
        memory_map_entry_t *map = (memory_map_entry_t *)&g_bootloaderContext.memoryMap[kIndexSRAM];
        tmp = ram_size / (kSram_LowerPart + kSram_UpperPart);
        map->startAddress = kSRAMSeparatrix - tmp * kSram_LowerPart;   // start of SRAM
        map->endAddress = kSRAMSeparatrix + tmp * kSram_UpperPart - 1; // end of SRAM
    }
#else
#error "This function only applies to cm0plus family"
#endif // __CORE_CM0PLUS_H_GENERIC

    return kStatus_Success;
}

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
