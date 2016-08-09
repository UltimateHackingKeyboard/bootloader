/*
 * Copyright (c) 2013-2016, Freescale Semiconductor, Inc.
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

#include <assert.h>
#include "fsl_flash.h"
#include "fsl_device_registers.h"

//! @addtogroup flash_driver_api
//! @{

#if (defined(KL03Z4_SERIES) || defined(KL43Z4_SERIES) || defined(KL33Z4_SERIES) || defined(KL27Z4_SERIES) || \
     defined(KL17Z4_SERIES))
#define FLASH_API_TREE_1_0
#elif(defined(KL27Z644_SERIES) || defined(KL17Z644_SERIES))
#define FLASH_API_TREE_1_1
#elif(defined(KL33Z644_SERIES) || defined(KL13Z644_SERIES) || defined(K80F25615_SERIES) || \
      defined(K81F25615_SERIES) || defined(K82F25615_SERIES) || defined(KL82Z7_SERIES) || defined(KL81Z7_SERIES))
#define FLASH_API_TREE_1_2
#endif

#if !defined(FLASH_API_TREE_1_0) && !defined(FLASH_API_TREE_1_1) && !defined(FLASH_API_TREE_1_2)
#error Unknown version of Flash Driver API.
#endif

#define BOOTLOADER_TREE_LOCATION (0x1c00001cul)
#define BOOTLOADER_API_TREE_POINTER (*(bootloader_tree_t **)BOOTLOADER_TREE_LOCATION)

typedef union BootloaderVersion
{
    struct
    {
        uint32_t bugfix : 8; //!< bugfix version [7:0]
        uint32_t minor : 8;  //!< minor version [15:8]
        uint32_t major : 8;  //!< major version [23:16]
        uint32_t name : 8;   //!< name [31:24]
    } B;
    uint32_t version; //!< combined version numbers
} standard_version_t;

//! @brief Interface for the flash driver.
typedef struct FlashDriverInterface
{
#if !defined(FLASH_API_TREE_1_0)
    standard_version_t version; //!< flash driver API version number.
#endif

    status_t (*flash_init)(flash_config_t *config);

#if defined(FLASH_API_TREE_1_0)
    status_t (*flash_erase_all)(flash_config_t *config);
    status_t (*flash_erase_all_unsecure)(flash_config_t *config);
    status_t (*flash_erase)(flash_config_t *config, uint32_t start, uint32_t lengthInBytes);
#else
    status_t (*flash_erase_all)(flash_config_t *config, uint32_t key);
    status_t (*flash_erase_all_unsecure)(flash_config_t *config, uint32_t key);
    status_t (*flash_erase)(flash_config_t *config, uint32_t start, uint32_t lengthInBytes, uint32_t key);
#endif

    status_t (*flash_program)(flash_config_t *config, uint32_t start, uint32_t *src, uint32_t lengthInBytes);
    status_t (*flash_get_security_state)(flash_config_t *config, flash_security_state_t *state);
    status_t (*flash_security_bypass)(flash_config_t *config, const uint8_t *backdoorKey);
    status_t (*flash_verify_erase_all)(flash_config_t *config, flash_margin_value_t margin);
    status_t (*flash_verify_erase)(flash_config_t *config,
                                   uint32_t start,
                                   uint32_t lengthInBytes,
                                   flash_margin_value_t margin);
    status_t (*flash_verify_program)(flash_config_t *config,
                                     uint32_t start,
                                     uint32_t lengthInBytes,
                                     const uint32_t *expectedData,
                                     flash_margin_value_t margin,
                                     uint32_t *failedAddress,
                                     uint32_t *failedData);
    status_t (*flash_get_property)(flash_config_t *config, flash_property_tag_t whichProperty, uint32_t *value);

#if (!defined(FLASH_API_TREE_1_0)) && (!defined(FLASH_API_TREE_1_1))
    status_t (*flash_register_callback)(flash_config_t *config, flash_callback_t callback);
    status_t (*flash_program_once)(flash_config_t *config, uint32_t index, uint32_t *src, uint32_t lengthInBytes);
    status_t (*flash_read_once)(flash_config_t *config, uint32_t index, uint32_t *dst, uint32_t lengthInBytes);
    status_t (*flash_read_resource)(flash_config_t *config,
                                    uint32_t start,
                                    uint32_t *dst,
                                    uint32_t lengthInBytes,
                                    flash_read_resource_option_t option);
#endif
} flash_driver_interface_t;

//! @brief Root of the bootloader API tree.
//!
//! An instance of this struct resides in read-only memory in the bootloader. It
//! provides a user application access to APIs exported by the bootloader.
//!
//! @note The order of existing fields must not be changed.
typedef struct BootloaderTree
{
    void (*runBootloader)(void *arg);            //!< Function to start the bootloader executing.
    standard_version_t bootloader_version;       //!< Bootloader version number.
    const char *copyright;                       //!< Copyright string.
    const uint32_t *reserved;                    //!< Do NOT use.
    const flash_driver_interface_t *flashDriver; //!< Flash driver API.
} bootloader_tree_t;

////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////

//! @brief Global pointer to the flash driver API table in ROM.
static const flash_driver_interface_t *s_flashInterface;

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////

// See fsl_flash.h for documentation of this function.
status_t FLASH_Init(flash_config_t *config)
{
    // Get pointer to flash driver API table in ROM.
    s_flashInterface = BOOTLOADER_API_TREE_POINTER->flashDriver;
    assert(s_flashInterface);

    return s_flashInterface->flash_init(config);
}

// See fsl_flash.h for documentation of this function.
status_t FLASH_EraseAll(flash_config_t *config, uint32_t key)
{
    assert(s_flashInterface);
#if defined(FLASH_API_TREE_1_0)
    if (key != kFLASH_ApiEraseKey)
    {
        return kStatus_FLASH_EraseKeyError;
    }
    return s_flashInterface->flash_erase_all(config);
#else
    return s_flashInterface->flash_erase_all(config, key);
#endif
}

// See fsl_flash.h for documentation of this function.
status_t FLASH_Erase(flash_config_t *config, uint32_t start, uint32_t lengthInBytes, uint32_t key)
{
    assert(s_flashInterface);
#if defined(FLASH_API_TREE_1_0)
    if (key != kFLASH_ApiEraseKey)
    {
        return kStatus_FLASH_EraseKeyError;
    }
    return s_flashInterface->flash_erase(config, start, lengthInBytes);
#else
    return s_flashInterface->flash_erase(config, start, lengthInBytes, key);
#endif
}

// See fsl_flash.h for documentation of this function.
status_t FLASH_EraseAllUnsecure(flash_config_t *config, uint32_t key)
{
    assert(s_flashInterface);
#if defined(FLASH_API_TREE_1_0)
    if (key != kFLASH_ApiEraseKey)
    {
        return kStatus_FLASH_EraseKeyError;
    }
    return s_flashInterface->flash_erase_all_unsecure(config);
#else
    return s_flashInterface->flash_erase_all_unsecure(config, key);
#endif
}

// See fsl_flash.h for documentation of this function.
status_t FLASH_Program(flash_config_t *config, uint32_t start, uint32_t *src, uint32_t lengthInBytes)
{
    assert(s_flashInterface);
    return s_flashInterface->flash_program(config, start, src, lengthInBytes);
}

// See fsl_flash.h for documentation of this function.
status_t FLASH_GetSecurityState(flash_config_t *config, flash_security_state_t *state)
{
    assert(s_flashInterface);
    return s_flashInterface->flash_get_security_state(config, state);
}

// See fsl_flash.h for documentation of this function.
status_t FLASH_SecurityBypass(flash_config_t *config, const uint8_t *backdoorKey)
{
    assert(s_flashInterface);
    return s_flashInterface->flash_security_bypass(config, backdoorKey);
}

// See fsl_flash.h for documentation of this function.
status_t FLASH_VerifyEraseAll(flash_config_t *config, flash_margin_value_t margin)
{
    assert(s_flashInterface);
    return s_flashInterface->flash_verify_erase_all(config, margin);
}

// See fsl_flash.h for documentation of this function.
status_t FLASH_VerifyErase(flash_config_t *config, uint32_t start, uint32_t lengthInBytes, flash_margin_value_t margin)
{
    assert(s_flashInterface);
    return s_flashInterface->flash_verify_erase(config, start, lengthInBytes, margin);
}

// See fsl_flash.h for documentation of this function.
status_t FLASH_VerifyProgram(flash_config_t *config,
                             uint32_t start,
                             uint32_t lengthInBytes,
                             const uint32_t *expectedData,
                             flash_margin_value_t margin,
                             uint32_t *failedAddress,
                             uint32_t *failedData)
{
    assert(s_flashInterface);
    return s_flashInterface->flash_verify_program(config, start, lengthInBytes, expectedData, margin, failedAddress,
                                                  failedData);
}

// See fsl_flash.h for documentation of this function.
status_t FLASH_GetProperty(flash_config_t *config, flash_property_tag_t whichProperty, uint32_t *value)
{
    assert(s_flashInterface);
    if (whichProperty == kFLASH_PropertyVersion)
    {
#if defined(FLASH_API_TREE_1_0)
        standard_version_t version;
        version.B.name = 'F';
        version.B.major = 1;
        version.B.minor = 0;
        version.B.bugfix = 0;
        *value = version.version;
#else
        *value = s_flashInterface->version.version;
#endif
        return kStatus_Success;
    }
    return s_flashInterface->flash_get_property(config, whichProperty, value);
}

// See fsl_flash.h for documentation of this function.
status_t FLASH_ProgramOnce(flash_config_t *config, uint32_t index, uint32_t *src, uint32_t lengthInBytes)
{
    assert(s_flashInterface);
#if (!defined(FLASH_API_TREE_1_0)) && (!defined(FLASH_API_TREE_1_1))
    if (s_flashInterface->flash_program_once)
    {
        return s_flashInterface->flash_program_once(config, index, src, lengthInBytes);
    }
#endif
    return kStatus_FLASH_CommandNotSupported;
}

// See fsl_flash.h for documentation of this function.
status_t FLASH_ReadResource(
    flash_config_t *config, uint32_t start, uint32_t *dst, uint32_t lengthInBytes, flash_read_resource_option_t option)
{
    assert(s_flashInterface);
#if (!defined(FLASH_API_TREE_1_0)) && (!defined(FLASH_API_TREE_1_1))
    if (s_flashInterface->flash_read_resource)
    {
        return s_flashInterface->flash_read_resource(config, start, dst, lengthInBytes, option);
    }
#endif
    return kStatus_FLASH_CommandNotSupported;
}

// See fsl_flash.h for documentation of this function.
status_t FLASH_ReadOnce(flash_config_t *config, uint32_t index, uint32_t *dst, uint32_t lengthInBytes)
{
    assert(s_flashInterface);
#if (!defined(FLASH_API_TREE_1_0)) && (!defined(FLASH_API_TREE_1_1))
    if (s_flashInterface->flash_read_once)
    {
        return s_flashInterface->flash_read_once(config, index, dst, lengthInBytes);
    }
#endif
    return kStatus_FLASH_CommandNotSupported;
}

// See fsl_flash.h for documentation of this function.
status_t FLASH_SetCallback(flash_config_t *config, flash_callback_t callback)
{
    assert(s_flashInterface);
#if (!defined(FLASH_API_TREE_1_0)) && (!defined(FLASH_API_TREE_1_1))
    return s_flashInterface->flash_register_callback(config, callback);
#else
    return kStatus_FLASH_CommandNotSupported;
#endif
}

//! @}

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
