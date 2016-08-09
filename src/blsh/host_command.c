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

#include "host_command.h"
#include "host_hardware.h"
#include "microseconds/microseconds.h"
#include "bllibc.h"
#include "bootloader_config.h"
#include "crc/crc16.h"

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*! @brief command start. */
static const uint8_t k_commandPing[] = { kFramingPacketStartByte, kFramingPacketType_Ping };
static const uint8_t k_commandAck[] = { kFramingPacketStartByte, kFramingPacketType_Ack };

/* Default transfer bus */
#if BL_CONFIG_SPI
static uint8_t s_current_bus = kSPI_mode;
transfer_data_t write_serial_data = send_spi_data;
transfer_data_t read_serial_data = receive_spi_data;
#elif BL_CONFIG_I2C
static uint8_t s_current_bus = kI2C_mode;
transfer_data_t write_serial_data = send_i2c_data;
transfer_data_t read_serial_data = receive_i2c_data;
#elif BL_CONFIG_UART
static uint8_t s_current_bus = kUART_mode;
transfer_data_t write_serial_data = send_uart_data;
transfer_data_t read_serial_data = receive_uart_data;
#if defined(CPU_MK65FN2M0VMI18)
#elif BL_CONFIG_CAN
static uint8_t s_current_bus = kCAN_mode;
transfer_data_t write_serial_data = send_can_data;
transfer_data_t read_serial_data = receive_can_data;
#endif
#endif

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*!
 * @brief static local function prototypes
 */
/*! @brief no data phase command protocol process */
static status_t run_noDataPhase_command(command_frame_packet_t *command, void *command_response);

static status_t run_SBfile_command(command_frame_packet_t *command,
                                   generic_response_frame_packet_t *command_response,
                                   uint32_t address);

static status_t run_writeMemory_command(command_frame_packet_t *command,
                                        generic_response_frame_packet_t *command_response,
                                        uint8_t *memory_data);

static status_t run_readMemory_command(command_frame_packet_t *command,
                                       generic_response_frame_packet_t *command_response,
                                       uint8_t *memory_data);

static status_t wait_data_packet(serial_framing_packet_t *data_packet, uint32_t length);

static void read_flash(uint32_t address, uint8_t *buffer, uint32_t bytes);

/*******************************************************************************
 * Code
 ******************************************************************************/

status_t handle_getProperty_command(uint8_t property_tag, uint32_t *response_param)
{
    /* Command response */
    property_response_frame_packet_t command_response;
    /* Command packet. */
    command_frame_packet_t getProperty_command;
    crc16_data_t crc16_value;
    crc16_init(&crc16_value);

    /* Packet */
    getProperty_command.framing_data.header.startByte = kFramingPacketStartByte;
    getProperty_command.framing_data.header.packetType = kFramingPacketType_Command;
    getProperty_command.framing_data.length = 0x0c;
    getProperty_command.command_data.commandTag = kCommandTag_GetProperty;
    getProperty_command.command_data.flags = 0x00;
    getProperty_command.command_data.reserved = 0x00;
    getProperty_command.command_data.parameterCount = 0x02;
    getProperty_command.param[0] = property_tag;
    getProperty_command.param[1] = 0;

    /* Claulate crc16 value */
    crc16_update(&crc16_value, (uint8_t *)&getProperty_command.framing_data,
                 sizeof(framing_data_packet_t) - sizeof(uint16_t));
    crc16_update(&crc16_value, (uint8_t *)&getProperty_command.command_data.commandTag,
                 getProperty_command.framing_data.length);
    getProperty_command.framing_data.crc16 = crc16_value.currentCrc;

    /* Handle command */
    command_response.generic_response.status = kStatus_Fail;
    if (run_noDataPhase_command(&getProperty_command, &command_response) != kStatus_Success)
    {
        return kStatus_Fail;
    }

    if (command_response.generic_response.status == kStatus_Success)
    {
        /* Response result */
        response_param[0] = command_response.generic_response.commandPacket.parameterCount;
        for (int32_t i = 1; i < response_param[0]; i++)
        {
            response_param[i] = command_response.generic_response.propertyValue[i - 1];
        }
    }

    return command_response.generic_response.status;
}

status_t handle_setProperty_command(uint8_t property_tag, uint32_t property_value)
{
    /* Command response */
    property_response_frame_packet_t command_response;
    /* Command packet. */
    command_frame_packet_t setProperty_command;
    crc16_data_t crc16_value;
    crc16_init(&crc16_value);

    /* Packet */
    setProperty_command.framing_data.header.startByte = kFramingPacketStartByte;
    setProperty_command.framing_data.header.packetType = kFramingPacketType_Command;
    setProperty_command.framing_data.length = 0x0c;
    setProperty_command.command_data.commandTag = kCommandTag_SetProperty;
    setProperty_command.command_data.flags = 0x00;
    setProperty_command.command_data.reserved = 0x00;
    setProperty_command.command_data.parameterCount = 0x02;
    setProperty_command.param[0] = property_tag;
    setProperty_command.param[1] = property_value;

    /* Claulate crc16 value */
    crc16_update(&crc16_value, (uint8_t *)&setProperty_command.framing_data,
                 sizeof(framing_data_packet_t) - sizeof(uint16_t));
    crc16_update(&crc16_value, (uint8_t *)&setProperty_command.command_data.commandTag,
                 setProperty_command.framing_data.length);
    setProperty_command.framing_data.crc16 = crc16_value.currentCrc;

    /* Handle command */
    command_response.generic_response.status = kStatus_Fail;
    if (run_noDataPhase_command(&setProperty_command, &command_response) != kStatus_Success)
    {
        return kStatus_Fail;
    }

    return command_response.generic_response.status;
}

status_t handle_reset_command(void)
{
    /* Command response */
    generic_response_frame_packet_t command_response;
    /* Command packet. */
    command_frame_packet_t reset_command;
    crc16_data_t crc16_value;
    crc16_init(&crc16_value);

    /* Packet */
    reset_command.framing_data.header.startByte = kFramingPacketStartByte;
    reset_command.framing_data.header.packetType = kFramingPacketType_Command;
    reset_command.framing_data.length = 0x0004;
    reset_command.command_data.commandTag = kCommandTag_Reset;
    reset_command.command_data.flags = 0x00;
    reset_command.command_data.reserved = 0x00;
    reset_command.command_data.parameterCount = 0x00;

    /* Claulate crc16 value */
    crc16_update(&crc16_value, (uint8_t *)&reset_command.framing_data,
                 sizeof(framing_data_packet_t) - sizeof(uint16_t));
    crc16_update(&crc16_value, (uint8_t *)&reset_command.command_data.commandTag, reset_command.framing_data.length);
    reset_command.framing_data.crc16 = crc16_value.currentCrc;

    /* Handle command */
    command_response.status = kStatus_Fail;

    if (run_noDataPhase_command(&reset_command, &command_response) != kStatus_Success)
    {
        return kStatus_Fail;
    }

    return command_response.status;
}

status_t handle_flashEraseAllUnsecure_command(void)
{
    /* Command response */
    generic_response_frame_packet_t command_response;
    /* Command packet. */
    command_frame_packet_t flashEraseAllUnsecure_command;
    crc16_data_t crc16_value;
    crc16_init(&crc16_value);

    /* Packet */
    flashEraseAllUnsecure_command.framing_data.header.startByte = kFramingPacketStartByte;
    flashEraseAllUnsecure_command.framing_data.header.packetType = kFramingPacketType_Command;
    flashEraseAllUnsecure_command.framing_data.length = 0x0004;
    flashEraseAllUnsecure_command.command_data.commandTag = kCommandTag_FlashEraseAllUnsecure;
    flashEraseAllUnsecure_command.command_data.flags = 0x00;
    flashEraseAllUnsecure_command.command_data.reserved = 0x00;
    flashEraseAllUnsecure_command.command_data.parameterCount = 0x00;

    /* Claulate crc16 value */
    crc16_update(&crc16_value, (uint8_t *)&flashEraseAllUnsecure_command.framing_data,
                 sizeof(framing_data_packet_t) - sizeof(uint16_t));
    crc16_update(&crc16_value, (uint8_t *)&flashEraseAllUnsecure_command.command_data.commandTag,
                 flashEraseAllUnsecure_command.framing_data.length);
    flashEraseAllUnsecure_command.framing_data.crc16 = crc16_value.currentCrc;

    /* Handle command */
    command_response.status = kStatus_Fail;

    if (run_noDataPhase_command(&flashEraseAllUnsecure_command, &command_response) != kStatus_Success)
    {
        return kStatus_Fail;
    }

    return command_response.status;
}

status_t handle_flashEraseAll_command(void)
{
    /* Command response */
    generic_response_frame_packet_t command_response;
    /* Command packet. */
    command_frame_packet_t flashEraseAll_command;
    crc16_data_t crc16_value;
    crc16_init(&crc16_value);

    /* Packet */
    flashEraseAll_command.framing_data.header.startByte = kFramingPacketStartByte;
    flashEraseAll_command.framing_data.header.packetType = kFramingPacketType_Command;
    flashEraseAll_command.framing_data.length = 0x0004;
    flashEraseAll_command.command_data.commandTag = kCommandTag_FlashEraseAll;
    flashEraseAll_command.command_data.flags = 0x00;
    flashEraseAll_command.command_data.reserved = 0x00;
    flashEraseAll_command.command_data.parameterCount = 0x00;

    /* Claulate crc16 value */
    crc16_update(&crc16_value, (uint8_t *)&flashEraseAll_command.framing_data,
                 sizeof(framing_data_packet_t) - sizeof(uint16_t));
    crc16_update(&crc16_value, (uint8_t *)&flashEraseAll_command.command_data.commandTag,
                 flashEraseAll_command.framing_data.length);
    flashEraseAll_command.framing_data.crc16 = crc16_value.currentCrc;

    /* Handle command */
    command_response.status = kStatus_Fail;

    if (run_noDataPhase_command(&flashEraseAll_command, &command_response) != kStatus_Success)
    {
        return kStatus_Fail;
    }

    return command_response.status;
}

status_t handle_flashEraseRegion_command(uint32_t start_address, uint32_t erase_bytes)
{
    /* Command response */
    generic_response_frame_packet_t command_response;
    /* Command packet. */
    command_frame_packet_t flashEraseRegion_command;
    crc16_data_t crc16_value;
    crc16_init(&crc16_value);

    /* Erase bytes count must be a multiple of 512 */
    if (erase_bytes % 512)
    {
        if (erase_bytes > 512)
        {
            erase_bytes = ((erase_bytes >> 9) + 1) << 9;
        }
        else
        {
            erase_bytes = 512;
        }
    }

    /* Packet */
    flashEraseRegion_command.framing_data.header.startByte = kFramingPacketStartByte;
    flashEraseRegion_command.framing_data.header.packetType = kFramingPacketType_Command;
    flashEraseRegion_command.framing_data.length = 0x000c;
    flashEraseRegion_command.command_data.commandTag = kCommandTag_FlashEraseRegion;
    flashEraseRegion_command.command_data.flags = 0x00;
    flashEraseRegion_command.command_data.reserved = 0x00;
    flashEraseRegion_command.command_data.parameterCount = 0x02;
    flashEraseRegion_command.param[0] = start_address;
    flashEraseRegion_command.param[1] = erase_bytes;

    /* Claulate crc16 value */
    crc16_update(&crc16_value, (uint8_t *)&flashEraseRegion_command.framing_data,
                 sizeof(framing_data_packet_t) - sizeof(uint16_t));
    crc16_update(&crc16_value, (uint8_t *)&flashEraseRegion_command.command_data.commandTag,
                 flashEraseRegion_command.framing_data.length);
    flashEraseRegion_command.framing_data.crc16 = crc16_value.currentCrc;

    /* Handle command */
    command_response.status = kStatus_Fail;

    if (run_noDataPhase_command(&flashEraseRegion_command, &command_response) != kStatus_Success)
    {
        blsh_printf("\r\n Erase fail!");
        return kStatus_Fail;
    }

    if (command_response.status == kStatus_Success)
    {
        blsh_printf("\r\n Erase flash region OK! ");
    }
    else
    {
        blsh_printf("\r\n Erase fail!");
    }

    return command_response.status;
}

status_t handle_receiveSBFile_command(uint32_t address, uint32_t length)
{
    /* Command response */
    generic_response_frame_packet_t command_response;
    /* Command packet. */
    command_frame_packet_t receiveSBFile_command;
    crc16_data_t crc16_value;
    crc16_init(&crc16_value);

    /* Packet */
    receiveSBFile_command.framing_data.header.startByte = kFramingPacketStartByte;
    receiveSBFile_command.framing_data.header.packetType = kFramingPacketType_Command;
    receiveSBFile_command.framing_data.length = 0x0008;
    receiveSBFile_command.command_data.commandTag = kCommandTag_ReceiveSbFile;
    receiveSBFile_command.command_data.flags = 0x01;
    receiveSBFile_command.command_data.reserved = 0x00;
    receiveSBFile_command.command_data.parameterCount = 0x01;
    receiveSBFile_command.param[0] = length;

    /* Claulate crc16 value */
    crc16_update(&crc16_value, (uint8_t *)&receiveSBFile_command.framing_data,
                 sizeof(framing_data_packet_t) - sizeof(uint16_t));
    crc16_update(&crc16_value, (uint8_t *)&receiveSBFile_command.command_data.commandTag,
                 receiveSBFile_command.framing_data.length);
    receiveSBFile_command.framing_data.crc16 = crc16_value.currentCrc;

    command_response.status = kStatus_Fail;
    if (run_SBfile_command(&receiveSBFile_command, &command_response, address) != kStatus_Success)
    {
        return kStatus_Fail;
    }

    // return command_response.status;
    return kStatus_Success;
}

status_t handle_writeMemory_command(uint32_t start_address, uint8_t *buffer, uint32_t length)
{
    /* Command response. */
    generic_response_frame_packet_t command_response;
    /* Command packet. */
    command_frame_packet_t writeMemory_command;
    crc16_data_t crc16_value;
    crc16_init(&crc16_value);

    /* Packet */
    writeMemory_command.framing_data.header.startByte = kFramingPacketStartByte;
    writeMemory_command.framing_data.header.packetType = kFramingPacketType_Command;
    writeMemory_command.framing_data.length = 0x000c;
    writeMemory_command.command_data.commandTag = kCommandTag_WriteMemory;
    writeMemory_command.command_data.flags = 0x01;
    writeMemory_command.command_data.reserved = 0x00;
    writeMemory_command.command_data.parameterCount = 0x02;
    writeMemory_command.param[0] = start_address;
    writeMemory_command.param[1] = length;

    /* Claulate crc16 value */
    crc16_update(&crc16_value, (uint8_t *)&writeMemory_command.framing_data,
                 sizeof(framing_data_packet_t) - sizeof(uint16_t));
    crc16_update(&crc16_value, (uint8_t *)&writeMemory_command.command_data.commandTag,
                 writeMemory_command.framing_data.length);
    writeMemory_command.framing_data.crc16 = crc16_value.currentCrc;

    /* Flash target */
    command_response.status = kStatus_Fail;

    if (run_writeMemory_command(&writeMemory_command, &command_response, buffer) != kStatus_Success)
    {
        return kStatus_Fail;
    }

    return command_response.status;
}

status_t handle_readMemory_command(uint32_t start_address, uint8_t *buffer, uint32_t length)
{
    /* Command response. */
    generic_response_frame_packet_t command_response;
    /* Command packet. */
    command_frame_packet_t readMemory_command;
    crc16_data_t crc16_value;
    crc16_init(&crc16_value);

    /* Packet */
    readMemory_command.framing_data.header.startByte = kFramingPacketStartByte;
    readMemory_command.framing_data.header.packetType = kFramingPacketType_Command;
    readMemory_command.framing_data.length = 0x000c;
    readMemory_command.command_data.commandTag = kCommandTag_ReadMemory;
    readMemory_command.command_data.flags = 0x00;
    readMemory_command.command_data.reserved = 0x00;
    readMemory_command.command_data.parameterCount = 0x02;
    readMemory_command.param[0] = start_address;
    readMemory_command.param[1] = length;

    /* Claulate crc16 value */
    crc16_update(&crc16_value, (uint8_t *)&readMemory_command.framing_data,
                 sizeof(framing_data_packet_t) - sizeof(uint16_t));
    crc16_update(&crc16_value, (uint8_t *)&readMemory_command.command_data.commandTag,
                 readMemory_command.framing_data.length);
    readMemory_command.framing_data.crc16 = crc16_value.currentCrc;

    /* Read memory */
    command_response.status = kStatus_Fail;
    if (run_readMemory_command(&readMemory_command, &command_response, buffer) != kStatus_Success)
    {
        return kStatus_Fail;
    }

    return command_response.status;
}

status_t handle_fillMemory_command(uint32_t start_address, uint32_t pattern_word, uint32_t byte_count)
{
    /* Command response. */
    generic_response_frame_packet_t command_response;
    /* Command packet. */
    command_frame_packet_t fillMemory_command;
    crc16_data_t crc16_value;
    crc16_init(&crc16_value);

    /* Packet */
    fillMemory_command.framing_data.header.startByte = kFramingPacketStartByte;
    fillMemory_command.framing_data.header.packetType = kFramingPacketType_Command;
    fillMemory_command.framing_data.length = 0x0010;
    fillMemory_command.command_data.commandTag = kCommandTag_FillMemory;
    fillMemory_command.command_data.flags = 0x00;
    fillMemory_command.command_data.reserved = 0x00;
    fillMemory_command.command_data.parameterCount = 0x03;
    fillMemory_command.param[0] = start_address;
    fillMemory_command.param[1] = byte_count;
    fillMemory_command.param[2] = pattern_word;

    /* Claulate crc16 value */
    crc16_update(&crc16_value, (uint8_t *)&fillMemory_command.framing_data,
                 sizeof(framing_data_packet_t) - sizeof(uint16_t));
    crc16_update(&crc16_value, (uint8_t *)&fillMemory_command.command_data.commandTag,
                 fillMemory_command.framing_data.length);
    fillMemory_command.framing_data.crc16 = crc16_value.currentCrc;

    /* Execute command */
    command_response.status = kStatus_Fail;

    if (run_noDataPhase_command(&fillMemory_command, &command_response) != kStatus_Success)
    {
        return kStatus_Fail;
    }

    return command_response.status;
}

status_t handle_flashSecurityDisable_command(uint32_t backdoorkey_low, uint32_t backdoorkey_high)
{
    /* Command response. */
    generic_response_frame_packet_t command_response;
    /* Command packet. */
    command_frame_packet_t flashSecurityDisable_command;
    crc16_data_t crc16_value;
    crc16_init(&crc16_value);

    /* Packet */
    flashSecurityDisable_command.framing_data.header.startByte = kFramingPacketStartByte;
    flashSecurityDisable_command.framing_data.header.packetType = kFramingPacketType_Command;
    flashSecurityDisable_command.framing_data.length = 0x000c;
    flashSecurityDisable_command.command_data.commandTag = kCommandTag_FlashSecurityDisable;
    flashSecurityDisable_command.command_data.flags = 0x00;
    flashSecurityDisable_command.command_data.reserved = 0x00;
    flashSecurityDisable_command.command_data.parameterCount = 0x02;
    flashSecurityDisable_command.param[0] = backdoorkey_low;
    flashSecurityDisable_command.param[1] = backdoorkey_high;

    /* Claulate crc16 value */
    crc16_update(&crc16_value, (uint8_t *)&flashSecurityDisable_command.framing_data,
                 sizeof(framing_data_packet_t) - sizeof(uint16_t));
    crc16_update(&crc16_value, (uint8_t *)&flashSecurityDisable_command.command_data.commandTag,
                 flashSecurityDisable_command.framing_data.length);
    flashSecurityDisable_command.framing_data.crc16 = crc16_value.currentCrc;

    /* Execute command */
    command_response.status = kStatus_Fail;

    if (run_noDataPhase_command(&flashSecurityDisable_command, &command_response) != kStatus_Success)
    {
        return kStatus_Fail;
    }

    return command_response.status;
}

status_t handle_execute_command(uint32_t address, uint32_t arg, uint32_t stack_pointer)
{
    /* Command response. */
    generic_response_frame_packet_t command_response;
    /* Command packet. */
    command_frame_packet_t execute_command;
    crc16_data_t crc16_value;
    crc16_init(&crc16_value);

    /* Packet */
    execute_command.framing_data.header.startByte = kFramingPacketStartByte;
    execute_command.framing_data.header.packetType = kFramingPacketType_Command;
    execute_command.framing_data.length = 0x0010;
    execute_command.command_data.commandTag = kCommandTag_Execute;
    execute_command.command_data.flags = 0x00;
    execute_command.command_data.reserved = 0x00;
    execute_command.command_data.parameterCount = 0x03;
    execute_command.param[0] = address;
    execute_command.param[1] = arg;
    execute_command.param[2] = stack_pointer;

    /* Claulate crc16 value */
    crc16_update(&crc16_value, (uint8_t *)&execute_command.framing_data,
                 sizeof(framing_data_packet_t) - sizeof(uint16_t));
    crc16_update(&crc16_value, (uint8_t *)&execute_command.command_data.commandTag,
                 execute_command.framing_data.length);
    execute_command.framing_data.crc16 = crc16_value.currentCrc;

    /* Execute command */
    command_response.status = kStatus_Fail;

    if (run_noDataPhase_command(&execute_command, &command_response) != kStatus_Success)
    {
        return kStatus_Fail;
    }

    return command_response.status;
}

status_t handle_call_command(uint32_t address, uint32_t arg)
{
    /* Command response. */
    generic_response_frame_packet_t command_response;
    /* Command packet. */
    command_frame_packet_t call_command;
    crc16_data_t crc16_value;
    crc16_init(&crc16_value);

    /* Packet */
    call_command.framing_data.header.startByte = kFramingPacketStartByte;
    call_command.framing_data.header.packetType = kFramingPacketType_Command;
    call_command.framing_data.length = 0x000c;
    call_command.command_data.commandTag = kCommandTag_Call;
    call_command.command_data.flags = 0x00;
    call_command.command_data.reserved = 0x00;
    call_command.command_data.parameterCount = 0x02;
    call_command.param[0] = address;
    call_command.param[1] = arg;

    /* Claulate crc16 value */
    crc16_update(&crc16_value, (uint8_t *)&call_command.framing_data, sizeof(framing_data_packet_t) - sizeof(uint16_t));
    crc16_update(&crc16_value, (uint8_t *)&call_command.command_data.commandTag, call_command.framing_data.length);
    call_command.framing_data.crc16 = crc16_value.currentCrc;

    /* Execute command */
    command_response.status = kStatus_Fail;

    if (run_noDataPhase_command(&call_command, &command_response) != kStatus_Success)
    {
        return kStatus_Fail;
    }

    return command_response.status;
}

status_t handle_flashProgramOnce_command(uint32_t index, uint32_t byte_count, uint32_t data1, uint32_t data2)
{
    /* Command response. */
    generic_response_frame_packet_t command_response;
    /* Command packet. */
    command_frame_packet_t flashProgramOnce_command;
    crc16_data_t crc16_value;
    crc16_init(&crc16_value);

    /* Packet */
    flashProgramOnce_command.framing_data.header.startByte = kFramingPacketStartByte;
    flashProgramOnce_command.framing_data.header.packetType = kFramingPacketType_Command;
    flashProgramOnce_command.framing_data.length = (byte_count > 4 ? 0x0014 : 0x0010);
    flashProgramOnce_command.command_data.commandTag = kCommandTag_FlashProgramOnce;
    flashProgramOnce_command.command_data.flags = 0x00;
    flashProgramOnce_command.command_data.reserved = 0x00;
    flashProgramOnce_command.command_data.parameterCount = (byte_count > 4 ? 0x04 : 0x03);
    flashProgramOnce_command.param[0] = index;
    flashProgramOnce_command.param[1] = byte_count;
    flashProgramOnce_command.param[2] = data1;
    flashProgramOnce_command.param[3] = data2;

    /* Claulate crc16 value */
    crc16_update(&crc16_value, (uint8_t *)&flashProgramOnce_command.framing_data,
                 sizeof(framing_data_packet_t) - sizeof(uint16_t));
    crc16_update(&crc16_value, (uint8_t *)&flashProgramOnce_command.command_data.commandTag,
                 flashProgramOnce_command.framing_data.length);
    flashProgramOnce_command.framing_data.crc16 = crc16_value.currentCrc;

    /* Execute command */
    command_response.status = kStatus_Fail;

    if (run_noDataPhase_command(&flashProgramOnce_command, &command_response) != kStatus_Success)
    {
        return kStatus_Fail;
    }

    return command_response.status;
}

status_t handle_flashReadOnce_command(uint32_t index, uint32_t byte_count, uint32_t *data1, uint32_t *data2)
{
    /* Command response. */
    flash_read_once_response_frame_packet_t command_response;
    /* Command packet. */
    command_frame_packet_t flashReadOnce_command;
    crc16_data_t crc16_value;
    crc16_init(&crc16_value);

    /* Packet */
    flashReadOnce_command.framing_data.header.startByte = kFramingPacketStartByte;
    flashReadOnce_command.framing_data.header.packetType = kFramingPacketType_Command;
    flashReadOnce_command.framing_data.length = 0x000c;
    flashReadOnce_command.command_data.commandTag = kCommandTag_FlashReadOnce;
    flashReadOnce_command.command_data.flags = 0x00;
    flashReadOnce_command.command_data.reserved = 0x00;
    flashReadOnce_command.command_data.parameterCount = 0x02;
    flashReadOnce_command.param[0] = index;
    flashReadOnce_command.param[1] = byte_count;

    /* Claulate crc16 value */
    crc16_update(&crc16_value, (uint8_t *)&flashReadOnce_command.framing_data,
                 sizeof(framing_data_packet_t) - sizeof(uint16_t));
    crc16_update(&crc16_value, (uint8_t *)&flashReadOnce_command.command_data.commandTag,
                 flashReadOnce_command.framing_data.length);
    flashReadOnce_command.framing_data.crc16 = crc16_value.currentCrc;

    /* Execute command */
    command_response.response.status = kStatus_Fail;

    if (run_noDataPhase_command(&flashReadOnce_command, &command_response) != kStatus_Success)
    {
        return kStatus_Fail;
    }
    *data1 = command_response.response.data[0];
    *data2 = command_response.response.data[1];

    return command_response.response.status;
}

status_t handle_flashReadResource_command(uint32_t start_address, uint8_t *buffer, uint32_t length, uint32_t option)
{
    /* Command response. */
    generic_response_frame_packet_t command_response;
    /* Command packet. */
    command_frame_packet_t flashReadResource_command;
    crc16_data_t crc16_value;
    crc16_init(&crc16_value);

    /* Packet */
    flashReadResource_command.framing_data.header.startByte = kFramingPacketStartByte;
    flashReadResource_command.framing_data.header.packetType = kFramingPacketType_Command;
    flashReadResource_command.framing_data.length = 0x0010;
    flashReadResource_command.command_data.commandTag = kCommandTag_FlashReadResource;
    flashReadResource_command.command_data.flags = 0x00;
    flashReadResource_command.command_data.reserved = 0x00;
    flashReadResource_command.command_data.parameterCount = 0x03;
    flashReadResource_command.param[0] = start_address;
    flashReadResource_command.param[1] = length;
    flashReadResource_command.param[2] = option;

    /* Claulate crc16 value */
    crc16_update(&crc16_value, (uint8_t *)&flashReadResource_command.framing_data,
                 sizeof(framing_data_packet_t) - sizeof(uint16_t));
    crc16_update(&crc16_value, (uint8_t *)&flashReadResource_command.command_data.commandTag,
                 flashReadResource_command.framing_data.length);
    flashReadResource_command.framing_data.crc16 = crc16_value.currentCrc;

    /* Read memory */
    command_response.status = kStatus_Fail;
    if (run_readMemory_command(&flashReadResource_command, &command_response, buffer) != kStatus_Success)
    {
        return kStatus_Fail;
    }

    return command_response.status;
}

/*!
 * @brief no data phase command protocol process.
 *
 * @param command whole command packet.
 * @param command_response command response packet.
 */
static status_t run_noDataPhase_command(command_frame_packet_t *command, void *command_response)
{
    int8_t retry = 0;

    /* Try ping command with 3 times */
    if (wait_ping_response(3) != kStatus_Success)
    {
        return kStatus_Fail;
    }

    /* Send command */
    write_serial_data((uint8_t *)command, sizeof(framing_data_packet_t) + command->framing_data.length);
    blsh_printf("\r\n Inject command '%s'", kCommandNames[command->command_data.commandTag - 1]);

    /* Wait for ack packet */
    retry = 3;
    do
    {
        if (retry <= 0)
        {
            return kStatus_Fail;
        }

        if (wait_ack_packet() == kStatus_Success)
        {
            break;
        }

    } while (retry-- > 0);

    /* Wait for data response */
    wait_command_response(command_response);

    /* Send ack response */
    write_serial_data((uint8_t *)k_commandAck, sizeof(k_commandAck));

    return kStatus_Success;
}

/*!
 * @brief write memory command protocol process.
 *
 * @param command whole command packet.
 * @param command_response command response packet.
 * @param memory_data the data written to the memory.
 */
static status_t run_writeMemory_command(command_frame_packet_t *command,
                                        generic_response_frame_packet_t *command_response,
                                        uint8_t *memory_data)
{
    uint32_t data_packet_num = 0;
    uint32_t data_length = command->param[1];
    uint32_t image_index = 0;
    crc16_data_t crc16_value;
    crc16_init(&crc16_value);

    /* Calculate data packet num to send */
    if (data_length % kOutgoingPacketBufferSize)
    {
        data_packet_num = (data_length >> 5) + 1;
    }
    else
    {
        data_packet_num = (data_length >> 5);
    }

    /* Try ping command with 3 times */
    if (wait_ping_response(3) != kStatus_Success)
    {
        return kStatus_Fail;
    }

    /* Send command */
    write_serial_data((uint8_t *)command, sizeof(framing_data_packet_t) + command->framing_data.length);
    blsh_printf("\r\n Inject command '%s'", kCommandNames[command->command_data.commandTag - 1]);

    /* Wait for ack packet */
    if (wait_ack_packet() == kStatus_Fail)
    {
        return kStatus_Fail;
    }

    /* Wait for initial response */
    wait_command_response(command_response);

    /* Send ack response */
    write_serial_data((uint8_t *)k_commandAck, sizeof(k_commandAck));

    /* Send Data */
    serial_framing_packet_t data_packet;
    data_packet.dataPacket.header.startByte = kFramingPacketStartByte;
    data_packet.dataPacket.header.packetType = kFramingPacketType_Data;

    while (data_packet_num)
    {
        if (data_length > kOutgoingPacketBufferSize)
        {
            data_packet.dataPacket.length = kOutgoingPacketBufferSize;

            for (int32_t i = 0; i < kOutgoingPacketBufferSize; i++)
            {
                data_packet.data[i] = memory_data[image_index];
                image_index++;
            }
            data_length -= kOutgoingPacketBufferSize;
        }
        else
        {
            data_packet.dataPacket.length = data_length;

            for (int32_t i = 0; i < data_length; i++)
            {
                data_packet.data[i] = memory_data[image_index];
                image_index++;
            }
            data_length = 0;
        }

        crc16_init(&crc16_value);
        crc16_update(&crc16_value, (uint8_t *)&data_packet.dataPacket,
                     sizeof(framing_data_packet_t) - sizeof(uint16_t));
        crc16_update(&crc16_value, (uint8_t *)data_packet.data, data_packet.dataPacket.length);
        data_packet.dataPacket.crc16 = crc16_value.currentCrc;

        /* Send command */
        write_serial_data((uint8_t *)&data_packet, sizeof(framing_data_packet_t) + data_packet.dataPacket.length);

        /* Wait for ack packet */
        uint8_t retry = 3;
        do
        {
            if (retry <= 0)
            {
                return kStatus_Fail;
            }

            if (wait_ack_packet() == kStatus_Success)
            {
                break;
            }
        } while (retry-- > 0);

        data_packet_num--;
    }

    /* Wait for final response */
    wait_command_response(command_response);

    /* Send ack response */
    write_serial_data((uint8_t *)k_commandAck, sizeof(k_commandAck));

    return kStatus_Success;
}

/*!
 * @brief read memory command protocol process.
 *
 * @param command whole command packet.
 * @param command_response command response packet.
 * @param memory_data the data read from memory.
 */
static status_t run_readMemory_command(command_frame_packet_t *command,
                                       generic_response_frame_packet_t *command_response,
                                       uint8_t *memory_data)
{
    uint32_t data_packet_num = 0;
    uint32_t data_length = command->param[1];
    uint32_t image_index = 0;
    crc16_data_t crc16_value;
    crc16_init(&crc16_value);

    /* Calculate data packet num to receive */
    if (data_length % kOutgoingPacketBufferSize)
    {
        data_packet_num = (data_length >> 5) + 1;
    }
    else
    {
        data_packet_num = (data_length >> 5);
    }

    /* Try ping command with 3 times */
    if (wait_ping_response(3) != kStatus_Success)
    {
        return kStatus_Fail;
    }

    /* Send command */
    write_serial_data((uint8_t *)command, sizeof(framing_data_packet_t) + command->framing_data.length);
    blsh_printf("\r\n Inject command '%s'", kCommandNames[command->command_data.commandTag - 1]);

    /* Wait for ack packet */
    if (wait_ack_packet() == kStatus_Fail)
    {
        return kStatus_Fail;
    }

    /* Wait for initial response */
    wait_command_response(command_response);
    if (command_response->status != kStatus_Success)
    {
        return command_response->status;
    }

    /* Send ack response */
    write_serial_data((uint8_t *)k_commandAck, sizeof(k_commandAck));

    /* Receive Data */
    serial_framing_packet_t data_packet = { 0 };
    while (data_packet_num)
    {
        if (data_length > kOutgoingPacketBufferSize)
        {
            /* Receive data phase packet */
            if (wait_data_packet(&data_packet, data_length) != kStatus_Success)
            {
                return kStatus_Fail;
            }
            for (int32_t i = 0; i < kOutgoingPacketBufferSize; i++)
            {
                memory_data[image_index] = data_packet.data[i];
                image_index++;
            }
            data_length -= kOutgoingPacketBufferSize;
        }
        else
        {
            /* Receive data phase packet */
            if (wait_data_packet(&data_packet, data_length) != kStatus_Success)
            {
                return kStatus_Fail;
            }
            for (int32_t i = 0; i < data_length; i++)
            {
                memory_data[image_index] = data_packet.data[i];
                image_index++;
            }
            data_length = 0;
        }

        /* Send ack packet */
        write_serial_data((uint8_t *)k_commandAck, sizeof(k_commandAck));

        data_packet_num--;
    }

    /* Wait for final response */
    wait_command_response(command_response);

    /* Send ack response */
    write_serial_data((uint8_t *)k_commandAck, sizeof(k_commandAck));

    return kStatus_Success;
}

/*!
 * @brief receive sb file command protocol process.
 *
 * @param command whole command packet.
 * @param command_response command response packet.
 * @param address the start address of sb image written to the target.
 */
static status_t run_SBfile_command(command_frame_packet_t *command,
                                   generic_response_frame_packet_t *command_response,
                                   uint32_t address)
{
    uint32_t data_packet_num = 0;
    uint32_t data_length = command->param[0];
    int32_t ack_value = 0;
    crc16_data_t crc16_value;
    crc16_init(&crc16_value);

    /* Calculate data packet num to send */
    if (data_length % kOutgoingPacketBufferSize)
    {
        data_packet_num = (data_length >> 5) + 1;
    }
    else
    {
        data_packet_num = (data_length >> 5);
    }

    /* Try ping command with 3 times */
    if (wait_ping_response(3) != kStatus_Success)
    {
        return kStatus_Fail;
    }

    /* Send command */
    write_serial_data((uint8_t *)command, sizeof(framing_data_packet_t) + command->framing_data.length);
    blsh_printf("\r\n Inject command '%s'", kCommandNames[command->command_data.commandTag - 1]);

    /* Wait for ack packet */
    if (wait_ack_packet() == kStatus_Fail)
    {
        return kStatus_Fail;
    }

    /* Wait for initial response */
    wait_command_response(command_response);

    /* Send ack response */
    write_serial_data((uint8_t *)k_commandAck, sizeof(k_commandAck));

    /* Send Data */
    serial_framing_packet_t data_packet;
    data_packet.dataPacket.header.startByte = kFramingPacketStartByte;
    data_packet.dataPacket.header.packetType = kFramingPacketType_Data;

    while (data_packet_num)
    {
        if (data_length > kOutgoingPacketBufferSize)
        {
            data_packet.dataPacket.length = kOutgoingPacketBufferSize;

            /* Read data */
            read_flash(address, data_packet.data, kOutgoingPacketBufferSize);
            data_length -= kOutgoingPacketBufferSize;
            address += kOutgoingPacketBufferSize;
        }
        else
        {
            data_packet.dataPacket.length = data_length;
            /* Read data */
            read_flash(address, data_packet.data, data_length);

            data_length = 0;
        }

        crc16_init(&crc16_value);
        crc16_update(&crc16_value, (uint8_t *)&data_packet.dataPacket,
                     sizeof(framing_data_packet_t) - sizeof(uint16_t));
        crc16_update(&crc16_value, (uint8_t *)data_packet.data, data_packet.dataPacket.length);
        data_packet.dataPacket.crc16 = crc16_value.currentCrc;

        /* Send command */
        write_serial_data((uint8_t *)&data_packet, sizeof(framing_data_packet_t) + data_packet.dataPacket.length);

        /* Wait for ack packet */
        uint8_t retry = 3;
        do
        {
            if (retry <= 0)
            {
                return kStatus_Fail;
            }

            ack_value = wait_ack_packet();
            if ((ack_value == kStatus_Success) || (ack_value == kStatus_OutOfRange))
            {
                break;
            }
        } while (retry-- > 0);

        /* Finish receive sb file abort unused data */
        if (ack_value == kStatus_OutOfRange)
        {
            break;
        }

        data_packet_num--;
    }

    /* Wait for final response */
    wait_command_response(command_response);

    /* Send ack response */
    write_serial_data((uint8_t *)k_commandAck, sizeof(k_commandAck));

    return kStatus_Success;
}

/*!
 * @brief read flash data.
 *
 * @param address the start address of reading flash.
 * @param buffer the buffer to store flash data.
 * @param bytes the number of reading bytes.
 */
static void read_flash(uint32_t address, uint8_t *buffer, uint32_t bytes)
{
    for (uint32_t i = 0; i < bytes; i++)
    {
        *(buffer + i) = *(uint8_t *)address++;
    }
}

status_t get_memory_info(memory_info_t *info)
{
    uint32_t property_value[4][2] = { 0 };
    uint32_t reserved_regions[5] = { 0 };

    if (info->is_info_reday == false)
    {
        /* Get property of memory */
        if (handle_getProperty_command(kPropertyTag_FlashStartAddress, property_value[0]) != kStatus_Success)
            return kStatus_Fail;
        if (handle_getProperty_command(kPropertyTag_FlashSizeInBytes, property_value[1]) != kStatus_Success)
            return kStatus_Fail;
        if (handle_getProperty_command(kPropertyTag_RAMStartAddress, property_value[2]) != kStatus_Success)
            return kStatus_Fail;
        if (handle_getProperty_command(kPropertyTag_RAMSizeInBytes, property_value[3]) != kStatus_Success)
            return kStatus_Fail;
        if (handle_getProperty_command(kPropertyTag_ReservedRegions, reserved_regions) != kStatus_Success)
            return kStatus_Fail;

        info->flashStart = property_value[0][1];
        info->flashSize = property_value[1][1];
        info->ramStart = property_value[2][1];
        info->ramSize = property_value[3][1];
        info->reservedFlashStart = reserved_regions[1];
        info->reservedFlashEnd = reserved_regions[2];
        info->reservedRamStart = reserved_regions[3];
        info->reservedRamEnd = reserved_regions[4];

        /* Caluclate the blank area */
        info->blankFlashStart =
            info->reservedFlashEnd > info->flashStart ? (info->reservedFlashEnd + 1) : (info->flashStart);
        info->blankFlashSize = info->flashStart + info->flashSize - info->blankFlashStart;

        info->blankRamStart = info->reservedRamEnd > info->ramStart ? (info->reservedRamEnd + 1) : (info->ramStart);
        info->blankRamSize = info->ramStart + info->ramSize - info->blankRamStart;

        info->is_info_reday = true;
    }

    return kStatus_Success;
}

status_t get_command_info(command_info_t *info)
{
    uint32_t property_value[2] = { 0 };
    if (info->is_info_reday == false)
    {
        if (handle_getProperty_command(kPropertyTag_AvailableCommands, &property_value[0]) != kStatus_Success)
            return kStatus_Fail;

        info->cmd_mask = property_value[1];
        info->is_info_reday = true;
    }

    return kStatus_Success;
}

void check_transfer_bus(uint8_t transfer_bus, uint32_t *input_freq)
{
    uint32_t *freq = input_freq;

    if (transfer_bus == kUART_mode)
    {
        if (*freq < kUART_MIN_BAUD)
        {
            *freq = kUART_DEFAULT_BAUD;
            blsh_printf("\r\n The frequency is adjusted to 19200. ");
        }
    }
#if defined(CPU_MK65FN2M0VMI18)
    else if (transfer_bus == kCAN_mode)
    {
        if (*freq <= kFLEXCAN_125K)
        {
            *freq = kFLEXCAN_125K;
            blsh_printf("\r\n The frequency is adjusted to 125K. ");
        }
        else if (*freq <= kFLEXCAN_250K)
        {
            *freq = kFLEXCAN_250K;
            blsh_printf("\r\n The frequency is adjusted to 250K. ");
        }
        else if (*freq <= kFLEXCAN_500K)
        {
            *freq = kFLEXCAN_500K;
            blsh_printf("\r\n The frequency is adjusted to 500K. ");
        }
        else
        {
            *freq = kFLEXCAN_1000K;
            blsh_printf("\r\n The frequency is adjusted to 1000K. ");
        }
    }
#endif
}

void configure_transfer_bus(uint8_t transfer_bus, uint32_t freq)
{
    if ((s_current_bus != transfer_bus) || (s_current_bus == kUART_mode))
    {
        s_current_bus = transfer_bus;
        if (handle_reset_command() == kStatus_Success)
        {
            blsh_printf("\r\n The target has reset successfully. ");
        }
        else
        {
            blsh_printf("\r\n Reset fail");
        }
    }

    if (transfer_bus == kSPI_mode)
    {
        write_serial_data = send_spi_data;
        read_serial_data = receive_spi_data;
        configure_spi_speed(freq);
    }
    else if (transfer_bus == kI2C_mode)
    {
        write_serial_data = send_i2c_data;
        read_serial_data = receive_i2c_data;
        configure_i2c_speed(freq);
    }
    else if (transfer_bus == kUART_mode)
    {
        write_serial_data = send_uart_data;
        read_serial_data = receive_uart_data;
        configure_uart_speed(freq);
    }
#if defined(CPU_MK65FN2M0VMI18)
    else if (transfer_bus == kCAN_mode)
    {
        write_serial_data = send_can_data;
        read_serial_data = receive_can_data;
        configure_can_speed(freq);
    }
#endif
}

status_t run_ping_command(void)
{
    uint8_t data[10] = { 0 };
    uint8_t recvStart = 0;
    uint8_t packetType = 0;
    uint64_t timeoutTicks = microseconds_get_ticks() + microseconds_convert_to_ticks(2000000); /* 2s time out */

    write_serial_data((uint8_t *)k_commandPing, sizeof(k_commandPing));
    /* Wait start byte response */
    microseconds_delay(100);
    while ((recvStart != kFramingPacketStartByte) && (microseconds_get_ticks() < timeoutTicks))
    {
        read_serial_data(&recvStart, 1);
    }

    if (recvStart != kFramingPacketStartByte)
    {
        return kStatus_Fail;
    }
    read_serial_data(&packetType, 1);
    if (packetType != kFramingPacketType_PingResponse)
    {
        return kStatus_Fail;
    }
    read_serial_data(data, 8);
    return kStatus_Success;
}

status_t wait_ping_response(uint8_t try_count)
{
    for (uint8_t i = 1; i <= try_count; i++)
    {
        if (run_ping_command() == kStatus_Success)
        {
            blsh_printf("\r\n Ping responded in %d attempt(s)", i);
            return kStatus_Success;
        }
    }

    blsh_printf("\r\n Error: Initial ping failure: No response received for ping command");
    return kStatus_Fail;
}

status_t wait_ack_packet(void)
{
    uint8_t recvStart = 0;
    uint8_t packetType = 0;
    uint64_t timeoutTicks = microseconds_get_ticks() + microseconds_convert_to_ticks(5000000); /* 5s time out */

    /* Wait start byte response */
    microseconds_delay(100);
    while ((recvStart != kFramingPacketStartByte) && (microseconds_get_ticks() < timeoutTicks))
    {
        read_serial_data(&recvStart, 1);
    }

    if (recvStart != kFramingPacketStartByte)
    {
        return kStatus_Fail;
    }
    read_serial_data(&packetType, 1);

    if (packetType == kFramingPacketType_Ack)
    {
        return kStatus_Success;
    }
    else if (packetType == kFramingPacketType_AckAbort)
    {
        return kStatus_OutOfRange;
    }
    else if (packetType == kFramingPacketType_Nak)
    {
        return kStatus_Fail;
    }
    else
    {
        return kStatus_Fail;
    }
}

status_t wait_command_response(generic_response_frame_packet_t *command_response)
{
    uint16_t length_rev = 0;
    uint16_t crc_rev = 0;
    uint8_t recvStart = 0;
    uint8_t packetType = 0;
    uint64_t timeoutTicks = microseconds_get_ticks() + microseconds_convert_to_ticks(5000000); /* 5s time out */

    /* Wait start byte response */
    microseconds_delay(100);
    while ((recvStart != kFramingPacketStartByte) && (microseconds_get_ticks() < timeoutTicks))
    {
        read_serial_data(&recvStart, 1);
    }

    if (recvStart != kFramingPacketStartByte)
    {
        return kStatus_Fail;
    }
    read_serial_data(&packetType, 1);

    if (packetType == kFramingPacketType_Command)
    {
        read_serial_data((uint8_t *)&length_rev, sizeof(uint16_t));
        read_serial_data((uint8_t *)&crc_rev, sizeof(uint16_t));

        command_response->framing_data.header.startByte = kFramingPacketStartByte;
        command_response->framing_data.header.packetType = kFramingPacketType_Command;
        command_response->framing_data.length = length_rev;
        command_response->framing_data.crc16 = crc_rev;

        read_serial_data((uint8_t *)&command_response->commandTag, command_response->framing_data.length);

        return kStatus_Success;
    }
    else
    {
        return kStatus_Fail;
    }
}

/*!
 * @brief  wait data packet when read memory.
 *
 * @param data_packet data packet for store memory data.
 * @param length the length to read.
 * @return status_t the status value
 */
static status_t wait_data_packet(serial_framing_packet_t *data_packet, uint32_t length)
{
    uint16_t length_rev = 0;
    uint16_t crc_rev = 0;
    uint8_t recvStart = 0;
    uint8_t packetType = 0;
    uint64_t timeoutTicks = microseconds_get_ticks() + microseconds_convert_to_ticks(5000000); /* 5s time out */

    /* Wait start byte response */
    microseconds_delay(100);
    while ((recvStart != kFramingPacketStartByte) && (microseconds_get_ticks() < timeoutTicks))
    {
        read_serial_data(&recvStart, 1);
    }

    if (recvStart != kFramingPacketStartByte)
    {
        return kStatus_Fail;
    }
    read_serial_data(&packetType, 1);

    /* Receive data phase packet */
    if (packetType == kFramingPacketType_Data)
    {
        read_serial_data((uint8_t *)&length_rev, sizeof(uint16_t));
        read_serial_data((uint8_t *)&crc_rev, sizeof(uint16_t));

        data_packet->dataPacket.header.startByte = kFramingPacketStartByte;
        data_packet->dataPacket.header.packetType = kFramingPacketType_Data;
        data_packet->dataPacket.length = length_rev;
        data_packet->dataPacket.crc16 = crc_rev;

        read_serial_data((uint8_t *)&data_packet->data, length);
        return kStatus_Success;
    }
    else
    {
        return kStatus_Fail;
    }
}