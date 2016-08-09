/*
 * Copyright (c) 2014-2016, Freescale Semiconductor, Inc.
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

#ifndef _fsl_otfad_hal_h
#define _fsl_oftad_hal_h

#include "bootloader_common.h"

//! @addtogroup otfad_hal
//! @{

////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////

//! @brief Constants
enum _hal_constants
{
    kOtfadNumKeyWords = 4, //!< Number of key words
    kOtfadNumCtrWords = 2, //!< Number of counter words
    kOtfadNumRgnWords = 2  //!< Number of region words
};

//! @brief Format of context info.
typedef struct OtfadContextInfo
{
    uint32_t keyInfo[kOtfadNumKeyWords];    //!< Key words
    uint32_t ctrInfo[kOtfadNumCtrWords];    //!< Counter words
    uint32_t regionInfo[kOtfadNumRgnWords]; //!< Region words
} otfad_context_info_t;

//! @brief Operational modes.
enum _otfad_modes
{
    kOtfadMode_Normal = 0x00,            //!< Normal mode (NRM)
    kOtfadMode_SecurityViolation = 0x02, //!< Security Violation Mode (SVM)
    kOtfadMode_LogiallyDisabled = 0x03   //!< Logically Disabled Mode (LDM)
};

//! @brief Enable flags.
enum _otfad_enables
{
    kOtfadDisable = 0x00, //!< Disable
    kOtfadEnable = 0x01   //!< Enable
};

////////////////////////////////////////////////////////////////////////////////
// Prototypes
////////////////////////////////////////////////////////////////////////////////

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

//! @brief Get the current mode.
//!
//! @param baseAddr Module base address
//! @return Current mode in status register
uint32_t otfad_hal_get_mode(OTFAD_Type *baseAddr);

//! @brief Enable the module.
//!
//! Set the global enable flag in the control register to '1'.
//! A power-on reset is required to clear this flag.
//!
//! @param baseAddr Module base address
void otfad_hal_global_enable(OTFAD_Type *baseAddr);

//! @brief Disable the module.
//!
//! Clear the global enable flag in the control register to '0'.
//! A power-on reset is required to clear this flag.
//!
//! @param baseAddr Module base address
void otfad_hal_global_disable(OTFAD_Type *baseAddr);

//! @brief Get enabled state.
//!
//! @param baseAddr Module base address
//! @return Global enabled flag in status register
bool otfad_hal_is_enabled(OTFAD_Type *baseAddr);

//! @brief Enable restricted register status.
//!
//! Set the restricted register access enable flag in the control register to '1'.
//! A power-on reset is required to clear this flag.
//!
//! @param baseAddr Module base address
void otfad_hal_restricted_register_access_enable(OTFAD_Type *baseAddr);

//! @brief Get restricted register access state.
//!
//! @param baseAddr Module base address
//! @return Restricted register access flag in status register
bool otfad_hal_is_register_access_restricted(OTFAD_Type *baseAddr);

//! @brief Get hardware revision level.
//!
//! @param baseAddr Module base address
//! @return Hardware revision level from status register
uint32_t otfad_hal_get_hardware_revision_level(OTFAD_Type *baseAddr);

//! @brief Get number of contexts.
//!
//! @param baseAddr Module base address
//! @return Number of contexts from status register
uint32_t otfad_hal_get_number_of_contexts(OTFAD_Type *baseAddr);

//! @brief Set context info.
//!
//! @param baseAddr Module base address
//! @param contextNum Context number
//! @param contextInfo Ponter to context info struct
void otfad_hal_set_context(OTFAD_Type *baseAddr, uint32_t contextNum, const otfad_context_info_t *contextInfo);

#if defined(__cplusplus)
}
#endif // __cplusplus

//! @}

#endif // _fsl_otfad_hal.h_

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
