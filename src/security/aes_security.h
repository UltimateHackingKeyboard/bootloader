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

#ifndef _aes_security_h
#define _aes_security_h

#include "bootloader_common.h"

//! @addtogroup aes_security
//! @{

////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////

#define AES_128_KEY_SIZE 16                // bytes
#define AES_128_KEY_SIZE_WORDS 4           // 32 bit words
#define AES_BLOCK_SIZE_WORDS 4             // 32 bit words
#define AES_BLOCK_SIZE 16                  // bytes
#define AES_128_KEY_SCHEDULE_SIZE_WORDS 44 // 32 bit words

#define AES_SECURITY_SUPPORTED (defined(CAU_BASE) || defined(LTC0_BASE) || FSL_FEATURE_SIM_HAS_MISCCTRL_LTCEN)

typedef struct mmcau_function_info
{
    uint32_t tag;    // 'kcau' = 0x
    uint32_t length; // number of bytes to copy, this number will be copied from the start of aes_init
    uint32_t aes_init_start;
    uint32_t aes_encrypt_start;
    uint32_t aes_decrypt_start;
} mmcau_function_info_t;

enum _mmcau_info_tag
{
    //! @brief Tag value used to validate the bootloader configuration data.
    kMmcauInfoTag = FOUR_CHAR_CODE('k', 'c', 'a', 'u')
};

////////////////////////////////////////////////////////////////////////////////
// API
////////////////////////////////////////////////////////////////////////////////

#if defined(__cplusplus)
extern "C" {
#endif

//! @name aes_security
//@{

//! @brief An initialization function for the decryption peripheral
//! Warning: The key must be word aligned
void aes_init(uint32_t *key);

//! @brief Encrypts a 16 byte block of data
//! in and out may use the same address so encrypting in place is supported
//! Warning: All parameters must be word aligned
void aes_encrypt(uint32_t *in, uint32_t *key, uint32_t *out);

//! @brief Decrypts a 16 byte block of data
//! in and out may use the same address so decrypting in place is supported
//! Warning: All parameters must be word aligned
void aes_decrypt(uint32_t *in, uint32_t *key, uint32_t *out);
//@}

#if defined(__cplusplus)
}
#endif

//! @}

#endif // _aes_security_h
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
