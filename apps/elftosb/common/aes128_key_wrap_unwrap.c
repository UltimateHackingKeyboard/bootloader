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
#define BOOTLOADER_HOST

#include "aes128_key_wrap_unwrap.h"
#if !defined(BOOTLOADER_HOST)
#include "security/aes_security.h"
#endif

#if defined(BOOTLOADER_HOST)
// From bytes_aes.c.
extern void Cipher(unsigned char cin[], unsigned int w[], int nr, unsigned char cout[]);
extern void InvCipher(unsigned char cin[], unsigned int w[], int nr, unsigned char cout[]);
#endif

////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////

//! @brief number of 64-bit data blocks
#define N 5

//! @brief 64-bit initialization vector
static const unsigned char iv[8] = { 0xa6, 0xa6, 0xa6, 0xa6, 0xa6, 0xa6, 0xa6, 0xa6 };
//! @brief 64-bit integrity check register
static unsigned char a[8];
//! @brief 8-bit array of 64-bit registers
static unsigned char r[8 * (N + 1)];

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////

// See aes128_key_wrap_unwrap.h for documentation on this function.
void do_aes128_key_wrap(const unsigned char plaintext[],
                        unsigned char wrapped_ciphertext[],
                        unsigned int expanded_kek[])
{
    unsigned int i, j;    // loop counters
    unsigned char in[16]; // 128-bit temporary plaintext input vector

    // step 1: initialize the byte-sized data variables
    // set A = IV
    // for i = 1 to n
    //     R[i] = P[i]

    a[0] = iv[0];
    a[1] = iv[1];
    a[2] = iv[2];
    a[3] = iv[3];
    a[4] = iv[4];
    a[5] = iv[5];
    a[6] = iv[6];
    a[7] = iv[7];

    for (i = 1; i <= N; i++)
    {
        r[8 * i + 0] = plaintext[8 * (i - 1) + 0];
        r[8 * i + 1] = plaintext[8 * (i - 1) + 1];
        r[8 * i + 2] = plaintext[8 * (i - 1) + 2];
        r[8 * i + 3] = plaintext[8 * (i - 1) + 3];
        r[8 * i + 4] = plaintext[8 * (i - 1) + 4];
        r[8 * i + 5] = plaintext[8 * (i - 1) + 5];
        r[8 * i + 6] = plaintext[8 * (i - 1) + 6];
        r[8 * i + 7] = plaintext[8 * (i - 1) + 7];
    }

    // step 2: calculate intermediate values
    // for j = 0 to 5
    //     for i = 1 to n
    //         B = AES(K, A | R[i])
    //         A = MSB(64, B) ^ (n*j)+i
    //         R[i] = LSB(64, B)

    for (j = 0; j <= 5; j++)
    {
        for (i = 1; i <= N; i++)
        {
            in[0] = a[0];
            in[1] = a[1];
            in[2] = a[2];
            in[3] = a[3];
            in[4] = a[4];
            in[5] = a[5];
            in[6] = a[6];
            in[7] = a[7];

            in[8] = r[8 * i + 0];
            in[9] = r[8 * i + 1];
            in[10] = r[8 * i + 2];
            in[11] = r[8 * i + 3];
            in[12] = r[8 * i + 4];
            in[13] = r[8 * i + 5];
            in[14] = r[8 * i + 6];
            in[15] = r[8 * i + 7];

#if defined BOOTLOADER_HOST
            Cipher(in, expanded_kek, 10, in); // perform aes128 encryption
#else
            aes_encrypt((unsigned int *)in, expanded_kek, (unsigned int *)in);
#endif // BOOTLOADER_HOST

            a[0] = in[0];
            a[1] = in[1];
            a[2] = in[2];
            a[3] = in[3];
            a[4] = in[4];
            a[5] = in[5];
            a[6] = in[6];
            a[7] = in[7] ^ ((N * j) + i);

            r[8 * i + 0] = in[8];
            r[8 * i + 1] = in[9];
            r[8 * i + 2] = in[10];
            r[8 * i + 3] = in[11];
            r[8 * i + 4] = in[12];
            r[8 * i + 5] = in[13];
            r[8 * i + 6] = in[14];
            r[8 * i + 7] = in[15];
        } // end for (i)
    }     // end for (j)

    // step 3: output the results
    // set C[0] = A
    // for i = 1 to n
    //     C[i] = R[i]

    wrapped_ciphertext[0] = a[0];
    wrapped_ciphertext[1] = a[1];
    wrapped_ciphertext[2] = a[2];
    wrapped_ciphertext[3] = a[3];
    wrapped_ciphertext[4] = a[4];
    wrapped_ciphertext[5] = a[5];
    wrapped_ciphertext[6] = a[6];
    wrapped_ciphertext[7] = a[7];

    for (i = 1; i <= N; i++)
    {
        wrapped_ciphertext[8 * i + 0] = r[8 * i + 0];
        wrapped_ciphertext[8 * i + 1] = r[8 * i + 1];
        wrapped_ciphertext[8 * i + 2] = r[8 * i + 2];
        wrapped_ciphertext[8 * i + 3] = r[8 * i + 3];
        wrapped_ciphertext[8 * i + 4] = r[8 * i + 4];
        wrapped_ciphertext[8 * i + 5] = r[8 * i + 5];
        wrapped_ciphertext[8 * i + 6] = r[8 * i + 6];
        wrapped_ciphertext[8 * i + 7] = r[8 * i + 7];
    }
}

//******************************************************************************
//******************************************************************************

// See aes128_key_wrap_unwrap.h for documentation on this function.
unsigned int do_aes128_key_unwrap(const unsigned char wrapped_ciphertext[],
                                  unsigned char unwrapped_plaintext[],
                                  unsigned int expanded_kek[])
{
    signed int i, j;      // loop counters
    unsigned char in[16]; // 128-bit temporary ciphertext input vector

    // step 1: initialize variables
    // set A = C[0]
    // for i = 1 to n
    //     R[i] = C[i]

    a[0] = wrapped_ciphertext[0];
    a[1] = wrapped_ciphertext[1];
    a[2] = wrapped_ciphertext[2];
    a[3] = wrapped_ciphertext[3];
    a[4] = wrapped_ciphertext[4];
    a[5] = wrapped_ciphertext[5];
    a[6] = wrapped_ciphertext[6];
    a[7] = wrapped_ciphertext[7];

    for (i = 1; i <= N; i++)
    {
        r[8 * i + 0] = wrapped_ciphertext[8 * i + 0];
        r[8 * i + 1] = wrapped_ciphertext[8 * i + 1];
        r[8 * i + 2] = wrapped_ciphertext[8 * i + 2];
        r[8 * i + 3] = wrapped_ciphertext[8 * i + 3];
        r[8 * i + 4] = wrapped_ciphertext[8 * i + 4];
        r[8 * i + 5] = wrapped_ciphertext[8 * i + 5];
        r[8 * i + 6] = wrapped_ciphertext[8 * i + 6];
        r[8 * i + 7] = wrapped_ciphertext[8 * i + 7];
    }

    // step 2: calculate intermediate values
    // for j = 5 to 0
    //     for i = n to 1
    //         B = AES-1(K, (A ^ (n*j+i) | R[i])
    //         A = MSB(64, B)
    //         R[i] = LSB(64, B)

    for (j = 5; j >= 0; j--)
    {
        for (i = N; i >= 1; i--)
        {
            in[0] = a[0];
            in[1] = a[1];
            in[2] = a[2];
            in[3] = a[3];
            in[4] = a[4];
            in[5] = a[5];
            in[6] = a[6];
            in[7] = a[7] ^ ((N * j) + i);

            in[8] = r[8 * i + 0];
            in[9] = r[8 * i + 1];
            in[10] = r[8 * i + 2];
            in[11] = r[8 * i + 3];
            in[12] = r[8 * i + 4];
            in[13] = r[8 * i + 5];
            in[14] = r[8 * i + 6];
            in[15] = r[8 * i + 7];

#if defined BOOTLOADER_HOST
            InvCipher(in, expanded_kek, 10, in); // perform aes128 decryption
#else
            // TODO aes_decrypt reverses bytes(?)
            aes_decrypt((unsigned int *)in, expanded_kek, (unsigned int *)in);
#endif // BOOTLOADER_HOST

            a[0] = in[0];
            a[1] = in[1];
            a[2] = in[2];
            a[3] = in[3];
            a[4] = in[4];
            a[5] = in[5];
            a[6] = in[6];
            a[7] = in[7];

            r[8 * i + 0] = in[8];
            r[8 * i + 1] = in[9];
            r[8 * i + 2] = in[10];
            r[8 * i + 3] = in[11];
            r[8 * i + 4] = in[12];
            r[8 * i + 5] = in[13];
            r[8 * i + 6] = in[14];
            r[8 * i + 7] = in[15];
        } // end for (i)
    }     // end for (j)

    // step 3: output the results
    // if A == IV
    //    then
    //         for i = 1 to n
    //             P[i] = R[i]
    //    else
    //         return an error

    unwrapped_plaintext[0] = a[0];
    unwrapped_plaintext[1] = a[1];
    unwrapped_plaintext[2] = a[2];
    unwrapped_plaintext[3] = a[3];
    unwrapped_plaintext[4] = a[4];
    unwrapped_plaintext[5] = a[5];
    unwrapped_plaintext[6] = a[6];
    unwrapped_plaintext[7] = a[7];

    for (i = 1; i <= N; i++)
    {
        unwrapped_plaintext[8 * i + 0] = r[8 * i + 0];
        unwrapped_plaintext[8 * i + 1] = r[8 * i + 1];
        unwrapped_plaintext[8 * i + 2] = r[8 * i + 2];
        unwrapped_plaintext[8 * i + 3] = r[8 * i + 3];
        unwrapped_plaintext[8 * i + 4] = r[8 * i + 4];
        unwrapped_plaintext[8 * i + 5] = r[8 * i + 5];
        unwrapped_plaintext[8 * i + 6] = r[8 * i + 6];
        unwrapped_plaintext[8 * i + 7] = r[8 * i + 7];
    }

    if ((unwrapped_plaintext[0] == iv[0]) && (unwrapped_plaintext[1] == iv[1]) && (unwrapped_plaintext[2] == iv[2]) &&
        (unwrapped_plaintext[3] == iv[3]) && (unwrapped_plaintext[4] == iv[4]) && (unwrapped_plaintext[5] == iv[5]) &&
        (unwrapped_plaintext[6] == iv[6]) && (unwrapped_plaintext[7] == iv[7]))
        return 0; // error-free exit
    else
        return -1; // error exit
}

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
