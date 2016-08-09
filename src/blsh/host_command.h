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

#ifndef __HOST_COMMAND_H__
#define __HOST_COMMAND_H__

#include <stdio.h>
#include <stdint.h>
#include "bootloader_common.h"
#include "property/property.h"
#include "packet/serial_packet.h"
#include "blsh.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @brief Transfer bus mode */
enum _transfer_mode_type
{
    kIdle_mode = 0,
    kSPI_mode = 1,
    kI2C_mode = 2,
    kUART_mode = 3,
    kCAN_mode = 4
};

#if DEBUG && !DEBUG_PRINT_DISABLE
/*! @brief Command names */
static const char *const kCommandNames[] = { "flash-erase-all",
                                             "flash-erase-region",
                                             "read-memory",
                                             "write-memory",
                                             "fill-memory",
                                             "flash-security-disable",
                                             "get-property",
                                             "receive-sb-file",
                                             "execute",
                                             "call",
                                             "reset",
                                             "set-property",
                                             "flash-erase-all-unsecure",
                                             "flash-program-once",
                                             "flash-read-once",
                                             "flash-read-resource",
                                             "configure-quadspi",
                                             "reliable-update",
                                             "flash-image",
                                             "i2c",
                                             "spi",
                                             "can" };
#endif

#pragma pack(1)
/*! @brief command packet */
typedef struct _command_frame_packet
{
    framing_data_packet_t framing_data;
    command_packet_t command_data;
    uint32_t param[7];
} command_frame_packet_t;
#pragma pack()

#pragma pack(1)
/*! @brief generic response packet */
typedef struct _generic_response_frame_packet
{
    framing_data_packet_t framing_data;
    uint8_t commandTag;        /*!< A command tag. */
    uint8_t flags;             /*!< Combination of packet flags. */
    uint8_t reserved;          /*!< Reserved, helpful for alignment, set to zero. */
    uint8_t parameterCount;    /*!< Number of parameters that follow in buffer. */
    uint32_t status;           /*!< parameter 0 */
    uint32_t param_commandTag; /*!< parameter 1 */
} generic_response_frame_packet_t;
#pragma pack()

#pragma pack(1)
/*! @brief generic response packet */
typedef struct _flash_read_once_response_frame_packet
{
    framing_data_packet_t framing_data;
    flash_read_once_response_packet_t response;
} flash_read_once_response_frame_packet_t;
#pragma pack()

#pragma pack(1)
/*! @brief generic response packet */
typedef struct _property_response_frame_packet
{
    framing_data_packet_t framing_data;
    get_property_response_packet_t generic_response;
} property_response_frame_packet_t;
#pragma pack()

/*! @brief target memory info */
typedef struct _memory_info
{
    bool is_info_reday;
    uint32_t flashStart;
    uint32_t flashSize;
    uint32_t ramStart;
    uint32_t ramSize;

    uint32_t reservedFlashStart;
    uint32_t reservedFlashEnd;
    uint32_t reservedRamStart;
    uint32_t reservedRamEnd;

    uint32_t blankFlashStart;
    uint32_t blankFlashSize;
    uint32_t blankRamStart;
    uint32_t blankRamSize;
} memory_info_t;

/*! @brief memory test options */
typedef struct _write_memory_test_option
{
    uint32_t address;
    uint32_t writeLength;
    uint32_t testTimes;
    uint64_t averageCost;
    uint32_t averageSpeed;
    uint8_t divider;
} write_memory_test_option_t;

/*! @brief bootloader command info */
typedef struct _command_info
{
    bool is_info_reday;
    uint32_t cmd_mask;
} command_info_t;

/*! @brief Data transfer bus mode(dafault = spi). */
typedef status_t (*transfer_data_t)(uint8_t *data, uint32_t length);
extern transfer_data_t write_serial_data;
extern transfer_data_t read_serial_data;

/*******************************************************************************
 * API
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*! @brief  handle get-property command */
status_t handle_getProperty_command(uint8_t input_param, uint32_t *response_param);

/*! @brief  handle set-property command */
status_t handle_setProperty_command(uint8_t property_tag, uint32_t property_value);

/*! @brief  handle flash-erase-all-unsecure command */
status_t handle_flashEraseAllUnsecure_command(void);

/*! @brief  handle flash-erase-all command */
status_t handle_flashEraseAll_command(void);

/*! @brief  handle flash-erase-region command */
status_t handle_flashEraseRegion_command(uint32_t start_address, uint32_t erase_bytes);

/*! @brief  handle reset target command */
status_t handle_reset_command(void);

/*! @brief  handle write-memory command */
status_t handle_writeMemory_command(uint32_t start_address, uint8_t *buffer, uint32_t length);

/*! @brief  handle read memory command */
status_t handle_readMemory_command(uint32_t start_address, uint8_t *buffer, uint32_t length);

/*! @brief  handle fill memory command */
status_t handle_fillMemory_command(uint32_t start_address, uint32_t pattern_word, uint32_t byte_count);

/*! @brief  handle flash security disable command */
status_t handle_flashSecurityDisable_command(uint32_t backdoorkey_low, uint32_t backdoorkey_high);

/*! @brief  handle execute command */
status_t handle_execute_command(uint32_t address, uint32_t arg, uint32_t stack_pointer);

/*! @brief  handle call command */
status_t handle_call_command(uint32_t address, uint32_t arg);

/*! @brief  handle flash program once command */
status_t handle_flashProgramOnce_command(uint32_t index, uint32_t byte_count, uint32_t data1, uint32_t data2);

/*! @brief  handle flash read once command */
status_t handle_flashReadOnce_command(uint32_t index, uint32_t byte_count, uint32_t *data1, uint32_t *data2);

/*! @brief  handle flash read resource command */
status_t handle_flashReadResource_command(uint32_t start_address, uint8_t *buffer, uint32_t length, uint32_t option);

/*! @brief  handle get-property command */
status_t handle_receiveSBFile_command(uint32_t address, uint32_t length);

/*! @brief  get target flash and ram information */
status_t get_memory_info(memory_info_t *info);

/*! @brief  get target command information */
status_t get_command_info(command_info_t *info);

/*! @brief  send ping command and wait ping response */
status_t run_ping_command(void);

/*! @brief  wait for ping command response */
status_t wait_ping_response(uint8_t try_count);

/*! @brief  wait ack packet */
status_t wait_ack_packet(void);

/*! @brief  wait command response */
status_t wait_command_response(generic_response_frame_packet_t *command_response);

/*! @brief  check transfer bus frequency */
void check_transfer_bus(uint8_t transfer_bus, uint32_t *input_freq);

/*! @brief  configure transfer bus send and receive function */
void configure_transfer_bus(uint8_t transfer_bus, uint32_t freq);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* __HOST_COMMAND_H__ */
