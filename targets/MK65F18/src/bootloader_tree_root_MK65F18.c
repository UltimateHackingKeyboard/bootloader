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

#include "bootloader/bootloader.h"
#include "bootloader_tree_MK65F18.h"
#include "drivers/flash/fsl_flash.h"
#if BL_FEATURE_ENCRYPTION
#include "security/aes_security.h"
#endif // #if BL_FEATURE_ENCRYPTION

// Shoudl be put into some header files.
extern status_t dspi_write(const peripheral_descriptor_t *self, const uint8_t *buffer, uint32_t byteCount);
extern status_t i2c_write(const peripheral_descriptor_t *self, const uint8_t *buffer, uint32_t byteCount);

////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////

const char bootloaderCopyright[] = "Copyright (c) 2013-2014 Freescale Semiconductor, Inc. All rights reserved.";

const bootloader_tree_t g_bootloaderTree = {
    .runBootloader = bootloader_user_entry,
    .version = {.name = kBootloader_Version_Name,
                .major = kBootloader_Version_Major,
                .minor = kBootloader_Version_Minor,
                .bugfix = kBootloader_Version_Bugfix },
    .copyright = bootloaderCopyright,
    .flash_version = {.name = kFlashDriver_Version_Name,
                      .major = kFlashDriver_Version_Major,
                      .minor = kFlashDriver_Version_Minor,
                      .bugfix = kFlashDriver_Version_Bugfix },
    .flash_init = flash_init,
    .flash_erase_all = flash_erase_all,
    .flash_erase_all_unsecure = flash_erase_all_unsecure,
    .flash_erase = flash_erase,
    .flash_program = flash_program,
    .flash_get_security_state = flash_get_security_state,
    .flash_security_bypass = flash_security_bypass,
    .flash_verify_erase_all = flash_verify_erase_all,
    .flash_verify_erase = flash_verify_erase,
    .flash_verify_program = flash_verify_program,
    .flash_get_property = flash_get_property,
    .flash_register_callback = flash_register_callback,
#if !BL_FEATURE_MIN_PROFILE
    .flash_program_once = flash_program_once,
    .flash_read_once = flash_read_once,
    .flash_read_resource = flash_read_resource,
#else
    .flash_program_once = NULL,
    .flash_read_once = NULL,
    .flash_read_resource = NULL,
#endif
#if BL_TARGET_FLASH
    .flash_prepare_execute_in_ram_functions = flash_prepare_execute_in_ram_functions,
#else
    .flash_prepare_execute_in_ram_functions = NULL,
#endif

#if AES_SECURITY_SUPPORTED
    .aes_init = aes_init,
    .aes_encrypt = aes_encrypt,
    .aes_decrypt = aes_decrypt
#else
    .aes_init = NULL,
    .aes_encrypt = NULL,
    .aes_decrypt = NULL,
#endif
                       .dspi_write = dspi_write,
    .i2c_write = i2c_write,
};

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
