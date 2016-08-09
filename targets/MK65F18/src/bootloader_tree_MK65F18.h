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
#include "drivers/flash/fsl_flash.h"

typedef struct BootloaderTree
{
    /* General information */
    void (*runBootloader)(void *arg); //!< Function to start the bootloader executing.
    standard_version_t version;       //!< Bootloader version number.
    const char *copyright;            //!< Copyright string.

    /* Flash driver APIs */
    standard_version_t flash_version; //!< flash driver API version number.
    status_t (*flash_init)(flash_driver_t *driver);
    status_t (*flash_erase_all)(flash_driver_t *driver, uint32_t key);
    status_t (*flash_erase_all_unsecure)(flash_driver_t *driver, uint32_t key);
    status_t (*flash_erase)(flash_driver_t *driver, uint32_t start, uint32_t lengthInBytes, uint32_t key);
    status_t (*flash_program)(flash_driver_t *driver, uint32_t start, uint32_t *src, uint32_t lengthInBytes);
    status_t (*flash_get_security_state)(flash_driver_t *driver, flash_security_state_t *state);
    status_t (*flash_security_bypass)(flash_driver_t *driver, const uint8_t *backdoorKey);
    status_t (*flash_verify_erase_all)(flash_driver_t *driver, flash_margin_value_t margin);
    status_t (*flash_verify_erase)(flash_driver_t *driver,
                                   uint32_t start,
                                   uint32_t lengthInBytes,
                                   flash_margin_value_t margin);
    status_t (*flash_verify_program)(flash_driver_t *driver,
                                     uint32_t start,
                                     uint32_t lengthInBytes,
                                     const uint8_t *expectedData,
                                     flash_margin_value_t margin,
                                     uint32_t *failedAddress,
                                     uint32_t *failedData);
    status_t (*flash_get_property)(flash_driver_t *driver, flash_property_t whichProperty, uint32_t *value);
    status_t (*flash_register_callback)(flash_driver_t *driver, flash_callback_t callback);
    status_t (*flash_program_once)(flash_driver_t *driver, uint32_t index, uint32_t *src, uint32_t lengthInBytes);
    status_t (*flash_read_once)(flash_driver_t *driver, uint32_t index, uint32_t *dst, uint32_t lengthInBytes);
    status_t (*flash_read_resource)(flash_driver_t *driver,
                                    uint32_t start,
                                    uint32_t *dst,
                                    uint32_t lengthInBytes,
                                    flash_read_resource_option_t option);
    status_t (*flash_prepare_execute_in_ram_functions)(flash_driver_t *driver);

    /* AES APIs */
    void (*aes_init)(uint32_t *key);
    void (*aes_encrypt)(uint32_t *in, uint32_t *key, uint32_t *out);
    void (*aes_decrypt)(uint32_t *in, uint32_t *key, uint32_t *out);

    /* Peripherals APIs */
    status_t (*dspi_write)(const peripheral_descriptor_t *self, const uint8_t *buffer, uint32_t byteCount);
    status_t (*i2c_write)(const peripheral_descriptor_t *self, const uint8_t *buffer, uint32_t byteCount);

} bootloader_tree_t;

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
