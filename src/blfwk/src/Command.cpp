/*
 * Copyright (c) 2013-2016, Freescale Semiconductor, Inc.
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

#include "blfwk/Command.h"
#include "blfwk/Logging.h"
#include "bootloader_common.h"
#include "blfwk/json.h"
#include "blfwk/utils.h"
#include "sbloader/sbloader.h"
#include "bootloader/bootloader.h"
#ifdef LINUX
#include <string.h>
#endif

using namespace blfwk;
using namespace utils;
using namespace std;

//#define TEST_SENDER_ABORT
//#define TEST_RECEIVER_ABORT

////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////

//! @brief Value of the terminator code in the g_statusCodes table.
const int32_t kStatusMessageTableTerminatorValue = 0x7fffffff;

//! @brief Status return code descriptions.
StatusMessageTableEntry blfwk::g_statusCodes[] = {
    // Generic statuses.
    { kStatus_Success, "Success." },
    { kStatus_Fail, "Failure." },
    { kStatus_ReadOnly, "kStatus_ReadOnly" },
    { kStatus_OutOfRange, "kStatus_OutOfRange" },
    { kStatus_InvalidArgument, "kStatus_InvalidArgument" },
    { kStatus_Timeout, "kStatus_Timeout" },
    { kStatus_NoTransferInProgress, "kStatus_NoTransferInProgress" },

    // Flash driver errors.
    { 100 /*kStatus_FlashSizeError*/, "kStatus_FlashSizeError" },
    { 101 /*kStatus_FlashAlignmentError*/, "kStatus_FlashAlignmentError" },
    { 102 /*kStatus_FlashAddressError*/, "kStatus_FlashAddressError" },
    { 103 /*kStatus_FlashAccessError*/, "kStatus_FlashAccessError" },
    { 104 /*kStatus_FlashProtectionViolation*/, "kStatus_FlashProtectionViolation" },
    { 105 /*kStatus_FlashCommandFailure*/, "kStatus_FlashCommandFailure" },
    { 106 /*kStatus_FlashUnknownProperty*/, "kStatus_FlashUnknownProperty" },
    { 108 /*kStatus_FlashRegionExecuteOnly*/, "kStatus_FlashRegionExecuteOnly" },
    { 109 /*kStatus_FlashExecuteInRamFunctionNotReady*/, "kStatus_FlashExecuteInRamFunctionNotReady" },

    // I2C driver errors.
    { 200 /*kStatus_I2C_SlaveTxUnderrun*/, "I2C Slave TX Underrun error." },
    { 201 /*kStatus_I2C_SlaveRxOverrun*/, "I2C Slave RX Overrun error." },
    { 202 /*kStatus_I2C_AribtrationLost*/, "I2C Arbitration Lost error." },

    // SPI driver errors.
    { 300 /*kStatus_SPI_SlaveTxUnderrun*/, "SPI Slave TX Underrun error." },
    { 301 /*kStatus_SPI_SlaveRxOverrun*/, "SPI Slave RX Overrun error." },

    // QSPI driver errors.
    { 400 /*kStatus_QspiFlashSizeError*/, "QSPI Flash Size error." },
    { 401 /*kStatus_QspiFlashAlignmentError*/, "QSPI Flash Alignment error." },
    { 402 /*kStatus_QspiFlashAddressError*/, "QSPI Flash Address error." },
    { 403 /*kStatus_QspiFlashCommandFailure*/, "QSPI Flash Command Failure." },
    { 404 /*kStatus_QspiFlashUnknownProperty*/, "QSPI Flash Unknown Property." },
    { 405 /*kStatus_QspiNotConfigured*/, "QSPI Not Configured." },
    { 406 /*kStatus_QspiCommandNotSupported*/, "QSPI Command Not Supported." },
    { 407 /*kStatus_QspiCommandTimeout*/, "QSPI Command Timeout" },
    { 408 /*kStatus_QspiWriteFailure*/, "QSPI Write Failure." },

    // OTFAD driver errors.
    { 500 /*kStatus_OtfadSecurityViolation*/, "OTFAD Security Violation." },
    { 501 /*kStatus_OtfadLogicallyDisabled*/, "OTFAD Logically Disabled." },
    { 502 /*kStatus_OtfadInvalidKey*/, "OTFAD Invalid Key." },
    { 503 /*Kstatus_OtfadInvalidKeyBlob*/, "OTFAD Invalid KeyBlob." },

    // Bootloader errors.
    { kStatus_UnknownCommand, "kStatus_UnknownCommand" },
    { kStatus_SecurityViolation, "Command disallowed when security is enabled." },
    { kStatus_AbortDataPhase, "kStatus_AbortDataPhase" },
    { kStatus_Ping, "kStatus_Ping" },
    { kStatus_NoResponse, "No response packet from target device." },
    { kStatus_NoResponseExpected, "No response packet from target device was expected." },

    // SB loader errors.
    { kStatusRomLdrSectionOverrun, "kStatusRomLdrSectionOverrun" },
    { kStatusRomLdrSignature, "kStatusRomLdrSignature" },
    { kStatusRomLdrSectionLength, "kStatusRomLdrSectionLength" },
    { kStatusRomLdrUnencryptedOnly, "kStatusRomLdrUnencryptedOnly" },
    { kStatusRomLdrEOFReached, "kStatusRomLdrEOFReached" },
    { kStatusRomLdrChecksum, "kStatusRomLdrChecksum" },
    { kStatusRomLdrCrc32Error, "kStatusRomLdrCrc32Error" },
    { kStatusRomLdrUnknownCommand, "kStatusRomLdrUnknownCommand" },
    { kStatusRomLdrIdNotFound, "kStatusRomLdrIdNotFound" },
    { kStatusRomLdrDataUnderrun, "kStatusRomLdrDataUnderrun" },
    { kStatusRomLdrJumpReturned, "kStatusRomLdrJumpReturned" },
    { kStatusRomLdrCallFailed, "kStatusRomLdrCallFailed" },
    { kStatusRomLdrKeyNotFound, "kStatusRomLdrKeyNotFound" },
    { kStatusRomLdrSecureOnly, "kStatusRomLdrSecureOnly" },

    // Memory interface errors.
    { kStatusMemoryRangeInvalid, "kStatusMemoryRangeInvalid" },
    { kStatusMemoryReadFailed, "kStatusMemoryReadFailed" },
    { kStatusMemoryWriteFailed, "kStatusMemoryWriteFailed" },
    { kStatusMemoryCumulativeWrite, "kStatusMemoryCumulativeWrite" },

    // Property store errors.
    { kStatus_UnknownProperty, "Unknown property." },
    { kStatus_ReadOnlyProperty, "Property is read-only." },
    { kStatus_InvalidPropertyValue, "Invalid property value." },

    // Application crc check statuses.
    { 10400, "kStatus_AppCrcCheckPassed" },
    { 10401, "kStatus_AppCrcCheckFailed" },
    { 10402, "kStatus_AppCrcCheckInactive" },
    { 10403, "kStatus_AppCrcCheckInvalid" },
    { 10404, "kStatus_AppCrcCheckOutOfRange" },

    // Packetizer errors.
    { kStatus_NoPingResponse, "No response received for ping command." },
    { kStatus_InvalidPacketType, "Invalid packet type." },
    { kStatus_InvalidCRC, "Invalid CRC value." },
    { kStatus_NoCommandResponse, "No response received for command." },

    // Reliable Update statuses.
    { 10600, "kStatus_ReliableUpdateSuccess" },
    { 10601, "kStatus_ReliableUpdateFail" },
    { 10602, "kStatus_ReliableUpdateInacive" },
    { 10603, "kStatus_ReliableUpdateBackupApplicationInvalid" },
    { 10604, "kStatus_ReliableUpdateStillInMainApplication" },
    { 10605, "kStatus_ReliableUpdateSwapSystemNotReady" },
    { 10606, "kStatus_ReliableUpdateBackupBootloaderNotReady" },
    { 10607, "kStatus_ReliableUpdateSwapIndicatorAddressInvalid" },

    // Terminator
    { kStatusMessageTableTerminatorValue, "" }
};

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////

// See host_command.h for documentation of this method.
Command *Command::create(const string_vector_t *argv)
{
    Command *cmd;

    if (argv->at(0) == kCommand_Reset.name)
    {
        cmd = new Reset(argv);
    }
    else if (argv->at(0) == kCommand_GetProperty.name)
    {
        cmd = new GetProperty(argv);
    }
    else if (argv->at(0) == kCommand_SetProperty.name)
    {
        cmd = new SetProperty(argv);
    }
    else if (argv->at(0) == kCommand_FlashEraseRegion.name)
    {
        cmd = new FlashEraseRegion(argv);
    }
    else if (argv->at(0) == kCommand_FlashEraseAll.name)
    {
        cmd = new FlashEraseAll(argv);
    }
    else if (argv->at(0) == kCommand_FlashEraseAllUnsecure.name)
    {
        cmd = new FlashEraseAllUnsecure(argv);
    }
    else if (argv->at(0) == kCommand_ReadMemory.name)
    {
        cmd = new ReadMemory(argv);
    }
    else if (argv->at(0) == kCommand_WriteMemory.name)
    {
        cmd = new WriteMemory(argv);
    }
    else if (argv->at(0) == kCommand_FillMemory.name)
    {
        cmd = new FillMemory(argv);
    }
    else if (argv->at(0) == kCommand_ReceiveSbFile.name)
    {
        cmd = new ReceiveSbFile(argv);
    }
    else if (argv->at(0) == kCommand_Execute.name)
    {
        cmd = new Execute(argv);
    }
    else if (argv->at(0) == kCommand_Call.name)
    {
        cmd = new Call(argv);
    }
    else if (argv->at(0) == kCommand_FlashSecurityDisable.name)
    {
        cmd = new FlashSecurityDisable(argv);
    }
    else if (argv->at(0) == kCommand_FlashProgramOnce.name)
    {
        cmd = new FlashProgramOnce(argv);
    }
    else if (argv->at(0) == kCommand_FlashReadOnce.name)
    {
        cmd = new FlashReadOnce(argv);
    }
    else if (argv->at(0) == kCommand_FlashReadResource.name)
    {
        cmd = new FlashReadResource(argv);
    }
    else if (argv->at(0) == kCommand_ConfigureQuadSpi.name)
    {
        cmd = new ConfigureQuadSpi(argv);
    }
    else if (argv->at(0) == kCommand_ReliableUpdate.name)
    {
        cmd = new ReliableUpdate(argv);
    }
    else if (argv->at(0) == kCommand_FlashImage.name)
    {
        cmd = new FlashImage(argv);
    }
    else if (argv->at(0) == kCommand_ConfigureI2c.name)
    {
        cmd = new ConfigureI2c(argv);
    }
    else if (argv->at(0) == kCommand_ConfigureSpi.name)
    {
        cmd = new ConfigureSpi(argv);
    }
    else if (argv->at(0) == kCommand_ConfigureCan.name)
    {
        cmd = new ConfigureCan(argv);
    }
    else
    {
        return NULL;
    }

    // Validate arguments.
    if (!cmd->init())
    {
        delete cmd;
        return NULL;
    }

    return cmd;
}

// See host_command.h for documentation of this method.
std::string Command::getResponse() const
{
    Json::Value root;
    root["command"] = getName();
    root["status"] = Json::Value(Json::objectValue);
    root["status"]["value"] = static_cast<int32_t>(m_responseValues.at(0));
    root["status"]["description"] = format_string("%d (0x%X) %s", m_responseValues.at(0), m_responseValues.at(0),
                                                  getStatusMessage(m_responseValues.at(0)).c_str());
    root["response"] = Json::Value(Json::arrayValue);
    for (int i = 1; i < (int)m_responseValues.size(); ++i)
    {
        root["response"].append(Json::Value(m_responseValues.at(i)));
    }

    Json::StyledWriter writer;
    return writer.write(root);
}

std::string Command::getStatusMessage(status_t code)
{
    int i;
    for (i = 0; g_statusCodes[i].status != kStatusMessageTableTerminatorValue; ++i)
    {
        if (code == g_statusCodes[i].status)
        {
            return g_statusCodes[i].message;
        }
    }

    return format_string("Unknown error code (%d)", code);
}

// See host_command.h for documentation of this method.
void Command::logResponses() const
{
    const uint32_vector_t *respv = getResponseValues();
    size_t count = respv->size();

    Log::info("Response status = %d (0x%x) %s\n", respv->at(0), respv->at(0), getStatusMessage(respv->at(0)).c_str());

    for (int i = 1; i < (int)count; ++i)
    {
        Log::info("Response word %d = %ld (0x%lx)\n", i, respv->at(i), respv->at(i));
    }

    // Print the response details if there are any.
    if (!m_responseDetails.empty())
    {
        Log::info("%s\n", m_responseDetails.c_str());
    }

    Log::json(getResponse().c_str());
}

// See host_command.h for documentation of this method.
bool Command::processResponse(const generic_response_packet_t *packet, uint8_t commandTag)
{
    if (!packet)
    {
        Log::debug("processResponse: null packet\n");
        m_responseValues.push_back(kStatus_NoResponse);
        return false;
    }

    if (packet->commandPacket.commandTag != kCommandTag_GenericResponse)
    {
        Log::error("Error: expected kCommandTag_GenericResponse (0x%x), received 0x%x\n", kCommandTag_GenericResponse,
                   packet->commandPacket.commandTag);
        m_responseValues.push_back(kStatus_UnknownCommand);
        return false;
    }
    if (packet->commandTag != commandTag)
    {
        Log::error("Error: expected commandTag 0x%x, received 0x%x\n", commandTag, packet->commandTag);
        m_responseValues.push_back(kStatus_UnknownCommand);
        return false;
    }

    // Set the status in the response vector.
    m_responseValues.push_back(packet->status);

    if (packet->status != kStatus_Success)
    {
        return false;
    }

    Log::info("Successful generic response to command '%s'\n", getName().c_str());
    return true;
}

//! See host_command.h for documentation on this function.
bool blfwk::DataPacket::FileDataProducer::init(string filePath, uint32_t count)
{
    m_filePointer = fopen(filePath.c_str(), "rb");
    if (!m_filePointer)
    {
        Log::error("Error: cannot open input data file '%s'\n", filePath.c_str());
        return false;
    }

    // If the fileSize wasn't specified, get the file size.
    if (count)
    {
        m_fileSize = count;
    }
    else
    {
        ::fseek(m_filePointer, 0, SEEK_END);
        m_fileSize = ftell(m_filePointer);
        ::fseek(m_filePointer, 0, SEEK_SET);
    }

    Log::info("Preparing to send %d (0x%x) bytes to the target.\n", m_fileSize, m_fileSize);
    return true;
}

//! See host_command.h for documentation on this function.
uint32_t blfwk::DataPacket::FileDataProducer::getData(uint8_t *data, uint32_t size)
{
    assert(m_filePointer);
    assert(data);
    if ((size == 0) || !hasMoreData())
    {
        return 0;
    }

    return (uint32_t)fread(data, 1, size, m_filePointer);
}

//! See host_command.h for documentation on this function.
uint32_t blfwk::DataPacket::HexDataProducer::initFromString(const string hexData)
{
    // Remove everything from string except for hex digits.
    string hexString = string_hex(hexData);

    // Clear any existing data.
    m_data.clear();

    // Load data byte array from hex string.
    // Two hex characters equals one byte.
    // Any trailing character is ignored.
    for (uint32_t i = 0; i < hexString.size(); i += 2)
    {
        string hexByte = hexString.substr(i, 2);
        long int val = strtol(hexByte.c_str(), NULL, 16);
        m_data.push_back(static_cast<uint8_t>(val));
    }

    return m_data.size();
}

//! See host_command.h for documentation on this function.
uint32_t blfwk::DataPacket::HexDataProducer::getData(uint8_t *data, uint32_t size)
{
    assert(data);

    if (!hasMoreData())
    {
        return 0;
    }

    uint32_t remaining = m_data.size() - m_byteIndex;
    size = min(size, remaining);
    memcpy(data, &m_data[m_byteIndex], size);
    m_byteIndex += size;
    return size;
}

//! See host_command.h for documentation on this function.
uint32_t blfwk::DataPacket::SegmentDataProducer::getData(uint8_t *data, uint32_t size)
{
    assert(data);

    if (!hasMoreData())
    {
        return 0;
    }

    size = m_segment->getData(m_byteIndex, size, data);
    m_byteIndex += size;
    return size;
}

//! See host_command.h for documentation on this function.
bool blfwk::DataPacket::FileDataConsumer::init(string filePath)
{
    m_filePointer = fopen(filePath.c_str(), "wb");
    if (!m_filePointer)
    {
        Log::error("Error: cannot open output data file '%s'\n", filePath.c_str());
        return false;
    }
    return true;
}

//! See host_command.h for documentation on this function.
void blfwk::DataPacket::FileDataConsumer::processData(const uint8_t *data, uint32_t size)
{
    fwrite(data, 1, size, m_filePointer);
}

//! See host_command.h for documentation on this function.
void blfwk::DataPacket::StdOutDataConsumer::processData(const uint8_t *data, uint32_t size)
{
    // Only the size of the final packet can be smaller than 32 bytes.
    // So moving the cursor to the start will not over-write the data already displayed.
    printf("\r");

    for (int i = 0; i < (int)size; ++i)
    {
        printf("%02x", data[i]);
        if ((m_currentCount++ % kBytesPerLine) == 0)
        {
            printf("\n");
        }
        else
        {
            printf(" ");
        }
    }
}

//! See host_command.h for documentation on this function.
uint8_t *blfwk::DataPacket::sendTo(Packetizer &device, uint32_t *bytesWritten, Progress *progress)
{
    *bytesWritten = 0;

    if (!m_dataProducer->hasMoreData())
    {
        device.pumpSimulator();
    }

    while (m_dataProducer->hasMoreData() && *bytesWritten < m_dataProducer->getDataSize())
    {
        uint32_t count = m_dataProducer->getData(m_packet, sizeof(m_packet));
        if (count)
        {
            status_t status = device.writePacket((const uint8_t *)m_packet, count, kPacketType_Data);
            if (status != kStatus_Success)
            {
                Log::error("Data phase write aborted by status 0x%x %s\n", status,
                           Command::getStatusMessage(status).c_str());
                if ((status == kStatus_AbortDataPhase) && device.isAbortEnabled())
                {
                    Log::error("Possible JUMP or RESET command received.\n");
                }
                break;
            }

            *bytesWritten += count;

            if (progress != NULL)
            {
                // execute process callback function.
                progress->progressCallback(*bytesWritten * 100 / m_dataProducer->getDataSize());
                if (progress->abortPhase())
                {
                    device.writePacket((const uint8_t *)&m_packet, 0, kPacketType_Data);
                    break;
                }
            }
#ifdef TEST_SENDER_ABORT
            // Send zero length packet to abort data phase.
            Log::info("Testing data phase abort\n");
            device.writePacket((const uint8_t *)&m_packet, 0, kPacketType_Data);
            break;
#endif
        }
    }

    // Read final command status
    uint8_t *responsePacket;
    uint32_t responseLength;
    if (device.readPacket(&responsePacket, &responseLength, kPacketType_Command) != kStatus_Success)
    {
        return NULL;
    }
    return responsePacket;
}

//! See host_command.h for documentation on this function.
uint8_t *blfwk::DataPacket::receiveFrom(Packetizer &device, uint32_t *byteCount, Progress *progress)
{
    status_t status = kStatus_Success;
    uint32_t totalCount = *byteCount;
    // If byte count is zero, need to pump the simulator to get the final response
    if (*byteCount == 0)
    {
        device.pumpSimulator();
    }

    while (*byteCount > 0)
    {
        uint8_t *dataPacket;
        uint32_t length;

        // Pump the simulator command state machine, if it is enabled.
        device.pumpSimulator();

        status = device.readPacket(&dataPacket, &length, kPacketType_Data);

        // Bail if there was an error reading the packet.
        if (status != kStatus_Success)
        {
            Log::info("Read data packet error. Sending ACK.\n");
            m_dataConsumer->finalize();
            device.sync();
            return NULL;
        }

        // Check for sender abort of data phase.
        if (length == 0)
        {
            Log::info("Data phase aborted by sender\n");
            break;
        }

        m_dataConsumer->processData(dataPacket, length);
        *byteCount -= length;

        if (*byteCount <= 0)
        {
            m_dataConsumer->finalize();
        }

        if (progress != NULL)
        {
            progress->progressCallback((totalCount - *byteCount) * 100 / totalCount);
            if (progress->abortPhase())
            {
                device.abortPacket();
                break;
            }
        }
#ifdef TEST_RECEIVER_ABORT
        Log::info("Testing data phase abort\n");
        device.abortPacket();
        break;
#endif
    }

    // Read the final generic response packet.
    uint8_t *responsePacket;
    uint32_t responseLength;
    if (device.readPacket(&responsePacket, &responseLength, kPacketType_Command) != kStatus_Success)
    {
        return NULL;
    }
    return responsePacket;
}

//! See host_command.h for documentation on this function.
const uint8_t *blfwk::CommandPacket::sendCommandGetResponse(Packetizer &device)
{
    uint8_t *responsePacket = NULL;
    uint32_t responseLength = 0;

    status_t status = device.writePacket(getData(), getSize(), kPacketType_Command);
    if (status != kStatus_Success)
    {
        Log::error("sendCommandGetResponse.writePacket error %d.\n", status);
        return NULL;
    }
    status = device.readPacket(&responsePacket, &responseLength, kPacketType_Command);
    if (status == kStatus_Success)
    {
        return responsePacket;
    }
    else
    {
        Log::error("sendCommandGetResponse.readPacket error %d.\n", status);
        return NULL;
    }
}

////////////////////////////////////////////////////////////////////////////////
// Reset command
////////////////////////////////////////////////////////////////////////////////

// See host_command.h for documentation of this method.
bool Reset::init()
{
    if (getArgCount() != 1)
    {
        return false;
    }
    return true;
}

// See host_command.h for documentation of this method.
void Reset::sendTo(Packetizer &device)
{
    blfwk::CommandPacket cmdPacket(kCommandTag_Reset, kCommandFlag_None);
    const uint8_t *responsePacket = cmdPacket.sendCommandGetResponse(device);
    if (responsePacket)
    {
        processResponse(responsePacket);
    }
    else
    {
        Log::warning("Ignoring missing response from reset command.\n");
        this->m_responseValues.push_back(kStatus_Success);
    }
}

////////////////////////////////////////////////////////////////////////////////
// GetProperty command
////////////////////////////////////////////////////////////////////////////////

// See host_command.h for documentation of this method.
bool GetProperty::init()
{
    if (getArgCount() != 2 && getArgCount() != 3)
    {
        return false;
    }

    // Init property from tag or description.
    uint32_t tag = kPropertyTag_InvalidProperty;
    PropertyArray::const_iterator it;
    if (utils::stringtoui(getArg(1), tag))
    {
        for (it = kProperties.begin(); it != kProperties.end(); ++it)
        {
            if (it->value == tag)
                break;
        }
    }
    else
    {
        for (it = kProperties.begin(); it != kProperties.end(); ++it)
        {
            if (strcmp(it->description, getArg(1).c_str()) == 0)
                break;
        }
    }

    if (it == kProperties.end())
    {
        m_property = kProperty_Invalid;
    }
    else
    {
        m_property = *it;
    }

    if (getArgCount() == 3)
    {
        if (!utils::stringtoui(getArg(2), m_memoryId))
        {
            return false;
        }
    }
    else
    {
        m_memoryId = 0;
    }

    return true;
}

// See host_command.h for documentation of this method.
void GetProperty::sendTo(Packetizer &device)
{
    // See if the user just wants a list of the possible properites.
    if (m_property.value == kPropertyTag_ListProperties)
    {
        Log::info("The possible properties for the %s command are\n", getName().c_str());
        for (auto it = kProperties.begin(); it != kProperties.end(); ++it)
        {
            Log::info("    %d or '%s'\n", it->value, it->description);
        }

        m_responseValues.push_back(kStatus_NoResponseExpected);
    }
    else
    {
        // Command Phase
        blfwk::CommandPacket cmdPacket(kCommandTag_GetProperty, kCommandFlag_None, m_property.value, m_memoryId);
        const uint8_t *responsePacket = cmdPacket.sendCommandGetResponse(device);

        const get_property_response_packet_t *packet =
            reinterpret_cast<const get_property_response_packet_t *>(responsePacket);
        processResponse(packet);
    }
}

bool GetProperty::processResponse(const get_property_response_packet_t *packet)
{
    if (!packet)
    {
        Log::debug("processResponse: null packet\n");
        m_responseValues.push_back(kStatus_NoResponse);
        return false;
    }

    // Handle generic response, which would be returned if command is not supported.
    if (packet->commandPacket.commandTag == kCommandTag_GenericResponse)
    {
        return processResponse((const uint8_t *)packet);
    }

    if (packet->commandPacket.commandTag != kCommandTag_GetPropertyResponse)
    {
        Log::error("Error: expected kCommandTag_GetPropertyResponse (0x%x), received 0x%x\n",
                   kCommandTag_GetPropertyResponse, packet->commandPacket.commandTag);
        m_responseValues.push_back(kStatus_UnknownCommand);
        return false;
    }

    // Set the status in the response vector.
    m_responseValues.push_back(packet->status);

    if (packet->status != kStatus_Success)
    {
        return false;
    }

    Log::debug("Successful response to command '%s(%s)'\n", getName().c_str(), m_property.description);

    // Currently, no properties have a data phase.
    assert(!(packet->commandPacket.flags & kCommandFlag_HasDataPhase));

    // All properties have at least one response word.
    // Attention: parameterCount = 1(response status) + response words
    for (uint8_t i = 0; i < (packet->commandPacket.parameterCount - 1); ++i)
    {
        m_responseValues.push_back(packet->propertyValue[i]);
    }

    // Format the returned property details.
    switch (m_property.value)
    {
        case kPropertyTag_BootloaderVersion:
            m_responseDetails =
                format_string("Current Version = %c%d.%d.%d", (m_responseValues.at(1) & 0xff000000) >> 24,
                              (m_responseValues.at(1) & 0x00ff0000) >> 16, (m_responseValues.at(1) & 0x0000ff00) >> 8,
                              m_responseValues.at(1) & 0x000000ff);
            break;
        case kPropertyTag_TargetVersion:
            m_responseDetails =
                format_string("Target Version = %c%d.%d.%d", (m_responseValues.at(1) & 0xff000000) >> 24,
                              (m_responseValues.at(1) & 0x00ff0000) >> 16, (m_responseValues.at(1) & 0x0000ff00) >> 8,
                              m_responseValues.at(1) & 0x000000ff);
            break;
        case kPropertyTag_AvailablePeripherals:
        {
            m_responseDetails = "Available Peripherals = ";
            uint32_t peripherals = m_responseValues.at(1);
            uint32_t position = 0;
            while (peripherals)
            {
                if (peripherals & 0x00000001)
                {
                    m_responseDetails.append(kPeripherals.at(position).description);
                    if (peripherals >> 1)
                        m_responseDetails.append(", ");
                }
                peripherals >>= 1;
                ++position;
            }
            break;
        }
        case kPropertyTag_FlashStartAddress:
            m_responseDetails = format_string("Flash Start Address = 0x%08X", m_responseValues.at(1));
            break;
        case kPropertyTag_FlashSizeInBytes:
            m_responseDetails = format_string("Flash Size = %s", utils::scale_bytes(m_responseValues.at(1)).c_str());
            break;
        case kPropertyTag_FlashSectorSize:
            m_responseDetails =
                format_string("Flash Sector Size = %s", utils::scale_bytes(m_responseValues.at(1)).c_str());
            break;
        case kPropertyTag_FlashBlockCount:
            m_responseDetails = format_string("Flash Block Count = %d", m_responseValues.at(1));
            break;
        case kPropertyTag_AvailableCommands:
        {
            m_responseDetails = "Available Commands = ";
            uint32_t commands = m_responseValues.at(1);
            uint32_t position = 0;
            while (commands)
            {
                if (commands & 0x00000001)
                {
                    m_responseDetails.append(kCommands.at(position).name);
                    if (commands >> 1)
                        m_responseDetails.append(", ");
                }
                commands >>= 1;
                ++position;
            }
            break;
        }
        case kPropertyTag_CrcCheckStatus:
            m_responseDetails =
                format_string("CRC Check Status = %s", getStatusMessage(m_responseValues.at(1)).c_str());
            break;
        case kPropertyTag_VerifyWrites:
            m_responseDetails = format_string("Verify Writes Flag = %s", m_responseValues.at(1) ? "ON" : "OFF");
            break;
        case kPropertyTag_MaxPacketSize:
            m_responseDetails =
                format_string("Max Packet Size = %s", utils::scale_bytes(m_responseValues.at(1)).c_str());
            break;
        case kPropertyTag_ReservedRegions:
        {
            uint32_t flashLength = m_responseValues.at(2) - m_responseValues.at(1) + 1;
            if (flashLength == 1)
                flashLength = 0;
            uint32_t ramLength = m_responseValues.at(4) - m_responseValues.at(3) + 1;
            if (ramLength == 1)
                ramLength = 0;
            m_responseDetails = "Reserved Regions = ";
            m_responseDetails.append(format_string("Flash: 0x%X-0x%X (%s), ", m_responseValues.at(1),
                                                   m_responseValues.at(2), utils::scale_bytes(flashLength).c_str()));
            m_responseDetails.append(format_string("RAM: 0x%X-0x%X (%s)", m_responseValues.at(3),
                                                   m_responseValues.at(4), utils::scale_bytes(ramLength).c_str()));
            break;
        }
        case kPropertyTag_RAMStartAddress:
            m_responseDetails = format_string("RAM Start Address = 0x%08X", m_responseValues.at(1));
            break;
        case kPropertyTag_RAMSizeInBytes:
            m_responseDetails = format_string("RAM Size = %s", utils::scale_bytes(m_responseValues.at(1)).c_str());
            break;
        case kPropertyTag_SystemDeviceId:
            m_responseDetails = format_string("System Device ID = 0x%08X", m_responseValues.at(1));
            break;
        case kPropertyTag_FlashSecurityState:
            m_responseDetails =
                format_string("Flash Security State = %s", m_responseValues.at(1) ? "SECURE" : "UNSECURE");
            break;
        case kPropertyTag_UniqueDeviceId:
            m_responseDetails = "Unique Device ID =";
            for (uint32_t i = 1; i < m_responseValues.size(); ++i)
            {
                m_responseDetails.append(format_string(" %04X %04X", (m_responseValues.at(i) & 0xffff0000) >> 16,
                                                       m_responseValues.at(i) & 0x0000ffff));
            }
            break;
        case kPropertyTag_FacSupport:
            m_responseDetails = format_string("Flash Access Controller (FAC) Support Flag = %s",
                                              m_responseValues.at(1) ? "SUPPORTED" : "UNSUPPORTED");
            break;
        case kPropertyTag_FlashAccessSegmentSize:
            m_responseDetails =
                format_string("Flash Access Segment Size = %s", utils::scale_bytes(m_responseValues.at(1)).c_str());
            break;
        case kPropertyTag_FlashAccessSegmentCount:
            m_responseDetails = format_string("Flash Access Segment Count = %d", m_responseValues.at(1));
            break;
        case kPropertyTag_FlashReadMargin:
            m_responseDetails = "Flash read margin level = ";
            if (m_responseValues.at(1) == 0)
                m_responseDetails.append("NORMAL");
            else if (m_responseValues.at(1) == 1)
                m_responseDetails.append("USER");
            else if (m_responseValues.at(1) == 2)
                m_responseDetails.append("FACTORY");
            else
                m_responseDetails.append(format_string("UNKNOWN (%d)", m_responseValues.at(1)));
            break;
        case kPropertyTag_QspiInitStatus:
            m_responseDetails =
                format_string("QSPI Init Status = %s", getStatusMessage(m_responseValues.at(1)).c_str());
            break;
        case kPropertyTag_ExternalMemoryAttributes:
        {
            uint32_t m_propertyTags = m_responseValues.at(1);
            uint32_t m_memStartAddress = m_responseValues.at(2);
            uint32_t m_memSizeInKBytes = m_responseValues.at(3);
            uint32_t m_memPageSize = m_responseValues.at(4);
            uint32_t m_memSectorSize = m_responseValues.at(5);
            uint32_t m_memBlockSize = m_responseValues.at(6);

            if (m_propertyTags > 0)
            {
                string externMemoryDescriptor = "UNKNOWN";

                switch (m_memoryId)
                {
                    case 1:
                        externMemoryDescriptor = "QuadSPI";
                        break;
                    default:
                        break;
                }

                m_responseDetails = format_string("%s Attributes: ", externMemoryDescriptor.c_str());
            }

            if (m_propertyTags & (1 << (kExternalMemoryPropertyTag_StartAddress - 1)))
            {
                m_responseDetails.append(format_string("Start Address = 0x%08x  ", m_memStartAddress));
            }

            if (m_propertyTags & (1 << (kExternalMemoryPropertyTag_MemorySizeInKbytes - 1)))
            {
                uint64_t m_memorySizeInBytes = (uint64_t)m_memSizeInKBytes * 1024;
                m_responseDetails.append(
                    format_string("Total Size = %s  ", utils::scale_bytes(m_memorySizeInBytes).c_str()));
            }

            if (m_propertyTags & (1 << (kExternalMemoryPropertyTag_PageSize - 1)))
            {
                m_responseDetails.append(format_string("Page Size = %s  ", utils::scale_bytes(m_memPageSize).c_str()));
            }

            if (m_propertyTags & (1 << (kExternalMemoryPropertyTag_SectorSize - 1)))
            {
                m_responseDetails.append(
                    format_string("Sector Size = %s  ", utils::scale_bytes(m_memSectorSize).c_str()));
            }

            if (m_propertyTags & (1 << (kExternalMemoryPropertyTag_BlockSize - 1)))
            {
                m_responseDetails.append(format_string("Block Size = %s ", utils::scale_bytes(m_memBlockSize).c_str()));
            }
        }
        break;
        case kPropertyTag_ReliableUpdateStatus:
            m_responseDetails =
                format_string("Reliable Update Status = %s", getStatusMessage(m_responseValues.at(1)).c_str());
            break;
        case kPropertyTag_Reserved9:
        case kPropertyTag_InvalidProperty:
        default:
            break;
    }

    return true;
}

////////////////////////////////////////////////////////////////////////////////
// SetProperty command
////////////////////////////////////////////////////////////////////////////////

// See host_command.h for documentation of this method.
bool SetProperty::init()
{
    if (getArgCount() != 3)
    {
        return false;
    }
    // Save property tag number and value.
    if (!utils::stringtoui(getArg(1), m_propertyTag))
    {
        return false;
    }
    if (!utils::stringtoui(getArg(2), m_propertyValue))
    {
        return false;
    }
    return true;
}

// See host_command.h for documentation of this method.
void SetProperty::sendTo(Packetizer &device)
{
    blfwk::CommandPacket cmdPacket(kCommandTag_SetProperty, kCommandFlag_None, m_propertyTag, m_propertyValue);
    processResponse(cmdPacket.sendCommandGetResponse(device));
}

////////////////////////////////////////////////////////////////////////////////
// FlashEraseRegion command
////////////////////////////////////////////////////////////////////////////////

// See host_command.h for documentation of this method.
bool FlashEraseRegion::init()
{
    if (getArgCount() != 3)
    {
        return false;
    }

    if (!utils::stringtoui(getArg(1), m_startAddress))
    {
        return false;
    }
    if (!utils::stringtoui(getArg(2), m_byteCount))
    {
        return false;
    }

    return true;
}

// See host_command.h for documentation of this method.
void FlashEraseRegion::sendTo(Packetizer &device)
{
    blfwk::CommandPacket cmdPacket(kCommandTag_FlashEraseRegion, kCommandFlag_None, m_startAddress, m_byteCount);
    processResponse(cmdPacket.sendCommandGetResponse(device));
}

////////////////////////////////////////////////////////////////////////////////
// FlashEraseAll command
////////////////////////////////////////////////////////////////////////////////

// See host_command.h for documentation of this method.
bool FlashEraseAll::init()
{
    if (getArgCount() == 1)
    {
        m_memoryId = kFlashMemInternal;
        return true;
    }
    else if (getArgCount() == 2)
    {
        if (!utils::stringtoui(getArg(1), m_memoryId))
        {
            return false;
        }
        return true;
    }

    return false;
}

// See host_command.h for documentation of this method.
void FlashEraseAll::sendTo(Packetizer &device)
{
    blfwk::CommandPacket cmdPacket(kCommandTag_FlashEraseAll, kCommandFlag_None, m_memoryId);
    processResponse(cmdPacket.sendCommandGetResponse(device));
}

////////////////////////////////////////////////////////////////////////////////
// FlashEraseAllUnsecure command
////////////////////////////////////////////////////////////////////////////////

// See host_command.h for documentation of this method.
bool FlashEraseAllUnsecure::init()
{
    if (getArgCount() != 1)
    {
        return false;
    }
    return true;
}

// See host_command.h for documentation of this method.
void FlashEraseAllUnsecure::sendTo(Packetizer &device)
{
    blfwk::CommandPacket cmdPacket(kCommandTag_FlashEraseAllUnsecure, kCommandFlag_None);
    processResponse(cmdPacket.sendCommandGetResponse(device));
}

////////////////////////////////////////////////////////////////////////////////
// ReadMemory command
////////////////////////////////////////////////////////////////////////////////

// See host_command.h for documentation of this method.
bool ReadMemory::init()
{
    if ((getArgCount() < 3) || (getArgCount() > 4))
    {
        return false;
    }

    if (!utils::stringtoui(getArg(1), m_startAddress))
    {
        return false; // invalid 'addr' parameter
    }
    if (!utils::stringtoui(getArg(2), m_byteCount))
    {
        return false; // invalid 'count' parameter
    }

    // File name argument is optional - will use stdout if missing.
    if (getArgCount() == 4)
    {
        m_dataFile = getArg(3);
    }

    return true;
}

// See host_command.h for documentation of this method.
void ReadMemory::sendTo(Packetizer &device)
{
    DataPacket::DataConsumer *dataConsumer;
    DataPacket::FileDataConsumer fileDataConsumer;
    DataPacket::StdOutDataConsumer stdoutDataConsumer;

    // Setup to write to file or stdout
    if (m_dataFile.size() > 0)
    {
        if (!fileDataConsumer.init(m_dataFile))
        {
            return;
        }
        dataConsumer = &fileDataConsumer;
    }
    else
    {
        dataConsumer = &stdoutDataConsumer;
    }

    // Send command packet.
    blfwk::CommandPacket cmdPacket(kCommandTag_ReadMemory, kCommandFlag_None, m_startAddress, m_byteCount);
    const uint8_t *responsePacket = cmdPacket.sendCommandGetResponse(device);

    const read_memory_response_packet_t *packet =
        reinterpret_cast<const read_memory_response_packet_t *>(responsePacket);
    uint32_t byteCount = m_byteCount;
    if (processResponse(packet))
    {
        byteCount = packet->dataByteCount;

        // Receive data packets.
        blfwk::DataPacket dataPacket(dataConsumer);
        uint8_t *finalResponsePacket = dataPacket.receiveFrom(device, &byteCount, m_progress);
        processResponse(finalResponsePacket);
    }

    // Push the number of bytes transferred response value.
    m_responseValues.push_back(m_byteCount - byteCount);

    // Format the command transfer details.
    m_responseDetails = format_string("Read %d of %d bytes.", m_byteCount - byteCount, m_byteCount);
}

bool ReadMemory::processResponse(const read_memory_response_packet_t *packet)
{
    if (!packet)
    {
        Log::debug("processResponse: null packet\n");
        m_responseValues.push_back(kStatus_NoResponse);
        return false;
    }

    // Handle generic response, which would be returned if command is not supported.
    if (packet->commandPacket.commandTag == kCommandTag_GenericResponse)
    {
        return processResponse((const uint8_t *)packet);
    }

    if (packet->commandPacket.commandTag != kCommandTag_ReadMemoryResponse)
    {
        Log::error("Error: expected kCommandTag_ReadMemoryResponse (0x%x), received 0x%x\n",
                   kCommandTag_ReadMemoryResponse, packet->commandPacket.commandTag);
        return false;
    }
    if (packet->status != kStatus_Success)
    {
        // Set the status in the response vector.
        // If status is OK, this push will be done by final response processing
        m_responseValues.push_back(packet->status);
        return false;
    }

    Log::info("Successful response to command '%s'\n", getName().c_str());

    return true;
}

////////////////////////////////////////////////////////////////////////////////
// WriteMemory command
////////////////////////////////////////////////////////////////////////////////

// See host_command.h for documentation of this method.
bool WriteMemory::init()
{
    if (getArgCount() != 3 && getArgCount() != 4)
    {
        return false;
    }

    if (!utils::stringtoui(getArg(1), m_startAddress))
    {
        return false;
    }
    m_fileOrData = getArg(2);

    if ((m_fileOrData[0] == '{') && (m_fileOrData[1] == '{'))
    {
        DataPacket::HexDataProducer hexProducer;
        // Argument string is hex data, so use hex data producer.
        if (hexProducer.initFromString(m_fileOrData) == 0)
        {
            return false;
        }
    }

    if (getArgCount() == 4)
    {
        if (!utils::stringtoui(getArg(3), m_count))
        {
            return false;
        }
    }

    return true;
}

// See host_command.h for documentation of this method.
void WriteMemory::sendTo(Packetizer &device)
{
    DataPacket::HexDataProducer hexProducer(m_data);
    DataPacket::FileDataProducer fileProducer;
    DataPacket::SegmentDataProducer segmentProducer(m_segment);
    DataPacket::DataProducer *dataProducer;

    if (m_segment)
    {
        dataProducer = &segmentProducer;
    }
    else if ((m_fileOrData[0] == '{') && (m_fileOrData[1] == '{'))
    {
        // Argument string is hex data, so use hex data producer.
        if (hexProducer.initFromString(m_fileOrData) == 0)
        {
            return;
        }
        dataProducer = &hexProducer;
    }
    else if (m_data.size() > 0)
    {
        dataProducer = &hexProducer;
    }
    else
    {
        // Argument string is file name, so use file data producer.
        if (!fileProducer.init(m_fileOrData, m_count))
        {
            return;
        }
        dataProducer = &fileProducer;
    }

    // Send command packet.
    uint32_t bytesToWrite = dataProducer->getDataSize();
    uint32_t bytesWritten;
    blfwk::CommandPacket cmdPacket(kCommandTag_WriteMemory, kCommandFlag_HasDataPhase, m_startAddress, bytesToWrite);
    if (!processResponse(cmdPacket.sendCommandGetResponse(device)))
    {
        m_responseDetails = format_string("Wrote 0 of %d bytes.", bytesToWrite);
        return;
    }

    // Pop the initial (successful) generic response value.
    if (m_responseValues.size())
    {
        m_responseValues.pop_back();
    }

    // Send data packets.
    blfwk::DataPacket dataPacket(dataProducer);
    processResponse(dataPacket.sendTo(device, &bytesWritten, m_progress));

    // Format the command transfer details.
    m_responseDetails = format_string("Wrote %d of %d bytes.", bytesWritten, bytesToWrite);
}

////////////////////////////////////////////////////////////////////////////////
// FillMemory command
////////////////////////////////////////////////////////////////////////////////

// See host_command.h for documentation of this method.
bool FillMemory::init()
{
    if ((getArgCount() < 4) || (getArgCount() > 5))
    {
        return false;
    }

    if (!utils::stringtoui(getArg(1), m_startAddress))
    {
        return false; // invalid 'addr' parameter
    }
    if (!utils::stringtoui(getArg(2), m_byteCount))
    {
        return false; // invalid 'byte_count' parameter
    }
    if (!utils::stringtoui(getArg(3), m_patternWord))
    {
        return false; // invalid 'pattern' parameter
    }

    if ((getArgCount() == 5) && (getArg(4) != "word"))
    {
        unsigned char b1 = (unsigned char)((m_patternWord >> 8) & 0xff);
        unsigned char b0 = (unsigned char)(m_patternWord & 0xff);

        if (getArg(4) == "byte")
        {
            // Replicate byte pattern in word.
            m_patternWord = b0 + (b0 << 8) + (b0 << 16) + (b0 << 24);
        }
        else if (getArg(4) == "short")
        {
            // Replicate short pattern in word.
            m_patternWord = b0 + (b1 << 8) + (b0 << 16) + (b1 << 24);
        }
        else
        {
            return false; // unknown pattern size argument
        }
    }

    return true;
}

// See host_command.h for documentation of this method.
void FillMemory::sendTo(Packetizer &device)
{
    blfwk::CommandPacket cmdPacket(kCommandTag_FillMemory, kCommandFlag_None, m_startAddress, m_byteCount,
                                   m_patternWord);
    processResponse(cmdPacket.sendCommandGetResponse(device));
}

////////////////////////////////////////////////////////////////////////////////
// ReceiveSbFile command
////////////////////////////////////////////////////////////////////////////////

// See host_command.h for documentation of this method.
bool ReceiveSbFile::init()
{
    if (getArgCount() != 2)
    {
        return false;
    }
    m_dataFile = getArg(1);
    return true;
}

// See host_command.h for documentation of this method.
void ReceiveSbFile::sendTo(Packetizer &device)
{
    DataPacket::FileDataProducer dataProducer;
    if (!dataProducer.init(m_dataFile, 0))
    {
        return;
    }

    // Send command packet.
    uint32_t bytesToWrite = dataProducer.getDataSize();
    uint32_t bytesWritten;
    blfwk::CommandPacket cmdPacket(kCommandTag_ReceiveSbFile, kCommandFlag_HasDataPhase, bytesToWrite);
    if (!processResponse(cmdPacket.sendCommandGetResponse(device)))
    {
        m_responseDetails = format_string("Wrote 0 of %d bytes.", bytesToWrite);
        return;
    }

    // Pop the initial (successful) generic response value.
    if (m_responseValues.size())
    {
        m_responseValues.pop_back();
    }

    // Send data packets.
    device.setAbortEnabled(true);
    blfwk::DataPacket dataPacket(&dataProducer);
    processResponse(dataPacket.sendTo(device, &bytesWritten, m_progress));
    device.setAbortEnabled(false);

    // Format the command transfer details.
    m_responseDetails = format_string("Wrote %d of %d bytes.", bytesWritten, bytesToWrite);
}

////////////////////////////////////////////////////////////////////////////////
// Execute command
////////////////////////////////////////////////////////////////////////////////

// See host_command.h for documentation of this method.
bool Execute::init()
{
    if (getArgCount() != 4)
    {
        return false;
    }

    if (!utils::stringtoui(getArg(1), m_jumpAddress))
    {
        return false;
    }

    if (!utils::stringtoui(getArg(2), m_wordArgument))
    {
        return false;
    }

    if (!utils::stringtoui(getArg(3), m_stackpointer))
    {
        return false;
    }
    return true;
}

// See host_command.h for documentation of this method.
void Execute::sendTo(Packetizer &device)
{
    blfwk::CommandPacket cmdPacket(kCommandTag_Execute, kCommandFlag_None, m_jumpAddress, m_wordArgument,
                                   m_stackpointer);
    const uint8_t *responsePacket = cmdPacket.sendCommandGetResponse(device);
    if (responsePacket)
    {
        processResponse(responsePacket);
    }
    else
    {
        Log::warning("Ignoring missing response from execute command.\n");
        this->m_responseValues.push_back(kStatus_Success);
    }
}

////////////////////////////////////////////////////////////////////////////////
// Call command
////////////////////////////////////////////////////////////////////////////////

// See host_command.h for documentation of this method.
bool Call::init()
{
    if (getArgCount() != 3)
    {
        return false;
    }

    if (!utils::stringtoui(getArg(1), m_callAddress))
    {
        return false;
    }
    if (!utils::stringtoui(getArg(2), m_wordArgument))
    {
        return false;
    }

    return true;
}

// See host_command.h for documentation of this method.
void Call::sendTo(Packetizer &device)
{
    blfwk::CommandPacket cmdPacket(kCommandTag_Call, kCommandFlag_None, m_callAddress, m_wordArgument);
    processResponse(cmdPacket.sendCommandGetResponse(device));
}

////////////////////////////////////////////////////////////////////////////////
// FlashSecurityDisable command
////////////////////////////////////////////////////////////////////////////////

// See host_command.h for documentation of this method.
bool FlashSecurityDisable::init()
{
    if (getArgCount() != 2)
    {
        return false;
    }
    if (getArg(1).length() != 16)
    {
        return false;
    }

    // String must be hex digits with no leading 0x.
    char *endPtr;
    m_keyLow = strtoul(getArg(1).substr(0, 8).c_str(), &endPtr, 16);
    if ((endPtr == NULL) || (*endPtr != 0))
    {
        return false;
    }
    m_keyHigh = strtoul(getArg(1).substr(8, 8).c_str(), &endPtr, 16);
    if ((endPtr == NULL) || (*endPtr != 0))
    {
        return false;
    }

    return true;
}

// See host_command.h for documentation of this method.
void FlashSecurityDisable::sendTo(Packetizer &device)
{
    blfwk::CommandPacket cmdPacket(kCommandTag_FlashSecurityDisable, kCommandFlag_None, m_keyLow, m_keyHigh);
    processResponse(cmdPacket.sendCommandGetResponse(device));
}

////////////////////////////////////////////////////////////////////////////////
// FlashProgramOnce command
////////////////////////////////////////////////////////////////////////////////

// See host_command.h for documentation of this method.
bool FlashProgramOnce::init()
{
    if (getArgCount() != 4)
    {
        return false;
    }

    if (getArg(3).length() != 8 && getArg(3).length() != 16)
    {
        return false;
    }

    if (!utils::stringtoui(getArg(1), m_index))
    {
        return false;
    }
    if (!utils::stringtoui(getArg(2), m_byteCount))
    {
        return false;
    }

    if (m_byteCount != 4 && m_byteCount != 8)
    {
        return false;
    }

    char *endPtr;
    m_dataLow = strtoul(getArg(3).substr(0, 8).c_str(), &endPtr, 16);
    if ((endPtr == NULL) || (*endPtr != 0))
    {
        return false;
    }

    if (m_byteCount == 8)
    {
        m_dataHigh = strtoul(getArg(3).substr(8, 8).c_str(), &endPtr, 16);
        if ((endPtr == NULL) || (*endPtr != 0))
        {
            return false;
        }
    }

    return true;
}

// See host_command.h for documentation of this method.
void FlashProgramOnce::sendTo(Packetizer &device)
{
    if (m_byteCount == 4)
    {
        blfwk::CommandPacket cmdPacket(kCommandTag_FlashProgramOnce, kCommandFlag_None, m_index, m_byteCount,
                                       m_dataLow);
        processResponse(cmdPacket.sendCommandGetResponse(device));
    }
    else
    {
        blfwk::CommandPacket cmdPacket(kCommandTag_FlashProgramOnce, kCommandFlag_None, m_index, m_byteCount, m_dataLow,
                                       m_dataHigh);
        processResponse(cmdPacket.sendCommandGetResponse(device));
    }
}

////////////////////////////////////////////////////////////////////////////////
// FlashReadOnce command
////////////////////////////////////////////////////////////////////////////////

// See host_command.h for documentation of this method.
bool FlashReadOnce::init(void)
{
    if (getArgCount() != 3)
    {
        return false;
    }

    if (!utils::stringtoui(getArg(1), m_index))
    {
        return false;
    }
    if (!utils::stringtoui(getArg(2), m_byteCount))
    {
        return false;
    }

    if (m_byteCount != 4 && m_byteCount != 8)
    {
        return false;
    }

    return true;
}

// See host_command.h for documentation of this method.
void FlashReadOnce::sendTo(Packetizer &device)
{
    // Command Phase
    blfwk::CommandPacket cmdPacket(kCommandTag_FlashReadOnce, kCommandFlag_None, m_index, m_byteCount);
    const uint8_t *responsePacket = cmdPacket.sendCommandGetResponse(device);

    const flash_read_once_response_packet_t *packet =
        reinterpret_cast<const flash_read_once_response_packet_t *>(responsePacket);
    processResponse(packet);
}

// See host_command.h for documentation of this method.
bool FlashReadOnce::processResponse(const flash_read_once_response_packet_t *packet)
{
    if (!packet)
    {
        Log::debug("processResponse: null packet\n");
        m_responseValues.push_back(kStatus_NoResponse);
        return false;
    }

    // Handle generic response, which would be returned if command is not supported.
    if (packet->commandPacket.commandTag == kCommandTag_GenericResponse)
    {
        return processResponse((const uint8_t *)packet);
    }

    if (packet->commandPacket.commandTag != kCommandTag_FlashReadOnceResponse)
    {
        Log::error("Error: expected kCommandTag_FlashReadOnceResponse (0x%x), received 0x%x\n",
                   kCommandTag_FlashReadOnceResponse, packet->commandPacket.commandTag);
        m_responseValues.push_back(kStatus_UnknownCommand);
        return false;
    }

    // Set the status in the response vector.
    m_responseValues.push_back(packet->status);

    if (packet->status != kStatus_Success)
    {
        return false;
    }

    Log::debug("Successful response to command '%s'\n", getName().c_str());

    // Currently, no properties have a data phase.
    assert(!(packet->commandPacket.flags & kCommandFlag_HasDataPhase));

    // All properties have at least one response word.
    // Attention: parameterCount = 1(response status) + response words
    m_responseValues.push_back(packet->byteCount);

    // two parameters(status and byte count) should be excluded from the parameterCount
    for (uint8_t i = 0; i < (packet->commandPacket.parameterCount - 2); ++i)
    {
        m_responseValues.push_back(packet->data[i]);
    }

    return true;
}

////////////////////////////////////////////////////////////////////////////////
// FlashReadResource command
////////////////////////////////////////////////////////////////////////////////

// See host_command.h for documentation of this method.
bool FlashReadResource::init()
{
    if ((getArgCount() < 4) || (getArgCount() > 5))
    {
        return false;
    }

    if (!utils::stringtoui(getArg(1), m_startAddress))
    {
        return false;
    }
    if (!utils::stringtoui(getArg(2), m_byteCount))
    {
        return false;
    }
    if (!utils::stringtoui(getArg(3), m_option))
    {
        return false;
    }

    // File name argument is optional - will use stdout if missing.
    if (getArgCount() == 5)
    {
        m_dataFile = getArg(4);
    }

    return true;
}

// See host_command.h for documentation of this method.
void FlashReadResource::sendTo(Packetizer &device)
{
    DataPacket::DataConsumer *dataConsumer;
    DataPacket::FileDataConsumer fileDataConsumer;
    DataPacket::StdOutDataConsumer stdoutDataConsumer;

    // Setup to write to file or stdout
    if (m_dataFile.size() > 0)
    {
        if (!fileDataConsumer.init(m_dataFile))
        {
            return;
        }
        dataConsumer = &fileDataConsumer;
    }
    else
    {
        dataConsumer = &stdoutDataConsumer;
    }

    // Send command packet.
    blfwk::CommandPacket cmdPacket(kCommandTag_FlashReadResource, kCommandFlag_None, m_startAddress, m_byteCount,
                                   m_option);
    const uint8_t *responsePacket = cmdPacket.sendCommandGetResponse(device);

    const flash_read_resource_response_packet_t *packet =
        reinterpret_cast<const flash_read_resource_response_packet_t *>(responsePacket);
    uint32_t byteCount = packet->dataByteCount;
    if (processResponse(packet))
    {
        // Receive data packets.
        blfwk::DataPacket dataPacket(dataConsumer);
        uint8_t *finalResponsePacket = dataPacket.receiveFrom(device, &byteCount, m_progress);
        processResponse(finalResponsePacket);
    }

    // Push the number of bytes transferred response value.
    m_responseValues.push_back(m_byteCount - byteCount);

    // Format the command transfer details.
    m_responseDetails = format_string("Read %d of %d bytes.", m_byteCount - byteCount, m_byteCount);
}

bool FlashReadResource::processResponse(const flash_read_resource_response_packet_t *packet)
{
    if (!packet)
    {
        Log::debug("processResponse: null packet\n");
        m_responseValues.push_back(kStatus_NoResponse);
        return false;
    }

    // Handle generic response, which would be returned if command is not supported.
    if (packet->commandPacket.commandTag == kCommandTag_GenericResponse)
    {
        return processResponse((const uint8_t *)packet);
    }

    if (packet->commandPacket.commandTag != kCommandTag_FlashReadResourceResponse)
    {
        Log::error("Error: expected kCommandTag_FlashReadResourceResponse (0x%x), received 0x%x\n",
                   kCommandTag_FlashReadResourceResponse, packet->commandPacket.commandTag);
        return false;
    }
    if (packet->status != kStatus_Success)
    {
        // Set the status in the response vector.
        // If status is OK, this push will be done by final response processing
        m_responseValues.push_back(packet->status);
        return false;
    }

    Log::info("Successful response to command '%s'\n", getName().c_str());

    return true;
}

////////////////////////////////////////////////////////////////////////////////
// Configure QuadSpi command
////////////////////////////////////////////////////////////////////////////////

// See host_command.h for documentation of this method.
bool ConfigureQuadSpi::init()
{
    if (getArgCount() != 3)
    {
        return false;
    }
    if (!utils::stringtoui(getArg(1), m_flashMemId))
    {
        return false;
    }
    if (!utils::stringtoui(getArg(2), m_configBlockAddress))
    {
        return false;
    }

    return true;
}

////////////////////////////////////////////////////////////////////////////////
// Configure Peripheral command
////////////////////////////////////////////////////////////////////////////////

// See host_command.h for documentation of this method.
void ConfigureQuadSpi::sendTo(Packetizer &device)
{
    blfwk::CommandPacket cmdPacket(kCommandTag_ConfigureQuadSpi, kCommandFlag_None, m_flashMemId, m_configBlockAddress);
    processResponse(cmdPacket.sendCommandGetResponse(device));
}

////////////////////////////////////////////////////////////////////////////////
// ReliableUpdate command
////////////////////////////////////////////////////////////////////////////////

// See host_command.h for documentation of this method.
bool ReliableUpdate::init()
{
    if (getArgCount() != 2)
    {
        return false;
    }
    if (!utils::stringtoui(getArg(1), m_address))
    {
        return false;
    }

    return true;
}

// See host_command.h for documentation of this method.
void ReliableUpdate::sendTo(Packetizer &device)
{
    blfwk::CommandPacket cmdPacket(kCommandTag_ReliableUpdate, kCommandFlag_None, m_address);
    processResponse(cmdPacket.sendCommandGetResponse(device));
}

////////////////////////////////////////////////////////////////////////////////
// FlashImage command
////////////////////////////////////////////////////////////////////////////////

// See host_command.h for documentation of this method.
bool FlashImage::init()
{
    if (getArgCount() != 2 && getArgCount() != 3)
    {
        return false;
    }

    m_fileName = getArg(1);

    if (getArgCount() == 3)
    {
        string strDoEraseOpt = getArg(2);
        if (strDoEraseOpt == "erase" || strDoEraseOpt == "1")
        {
            m_doEraseOpt = true;
        }
        else if (strDoEraseOpt == "none" || strDoEraseOpt == "0")
        {
            m_doEraseOpt = false;
        }
        else
        {
            return false;
        }
    }

    return true;
}

// See host_command.h for documentation of this method.
void FlashImage::sendTo(Packetizer &device)
{
    uint32_t fw_status;
    DataSource *dataSource;

    try
    {
        m_sourceFile = SourceFile::openFile(m_fileName);
    }
    catch (exception &e)
    {
        Log::error("Error: %s", e.what());
        return;
    }
    if (m_sourceFile->getFileType() == SourceFile::source_file_t::kBinarySourceFile)
    {
        Log::error("Error: please use write-memory command for binary file downloading.\n");
        return;
    }

    m_sourceFile->open();
    dataSource = m_sourceFile->createDataSource();

    m_progress->m_segmentCount = dataSource->getSegmentCount();

    if (m_doEraseOpt)
    {
        GetProperty cmdGetSectorSize(kProperty_FlashSectorSize);
        cmdGetSectorSize.sendTo(device);
        // Print and check the command response values.
        fw_status = cmdGetSectorSize.getResponseValues()->at(0);
        if (fw_status != kStatus_Success)
        {
            m_responseValues.push_back(fw_status);
            delete dataSource;
            return;
        }
        m_sectorSize = cmdGetSectorSize.getResponseValues()->at(1);

        for (uint32_t index = 0; index < dataSource->getSegmentCount(); ++index)
        {
            DataSource::Segment *segment = dataSource->getSegmentAt(index);

            // Align the start address and length to a sector boundary
            uint32_t alignedStart = segment->getBaseAddress() & (~(m_sectorSize - 1));
            uint32_t alignedLength = (segment->getLength() + m_sectorSize) & (~(m_sectorSize - 1));
            // Do erase operation to erase the necessary flash.
            FlashEraseRegion cmd(alignedStart, alignedLength);
            cmd.sendTo(device);

            // Print and check the command response values.
            fw_status = cmd.getResponseValues()->at(0);
            if (fw_status != kStatus_Success)
            {
                m_responseValues.push_back(fw_status);
                delete dataSource;
                return;
            }
        }
    }

    for (uint32_t index = 0; index < dataSource->getSegmentCount(); ++index)
    {
        DataSource::Segment *segment = dataSource->getSegmentAt(index);

        // Write the file to the base address.
        Log::info("Wrote %d bytes to address %#x\n", segment->getLength(), segment->getBaseAddress());
        WriteMemory cmd(segment);

        m_progress->m_segmentIndex = index + 1;
        cmd.registerProgress(m_progress);

        cmd.sendTo(device);

        // Print and check the command response values.
        fw_status = cmd.getResponseValues()->at(0);
        if (fw_status != kStatus_Success)
        {
            m_responseValues.push_back(fw_status);
            delete dataSource;
            return;
        }
    }

    m_responseValues.push_back(fw_status);
    delete dataSource;
    m_sourceFile->close();
}

////////////////////////////////////////////////////////////////////////////////
// Configure I2C command
////////////////////////////////////////////////////////////////////////////////

// See host_command.h for documentation of this method.
bool ConfigureI2c::init()
{
    if (getArgCount() > 1)
    {
        i2cAddress = (uint8_t)strtoul(getArg(1).c_str(), NULL, 16);

        if (i2cAddress > 0x7F)
        {
            i2cAddress &= 0x7F;
            Log::info("Only 7-bit i2c address is supported, so the effective value is 0x%x\n", i2cAddress);
        }

        if (getArgCount() > 2)
        {
            int32_t i2cSpeed = atoi(getArg(2).c_str());
            if (i2cSpeed <= 0)
                return false;

            i2cSpeedKHz = i2cSpeed;
        }
    }

    return true;
}

// See host_command.h for documentation of this method.
void ConfigureI2c::sendTo(Packetizer &device)
{
    blfwk::CommandPacket cmdPacket(kCommandTag_ConfigureI2c, kCommandFlag_None, i2cAddress, i2cSpeedKHz);
    processResponse(cmdPacket.sendCommandGetResponse(device));
}

////////////////////////////////////////////////////////////////////////////////
// Configure SPI command
////////////////////////////////////////////////////////////////////////////////

// See host_command.h for documentation of this method.
bool ConfigureSpi::init()
{
    if ((getArgCount() > 1))
    {
        int32_t spiSpeed = atoi(getArg(1).c_str());
        if (spiSpeed <= 0)
            return false;

        spiSpeedKHz = spiSpeed;

        if (getArgCount() > 2)
        {
            spiPolarity = (BusPal::spi_clock_polarity_t)atoi(getArg(2).c_str());

            if (getArgCount() > 3)
            {
                spiPhase = (BusPal::spi_clock_phase_t)atoi(getArg(3).c_str());

                if (getArgCount() > 4)
                {
                    if (!strcmp(getArg(4).c_str(), "lsb"))
                    {
                        spiDirection = BusPal::kSpiLsbFirst;
                    }
                    else if (!strcmp(getArg(4).c_str(), "msb"))
                    {
                        spiDirection = BusPal::kSpiMsbFirst;
                    }
                }
            }
        }
    }

    return true;
}

// See host_command.h for documentation of this method.
void ConfigureSpi::sendTo(Packetizer &device)
{
    blfwk::CommandPacket cmdPacket(kCommandTag_ConfigureSpi, kCommandFlag_None, spiSpeedKHz, spiPolarity, spiPhase,
                                   spiDirection);
    processResponse(cmdPacket.sendCommandGetResponse(device));
}

////////////////////////////////////////////////////////////////////////////////
// Configure CAN command
////////////////////////////////////////////////////////////////////////////////

// See host_command.h for documentation of this method.
bool ConfigureCan::init()
{
    if ((getArgCount() > 1))
    {
        canSpeed = atoi(getArg(1).c_str());
        if (canSpeed > 4)
            return false;

        if (getArgCount() > 2)
        {
            canTxid = strtoul(getArg(2).c_str(), NULL, 16) & 0x7ff;
        }

        if (getArgCount() > 3)
        {
            canRxid = strtoul(getArg(3).c_str(), NULL, 16) & 0x7ff;
        }
    }

    return true;
}

// See host_command.h for documentation of this method.
void ConfigureCan::sendTo(Packetizer &device)
{
    blfwk::CommandPacket cmdPacket(kCommandTag_ConfigureCan, kCommandFlag_None, canSpeed, canTxid, canRxid);
    processResponse(cmdPacket.sendCommandGetResponse(device));
}

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
