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

#include "fsl_common.h"
#include "srecord_image.h"
#include "blsh/bllibc.h"
#include "blsh/host_command.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

typedef struct _srecord_t
{
    uint8_t type;      /*!< Record number type, such as 9 for "S9", 3 for "S3" and so on.*/
    uint8_t count;     /*!< Number of character pairs (bytes) from address through checksum.*/
    uint32_t address;  /*!< The address specified as part of the S-record.*/
    uint8_t dataCount; /*!< Number of bytes of data.*/
    uint8_t data[256]; /*!< Pointer to data, or NULL if no data for this record type.*/
    uint8_t checksum;  /*!< The checksum byte present in the S-record.*/
} srecord_t;

/*******************************************************************************
 * Variables
 ******************************************************************************/
static srecord_t s_new_record = { 0 };

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static recordStatus_t srecord_parse_line(uint8_t *line, uint8_t line_length);
static recordStatus_t srecord_build_image(srecord_t *new_record);
static recordStatus_t srecord_erase_target(uint32_t image_address);
static recordStatus_t srecord_erase_region(srecord_t *new_record);

/*******************************************************************************
 * Code
 ******************************************************************************/

recordStatus_t srecord_image_program(uint32_t image_address)
{
    uint8_t image_char = 0;
    uint32_t image_index = 0;
    uint8_t line_buffer[256] = { 0 };
    uint8_t line_index = 0;
    recordStatus_t status = kRecordStatus_Fail;

    /* Traverse the first time to erase target flash regions*/
    srecord_erase_target(image_address);

    /* Clear globle variable*/
    s_image_buffer_index = 0;
    s_image_start_address = 0;
    s_image_next_address = 0;
    s_image_base_address = 0;

    /* Traverse the second time to program target*/
    while (status != kRecordStatus_FlashOver)
    {
        image_char = read_flash_char(image_address, image_index);
        image_index++;

        if (image_char == '\n')
        {
            status = srecord_parse_line(line_buffer, line_index);
            if (status != kRecordStatus_Success)
            {
                return status;
            }
            line_index = 0;

            /* Build image and flash target*/
            status = srecord_build_image(&s_new_record);

            if (status == kRecordStatus_Fail)
            {
                return kStatus_Fail;
            }
        }
        else if (image_char == '\r')
        {
            continue;
        }
        else
        {
            line_buffer[line_index++] = image_char;
        }
    }

    return kRecordStatus_Success;
}

/*!
 * @brief parse one line of srecord record image
 *
 * @param line one line of the srecord record.
 * @param line_length the length of the line.
 * @return parse status
 */
static recordStatus_t srecord_parse_line(uint8_t *line, uint8_t line_length)
{
    uint32_t checksum = 0;
    uint32_t i = 0;
    srecord_t *new_record = &s_new_record;

    if (line_length < SRECORD_MIN_LENGTH)
    {
        return kRecordStatus_InvalidLength;
    }

    if (line[0] != SRECORD_START_CHAR)
    {
        return kRecordStatus_InvalidStart;
    }

    /* Parse type field*/
    if ((line[1] > '9') || (line[1] < '0'))
    {
        return kRecordStatus_InvalidType;
    }
    new_record->type = line[1] - '0';

    /* Parse count field*/
    new_record->count = read_hex_byte(line, 2);
    checksum += new_record->count;

    /* verify the record length now that we know the count*/
    if (line_length != 4 + new_record->count * 2)
    {
        return kRecordStatus_InvalidLength;
    }

    /* Get address length*/
    uint8_t address_length = 0;
    uint8_t has_data = 0;
    switch (new_record->type)
    {
        case 0:
            address_length = 2;
            has_data = 1;
            break;
        case 1:
            address_length = 2;
            has_data = 1;
            break;
        case 2:
            address_length = 3;
            has_data = 1;
            break;
        case 3:
            address_length = 4;
            has_data = 1;
            break;
        case 5:
            address_length = 2;
            break;
        case 7:
            address_length = 4;
            break;
        case 8:
            address_length = 3;
            break;
        case 9:
            address_length = 2;
            break;
        default:
            return kRecordStatus_InvalidType;
    }

    /* Read address*/
    uint32_t address = 0;
    for (i = 0; i < address_length; i++)
    {
        uint8_t address_byte = read_hex_byte(line, SRECORD_ADDRESS_START_CHAR_INDEX + i * 2);
        address = (address << 8) | address_byte;
        checksum += address_byte;
    }
    new_record->address = address;

    /* Read data*/
    if (has_data)
    {
        int32_t data_start_char_index = 4 + address_length * 2;
        int32_t data_length = new_record->count - address_length - 1;

        for (i = 0; i < data_length; i++)
        {
            uint8_t data_byte = read_hex_byte(line, data_start_char_index + i * 2);
            new_record->data[i] = data_byte;
            checksum += data_byte;
        }
        new_record->dataCount = data_length;
    }

    /* Read and compare checksum byte*/
    checksum = (~checksum) & 0xff; /* low byte of one's complement of sum of other bytes */
    new_record->checksum = read_hex_byte(line, line_length - 2);
    if (checksum != new_record->checksum)
    {
        return kRecordStatus_InvalidChecksum;
    }

    return kRecordStatus_Success;
}

/*!
 * @brief build srecord image and flash target
 *
 * @param new_record one line of the intelhex record.
 * @return parse status
 */
static recordStatus_t srecord_build_image(srecord_t *new_record)
{
    uint8_t is_data_record = 0;
    uint8_t has_data = 0;
    uint32_t status = 0;

    /* Handle S3, 2, 1 records */
    if ((new_record->type == 3) || (new_record->type == 2) || (new_record->type == 1))
    {
        is_data_record = 1;
    }
    has_data = (new_record->data) && (new_record->dataCount);
    if (is_data_record && has_data)
    {
        if (s_image_buffer_index)
        {
            /* If this record's data would overflow the collection buffer, or if the */
            /* record is not contiguous with the rest of the data in the collection */
            /* buffer, then flush the buffer to the executable image and restart. */
            if (((s_image_buffer_index + new_record->dataCount) > IMAGE_BUFFER_SIZE) ||
                (new_record->address != s_image_next_address))
            {
                /* TO-DO flush */
                status = handle_writeMemory_command(s_image_start_address, s_image_buffer, s_image_buffer_index);
                s_image_buffer_index = 0;

                if (status == kStatus_Fail)
                {
                    return kStatus_Fail;
                }
            }
        }

        /* Capture addresses when starting an empty buffer. */
        if (s_image_buffer_index == 0)
        {
            s_image_start_address = new_record->address;
            s_image_next_address = s_image_start_address;
        }

        /* Copy record data into place in the collection buffer and update */
        /* size and address. */
        memcpy(&s_image_buffer[s_image_buffer_index], new_record->data, new_record->dataCount);
        s_image_buffer_index += new_record->dataCount;
        s_image_next_address += new_record->dataCount;
    }
    else if ((new_record->type == 7) || (new_record->type == 8) || (new_record->type == 9))
    {
        /* Flash any leftover data to target. */
        if (s_image_buffer_index)
        {
            status = handle_writeMemory_command(s_image_start_address, s_image_buffer, s_image_buffer_index);
            s_image_buffer_index = 0;

            if (status == kStatus_Fail)
            {
                return kRecordStatus_Fail;
            }

            return kRecordStatus_FlashOver;
        }
    }

    return kRecordStatus_Success;
}

/*!
 * @brief erase target flash before program target
 *
 * @param image_address address of the image in host flash.
 * @return parse status
 */
static recordStatus_t srecord_erase_target(uint32_t image_address)
{
    uint8_t image_char = 0;
    uint32_t image_index = 0;
    uint8_t line_buffer[256] = { 0 };
    uint8_t line_index = 0;
    recordStatus_t status = kRecordStatus_Fail;

    while (status != kRecordStatus_EraseOver)
    {
        image_char = read_flash_char(image_address, image_index);
        image_index++;

        if (image_char == '\n')
        {
            status = srecord_parse_line(line_buffer, line_index);
            if (status != kRecordStatus_Success)
            {
                return status;
            }
            line_index = 0;

            /* Erase target */
            status = srecord_erase_region(&s_new_record);
        }
        else if (image_char == '\r')
        {
            continue;
        }
        else
        {
            line_buffer[line_index++] = image_char;
        }
    }

    return kRecordStatus_Success;
}

/*!
 * @brief eraset flash region based on record
 *
 * @param new_record one line of the intelhex record.
 * @return parse status
 */
static recordStatus_t srecord_erase_region(srecord_t *new_record)
{
    uint8_t is_data_record = 0;
    uint8_t has_data = 0;

    /* Handle S3, 2, 1 records */
    if ((new_record->type == 3) || (new_record->type == 2) || (new_record->type == 1))
    {
        is_data_record = 1;
    }
    has_data = (new_record->data) && (new_record->dataCount);
    if (is_data_record && has_data)
    {
        if (s_image_buffer_index)
        {
            /* If this record's data would overflow the collection buffer, or if the */
            /* record is not contiguous with the rest of the data in the collection */
            /* buffer, then erase the flash region and restart. */
            if (((s_image_buffer_index + new_record->dataCount) > IMAGE_BUFFER_SIZE) ||
                (new_record->address != s_image_next_address))
            {
                /* Erase target flash region */
                handle_flashEraseRegion_command(s_image_start_address, s_image_buffer_index);
                s_image_buffer_index = 0;
            }
        }

        /* Capture addresses when starting an empty buffer. */
        if (s_image_buffer_index == 0)
        {
            s_image_start_address = new_record->address;
            s_image_next_address = s_image_start_address;
        }

        /* Update size and address. */
        s_image_buffer_index += new_record->dataCount;
        s_image_next_address += new_record->dataCount;
    }
    else if ((new_record->type == 7) || (new_record->type == 8) || (new_record->type == 9))
    {
        /* Erase target flash region */
        if (s_image_buffer_index)
        {
            handle_flashEraseRegion_command(s_image_start_address, s_image_buffer_index);
            s_image_buffer_index = 0;

            return kRecordStatus_EraseOver;
        }
    }

    return kRecordStatus_Success;
}
