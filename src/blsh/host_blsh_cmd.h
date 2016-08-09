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

#ifndef __HOST_BLSH_CMD_H__
#define __HOST_BLSH_CMD_H__

#include <stdint.h>
#include "blsh.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @brief bus option */
typedef struct _bus_option
{
    uint8_t bus;
    uint32_t freq;
} bus_option_t;

/*! @brief Packetizer status codes. */
enum _packetizer_status
{
    kStatus_NoPingResponse = MAKE_STATUS(kStatusGroup_Packetizer, 0),
    kStatus_InvalidPacketType = MAKE_STATUS(kStatusGroup_Packetizer, 1),
    kStatus_InvalidCRC = MAKE_STATUS(kStatusGroup_Packetizer, 2),
    kStatus_NoCommandResponse = MAKE_STATUS(kStatusGroup_Packetizer, 3)
};

#if defined(BL_EMBEDDED_HOST)

extern blsh_cmd_t flash_image_cmd;
extern blsh_cmd_t write_memory_cmd;
extern blsh_cmd_t read_memory_cmd;
extern blsh_cmd_t fill_memory_cmd;
extern blsh_cmd_t flash_security_disable_cmd;
extern blsh_cmd_t flash_erase_all_cmd;
extern blsh_cmd_t flash_erase_all_unsecure_cmd;
extern blsh_cmd_t flash_erase_region_cmd;
extern blsh_cmd_t execute_cmd;
extern blsh_cmd_t call_cmd;
extern blsh_cmd_t flash_program_once_cmd;
extern blsh_cmd_t flash_read_once_cmd;
extern blsh_cmd_t flash_read_resource_cmd;

#endif

/*******************************************************************************
 * API
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*! @brief initial blsh command and get some information for follow-up work */
void host_blsh_cmd_init(void);

/*! @brief get transfer bus type */
status_t transfer_bus_parse(uint8_t *src, uint8_t *option);

/*! @brief get bus frequency */
status_t transfer_freq_parse(uint8_t *src, uint8_t bus, uint32_t *option);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* __HOST_BLSH_CMD_H__ */
