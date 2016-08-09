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

#include "SB_image.h"
#include "blsh/host_command.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static uint32_t get_SB_image_length(uint32_t image_address);

/*******************************************************************************
 * Code
 ******************************************************************************/

recordStatus_t SB_image_program(uint32_t image_address)
{
    uint32_t image_length = get_SB_image_length(image_address);

    if (handle_receiveSBFile_command(IMAGE_START_ADDRESS, image_length) != kStatus_Success)
    {
        return kRecordStatus_Fail;
    }

    return kRecordStatus_Success;
}

/*!
 * @brief get SB image length
 *
 * @param image_address image address in target flash.
 * @return the length of sb image
 */
static uint32_t get_SB_image_length(uint32_t image_address)
{
    /* uint8_t  hex[4] = {0}; */
    uint32_t image_blocks = 0;

    image_blocks = read_flash_char(image_address, SB_IMAGE_BLOCKS_OFFSET + 3) << 24;
    image_blocks |= read_flash_char(image_address, SB_IMAGE_BLOCKS_OFFSET + 2) << 16;
    image_blocks |= read_flash_char(image_address, SB_IMAGE_BLOCKS_OFFSET + 1) << 8;
    image_blocks |= read_flash_char(image_address, SB_IMAGE_BLOCKS_OFFSET);

    /* Size of each block is 16 bytes */
    return (image_blocks << 4);
}
