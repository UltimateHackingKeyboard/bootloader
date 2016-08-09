/*
 * Copyright (c) 2013 - 2014, Freescale Semiconductor, Inc.
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

#ifndef __executable_image_H__
#define __executable_image_H__

#include <stdint.h>

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#define IMAGE_BUFFER_SIZE 1024 * 16
#define IMAGE_START_ADDRESS 0x00010000

/*! Image type value. */
enum
{
    kImageType_SB = 0,
    kImageType_Srecord = 1,
    kImageType_Intelhex = 2,
    kImageType_Binary = 3,
    kImageType_Invalid = 4
};

enum
{
    /*! The sb image sign. */
    SB_SIGN1 = 'S',
    SB_SIGN2 = 'T',
    SB_SIGN3 = 'M',
    SB_SIGN4 = 'P',
    /*! The sign offeset form start address. */
    SB_SIGN_OFFSET1 = 20,
    SB_SIGN_OFFSET2 = 21,
    SB_SIGN_OFFSET3 = 22,
    SB_SIGN_OFFSET4 = 23
};

enum
{
    /*! The srecord image sign. */
    SRECORD_SIGN = 'S',
    /*! The sign offeset form start address. */
    SRECORD_SIGN_OFFSET = 0
};

enum
{
    /*! The intelhex image sign. */
    INTELHEX_SIGN = ':',
    /*! The sign offeset form start address. */
    INTELHEX_SIGN_OFFSET = 0
};

enum _recordStatus_t
{
    kRecordStatus_Success = 0,
    kRecordStatus_Fail = 1,
    kRecordStatus_InvalidLength = 2,
    kRecordStatus_InvalidStart = 3,
    kRecordStatus_InvalidType = 4,
    kRecordStatus_InvalidChecksum = 5,
    kRecordStatus_FlashOver = 6,
    kRecordStatus_FlashPartly = 7,
    kRecordStatus_EraseOver = 8,
    kRecordStatus_ErasePartly = 9
};
typedef uint8_t recordStatus_t;

//! @brief Type of callback for flash image status
typedef void (*flash_image_status_t)(recordStatus_t status);

extern uint8_t s_image_buffer[IMAGE_BUFFER_SIZE];
extern uint32_t s_image_buffer_index;
extern uint32_t s_image_start_address;
extern uint32_t s_image_next_address;
extern uint32_t s_image_base_address;

/*******************************************************************************
 * API
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*! @brief read a char from flash region */
uint8_t read_flash_char(uint32_t address, uint32_t index);

/*! @brief get image type */
uint8_t get_image_type();

/*! @brief falsh_image function */
recordStatus_t flash_image(flash_image_status_t function);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* __executable_image_H__ */
