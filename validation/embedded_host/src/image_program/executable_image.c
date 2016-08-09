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

#include "executable_image.h"
#include "blsh/bllibc.h"
#include "srecord_image.h"
#include "intelhex_image.h"
#include "binary_image.h"
#include "SB_image.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
uint8_t s_image_buffer[IMAGE_BUFFER_SIZE] = { 0 };
uint32_t s_image_buffer_index = 0;
uint32_t s_image_start_address = 0;
uint32_t s_image_next_address = 0;
uint32_t s_image_base_address = 0;

/*******************************************************************************
 * Code
 ******************************************************************************/

uint8_t read_flash_char(uint32_t address, uint32_t index)
{
    return *(uint8_t *)(address + index);
}

uint8_t get_image_type()
{
    if (read_flash_char(IMAGE_START_ADDRESS, SRECORD_SIGN_OFFSET) == SRECORD_SIGN)
    {
        return kImageType_Srecord;
    }
    else if (read_flash_char(IMAGE_START_ADDRESS, INTELHEX_SIGN_OFFSET) == INTELHEX_SIGN)
    {
        return kImageType_Intelhex;
    }
    else if ((read_flash_char(IMAGE_START_ADDRESS, SB_SIGN_OFFSET1) == SB_SIGN1) &&
             (read_flash_char(IMAGE_START_ADDRESS, SB_SIGN_OFFSET2) == SB_SIGN2) &&
             (read_flash_char(IMAGE_START_ADDRESS, SB_SIGN_OFFSET3) == SB_SIGN3) &&
             (read_flash_char(IMAGE_START_ADDRESS, SB_SIGN_OFFSET4) == SB_SIGN4))
    {
        return kImageType_SB;
    }
    else if ((read_flash_char(IMAGE_START_ADDRESS, 0) != 0xff) || (read_flash_char(IMAGE_START_ADDRESS, 1) != 0xff) ||
             (read_flash_char(IMAGE_START_ADDRESS, 2) != 0xff) || (read_flash_char(IMAGE_START_ADDRESS, 3) != 0xff))
    {
        return kImageType_Binary;
    }
    else
    {
        return kImageType_Invalid;
    }
}

recordStatus_t flash_image(flash_image_status_t function)
{
    uint8_t image_type = get_image_type();
    uint32_t status = kRecordStatus_InvalidStart;

    if (image_type == kImageType_Srecord)
    {
        status = srecord_image_program(IMAGE_START_ADDRESS);
    }
    else if (image_type == kImageType_Intelhex)
    {
        status = intelhex_image_program(IMAGE_START_ADDRESS);
    }
    else if (image_type == kImageType_SB)
    {
        status = SB_image_program(IMAGE_START_ADDRESS);
    }
    else if (image_type == kImageType_Binary)
    {
        // status = binary_image_program(IMAGE_START_ADDRESS, 1788);
        status = kRecordStatus_InvalidType;
    }

    if (function != 0)
    {
        function(status);
    }

    return status;
}
