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

#ifndef _aes128_key_wrap_unwrap_h
#define _aes128_key_wrap_unwrap_h

#include <stdint.h>

//! @addtogroup aes_key_wrap
//! @{

////////////////////////////////////////////////////////////////////////////////
// API
////////////////////////////////////////////////////////////////////////////////

#if defined(__cplusplus)
extern "C" {
#endif

//! @name aes_key_wrap
//@{

//! @brief Encrypt and wrap plaintext key.
//!
//! @param plaintext 40 byte plaintext input array
//! @param wrapped_ciphertext 48 byte wrapped output array
//! @param expanded_kek Expanded kek (64 bytes)
void do_aes128_key_wrap(const uint8_t plaintext[], uint8_t wrapped_ciphertext[], uint32_t expanded_kek[]);

//! @brief Decrypt and unwrap wrapped key.
//!
//! @param wrapped_ciphertext 48 byte wrapped input array
//! @param unwrapped_plaintext 48 byte plaintext output array, Note: this includes an 8 byte IV header
//!         that is added to start of the original 40 input bytes by the wrapping
//! @param expanded_kek Expanded kek (64 ints on host, 4 ints on device)
//! @retval -1 on error
//! @retval 0 on success
uint32_t do_aes128_key_unwrap(const uint8_t wrapped_ciphertext[],
                              uint8_t unwrapped_plaintext[],
                              uint32_t expanded_kek[]);
//@}

#if defined(__cplusplus)
}
#endif

//! @}

#endif // _aes128_key_wrap_unwrap_h

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
