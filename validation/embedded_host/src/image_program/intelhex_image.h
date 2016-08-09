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

#ifndef __intelhex_image_H__
#define __intelhex_image_H__

#include "executable_image.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
enum
{
    /*! The required first character of a Intel Hex */
    INTELHEX_START_CHAR = ':',

    /*! The minimum length of a Hex. This is the start char (1) + datacount (2) + addr (4) + type (2) + check sum (2).
       */
    INTELHEX_MIN_LENGTH = 11,

    /*! Index of the first character of the address field. */
    INTELHEX_ADDRESS_START_CHAR_INDEX = 3,

    /*! Index of the first character of the record type field. */
    INTELHEX_TYPE_START_CHAR_INDEX = 7,

    /*! Index of the first character of the record type field. */
    INTELHEX_DATA_START_CHAR_INDEX = 9
};

/*! Intel Hex Record Type */
enum
{
    /*! Data Record, which contains data and a 16-bit start address for the data. */
    INTELHEX_RECORD_DATA = 0x00,

    /*! End of File Record, which specifies the end of the hex file, and */
    /*! must occur exactly once per file in the last line of the file. */
    INTELHEX_RECORD_END_OF_FILE = 0x01,

    /*! Extended Segment Address Record, which is used to specify bits 4- 19 of the Segment Base Address. */
    INTELHEX_RECORD_EXTENDED_SEGMENT_ADDRESS = 0x02,

    /*! Start Segment Address Record, which is used to specify the execution start address for the object file. */
    INTELHEX_RECORD_START_SEGMENT_ADDRESS = 0x03,

    /*! Extended Linear Address Record, which is used to specify bits 16- 31 of the Linear Base Address. */
    INTELHEX_RECORD_EXTENDED_LINEAR_ADDRESS = 0x04,

    /*! Start Linear Address Record, which is used to specify the execution start address for the object file. */
    INTELHEX_RECORD_START_LINEAR_ADDRESS = 0x05
};

/*******************************************************************************
 * API
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*! @brief  parse srecord image */
recordStatus_t intelhex_image_program(uint32_t image_address);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* __intelhex_image_H__ */
