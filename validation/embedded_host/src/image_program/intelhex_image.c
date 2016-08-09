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
#include "intelhex_image.h"
#include "blsh/bllibc.h"
#include "blsh/host_command.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

typedef struct _intelhex_record_t
{
    uint8_t dataCount; /*!< The number of bytes in the data field. */
    uint32_t address;  /*!< The address offset of the data. */
    uint8_t type;      /*!< Type of the data field. 00: Data */
                       /*!<                         01: End of File */
                       /*!<                         02: Extended Segment Address */
                       /*!<                         03: Start Segment Address */
                       /*!<                         04: Extended Linear Address */
                       /*!<                         05: Start Linear Address */
    uint8_t data[256]; /*!< Pointer to data, or NULL if no data for this record. */
    uint8_t checksum;  /*!< The checksum byte used to verify the record. */
} intelhex_record_t;

/*******************************************************************************
 * Variables
 ******************************************************************************/
static intelhex_record_t s_new_record = { 0 };

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static recordStatus_t intelhex_record_parse_line(uint8_t *line, uint8_t line_length);
static recordStatus_t intelhex_record_build_image(intelhex_record_t *new_record);
static recordStatus_t intelhex_record_erase_target(uint32_t image_address);
static recordStatus_t intelhex_record_erase_region(intelhex_record_t *new_record);

/*******************************************************************************
 * Code
 ******************************************************************************/

recordStatus_t intelhex_image_program(uint32_t image_address)
{
    uint8_t image_char = 0;
    uint32_t image_index = 0;
    uint8_t line_buffer[256] = { 0 };
    uint8_t line_index = 0;
    recordStatus_t status = kRecordStatus_Fail;

    /* Traverse the first time to erase target flash regions */
    intelhex_record_erase_target(image_address);

    /* Clear globle variable */
    s_image_buffer_index = 0;
    s_image_start_address = 0;
    s_image_next_address = 0;
    s_image_base_address = 0;

    /* Traverse the second time to program target */
    while (status != kRecordStatus_FlashOver)
    {
        image_char = read_flash_char(image_address, image_index);
        image_index++;

        if (image_char == '\n')
        {
            status = intelhex_record_parse_line(line_buffer, line_index);
            if (status != kRecordStatus_Success)
            {
                return status;
            }
            line_index = 0;

            /* Build image and program target */
            status = intelhex_record_build_image(&s_new_record);

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
 * @brief parse one line of intelhex record image
 *
 * @param line one line of the intelhex record.
 * @param line_length the length of the line.
 * @return parse status
 */
static recordStatus_t intelhex_record_parse_line(uint8_t *line, uint8_t line_length)
{
    uint32_t checksum = 0;
    uint32_t i = 0;
    intelhex_record_t *new_record = &s_new_record;

    /* Must be at least a certain length */
    if (line_length < INTELHEX_MIN_LENGTH)
    {
        return kRecordStatus_InvalidLength;
    }

    /* Start char must be ':' */
    if (line[0] != INTELHEX_START_CHAR)
    {
        return kRecordStatus_InvalidStart;
    }

    /* Parse count field */
    new_record->dataCount = read_hex_byte(line, 1);
    checksum += new_record->dataCount;

    /* verify the record length now that we know the count */
    if (line_length != 11 + new_record->dataCount * 2)
    {
        return kRecordStatus_InvalidLength;
    }

    /* Read address */
    uint32_t address = 0;
    for (i = 0; i < 2; ++i)
    {
        uint8_t address_byte = read_hex_byte(line, INTELHEX_ADDRESS_START_CHAR_INDEX + i * 2);
        address = (address << 8) | address_byte;
        checksum += address_byte;
    }
    new_record->address = address;

    /* Handle data type */
    new_record->type = read_hex_byte(line, INTELHEX_TYPE_START_CHAR_INDEX);
    checksum += new_record->type;
    switch (new_record->type)
    {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
            break;
        default:
            return kRecordStatus_InvalidType;
    }

    /* Read data */
    if (new_record->dataCount)
    {
        for (i = 0; i < new_record->dataCount; ++i)
        {
            uint8_t data_byte = read_hex_byte(line, INTELHEX_DATA_START_CHAR_INDEX + i * 2);
            new_record->data[i] = data_byte;
            checksum += data_byte;
        }
    }

    /* Read and compare checksum byte */
    checksum = (~checksum + 1) & 0xff; /* low byte of one's complement of sum of other bytes */
    new_record->checksum = read_hex_byte(line, line_length - 2);
    if (checksum != new_record->checksum)
    {
        return kRecordStatus_InvalidChecksum;
    }

    return kRecordStatus_Success;
}

/*!
 * @brief build intelhex srecord image and flash target
 *
 * @param new_record one line of the intelhex record.
 * @return parse status
 */
static recordStatus_t intelhex_record_build_image(intelhex_record_t *new_record)
{
    uint8_t is_data_record = 0;
    uint8_t is_entry_record = 0;
    uint8_t is_address_record = 0;
    uint8_t is_eof_record = 0;
    uint32_t status = 0;

    if (new_record->type == INTELHEX_RECORD_DATA)
    {
        is_data_record = 1;
    }
    else if ((new_record->type == INTELHEX_RECORD_START_SEGMENT_ADDRESS) ||
             (new_record->type == INTELHEX_RECORD_START_LINEAR_ADDRESS))
    {
        is_entry_record = 1;
    }
    else if ((new_record->type == INTELHEX_RECORD_EXTENDED_SEGMENT_ADDRESS) ||
             (new_record->type == INTELHEX_RECORD_EXTENDED_LINEAR_ADDRESS))
    {
        is_address_record = 1;
    }
    else if (new_record->type == INTELHEX_RECORD_END_OF_FILE)
    {
        is_eof_record = 1;
    }

    s_image_base_address = 0;
    /* Handle 00 data record */
    if (is_data_record)
    {
        if (s_image_buffer_index)
        {
            /* If this record's data would overflow the collection buffer, or if the */
            /* record is not contiguous with the rest of the data in the collection */
            /* buffer, then flush the buffer to the target and restart. */
            if (((s_image_buffer_index + new_record->dataCount) > IMAGE_BUFFER_SIZE) ||
                (new_record->address != s_image_next_address))
            {
                /* flush the buffer to the target */
                status = handle_writeMemory_command(s_image_start_address + s_image_base_address, s_image_buffer,
                                                    s_image_buffer_index);
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
    /* Hnadle 02, 04 record */
    else if (is_address_record)
    {
        /* If there are data in the collection buffer, then flush the buffer to the target. */
        if (s_image_buffer_index)
        {
            status = handle_writeMemory_command(s_image_start_address + s_image_base_address, s_image_buffer,
                                                s_image_buffer_index);
            s_image_buffer_index = 0;

            if (status == kStatus_Fail)
            {
                return kStatus_Fail;
            }
        }

        /* extended address stored at data field. */
        s_image_base_address = (new_record->data[0] << 8) | new_record->data[1];
        if (new_record->type == INTELHEX_RECORD_EXTENDED_SEGMENT_ADDRESS)
        {
            s_image_base_address <<= 4;
        }
        else
        {
            s_image_base_address <<= 16;
        }
    }
    /* Handle 03, 05 record */
    else if (is_entry_record)
    {
        /* Nothing to do */
    }
    /* Handle 01 record */
    else if (is_eof_record)
    {
        /* Flash any leftover data to target. */
        if (s_image_buffer_index)
        {
            status = handle_writeMemory_command(s_image_start_address, s_image_buffer, s_image_buffer_index);
            s_image_buffer_index = 0;

            if (status == kStatus_Fail)
            {
                return kStatus_Fail;
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
static recordStatus_t intelhex_record_erase_target(uint32_t image_address)
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
            status = intelhex_record_parse_line(line_buffer, line_index);
            if (status != kRecordStatus_Success)
            {
                return status;
            }
            line_index = 0;

            /* Erase flash regions */
            status = intelhex_record_erase_region(&s_new_record);
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
static recordStatus_t intelhex_record_erase_region(intelhex_record_t *new_record)
{
    uint8_t is_data_record = 0;
    uint8_t is_entry_record = 0;
    uint8_t is_address_record = 0;
    uint8_t is_eof_record = 0;

    if (new_record->type == INTELHEX_RECORD_DATA)
    {
        is_data_record = 1;
    }
    else if ((new_record->type == INTELHEX_RECORD_START_SEGMENT_ADDRESS) ||
             (new_record->type == INTELHEX_RECORD_START_LINEAR_ADDRESS))
    {
        is_entry_record = 1;
    }
    else if ((new_record->type == INTELHEX_RECORD_EXTENDED_SEGMENT_ADDRESS) ||
             (new_record->type == INTELHEX_RECORD_EXTENDED_LINEAR_ADDRESS))
    {
        is_address_record = 1;
    }
    else if (new_record->type == INTELHEX_RECORD_END_OF_FILE)
    {
        is_eof_record = 1;
    }

    s_image_base_address = 0;
    /* Handle 00 data record */
    if (is_data_record)
    {
        if (s_image_buffer_index)
        {
            /* If this record's data would overflow the collection buffer, or if the */
            /* record is not contiguous with the rest of the data in the collection */
            /* buffer, then erase flash region and restart. */
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

        /* update size and address. */
        s_image_buffer_index += new_record->dataCount;
        s_image_next_address += new_record->dataCount;
    }
    /* Hnadle 02, 04 record */
    else if (is_address_record)
    {
        /* If there are data in the collection buffer, then flush the buffer to the executable image. */
        if (s_image_buffer_index)
        {
            /* Erase target flash region */
            handle_flashEraseRegion_command(s_image_start_address, s_image_buffer_index);
            s_image_buffer_index = 0;
        }

        /* extended address stored at data field. */
        s_image_base_address = (new_record->data[0] << 8) | new_record->data[1];
        if (new_record->type == INTELHEX_RECORD_EXTENDED_SEGMENT_ADDRESS)
        {
            s_image_base_address <<= 4;
        }
        else
        {
            s_image_base_address <<= 16;
        }
    }
    /* Handle 03, 05 record */
    else if (is_entry_record)
    {
        /* Nothing to do */
    }
    /* Handle 01 record */
    else if (is_eof_record)
    {
        /* Flash any leftover data to target. */
        if (s_image_buffer_index)
        {
            /* Erase target flash region */
            handle_flashEraseRegion_command(s_image_start_address, s_image_buffer_index);
            s_image_buffer_index = 0;

            return kRecordStatus_EraseOver;
        }
    }

    return kRecordStatus_Success;
}
