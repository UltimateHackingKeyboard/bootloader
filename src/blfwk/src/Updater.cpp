/*
 * Copyright (c) 2013-14, Freescale Semiconductor, Inc.
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

#include "blfwk/Updater.h"
#include "bootloader/bootloader.h"

using namespace blfwk;

Updater::Updater(const Peripheral::PeripheralConfigData &config)
    : Bootloader(config)
    , m_sector_size(0)
    , m_sourceFile(NULL)
    , m_operation(kUpdaterOperation_Update)
    , m_progressCallback(NULL)
{
    //
    // Get the sector size of the device so we can compute the
    // address of the Bootloader COnfiguration Block and align
    // erase regions.
    //
    // Inject the get-property(flash-sector-size) command.
    GetProperty cmdGetSectorSize(kProperty_FlashSectorSize);
    Log::info("inject command '%s'\n", cmdGetSectorSize.getName().c_str());
    inject(cmdGetSectorSize);

    uint32_t fw_status = cmdGetSectorSize.getResponseValues()->at(0);
    if (fw_status != kStatus_Success)
    {
        throw std::runtime_error(cmdGetSectorSize.getStatusMessage(fw_status));
    }

    m_sector_size = cmdGetSectorSize.getResponseValues()->at(1);

    //
    // Get the flash start address of the device
    //
    // Inject the get-property(flash-start-address) command.
    GetProperty cmdGetFlashStartAddress(kProperty_FlashStartAddress);
    Log::info("inject command '%s'\n", cmdGetFlashStartAddress.getName().c_str());
    inject(cmdGetFlashStartAddress);

    fw_status = cmdGetFlashStartAddress.getResponseValues()->at(0);
    if (fw_status != kStatus_Success)
    {
        throw std::runtime_error(cmdGetFlashStartAddress.getStatusMessage(fw_status));
    }

    m_flashStart = cmdGetFlashStartAddress.getResponseValues()->at(1);

    //
    // Get the flash size of the device
    //
    // Inject the get-property(flash-size-in-bytes) command.
    GetProperty cmdGetFlashSize(kProperty_FlashSizeInBytes);
    Log::info("inject command '%s'\n", cmdGetFlashSize.getName().c_str());
    inject(cmdGetFlashSize);

    fw_status = cmdGetFlashSize.getResponseValues()->at(0);
    if (fw_status != kStatus_Success)
    {
        throw std::runtime_error(cmdGetFlashSize.getStatusMessage(fw_status));
    }

    m_flashSize = cmdGetFlashSize.getResponseValues()->at(1);
}

Updater::~Updater()
{
}

// See Updater.h for documentation of this method.
status_t Updater::flashFirmware(const char *filename, uint32_t base_address)
{
    m_base_address = base_address;
    // Create the SourceFile
    m_sourceFile = SourceFile::openFile(filename);

    // Initialize the Operation structure.
    m_operation.tasks.push_back(updater_task_t(kUpdaterTask_Erasing, m_sourceFile->getSize()));
    m_operation.tasks.push_back(updater_task_t(kUpdaterTask_Flashing, m_sourceFile->getSize()));
    m_operation.current_task = 0;

    if (m_sourceFile->getFileType() == SourceFile::source_file_t::kSBSourceFile &&
        isCommandSupported(kCommand_ReceiveSbFile))
    {
        return flashFromSBFile(filename);
    }
    else if (m_sourceFile->getFileType() == SourceFile::source_file_t::kELFSourceFile)
    {
        throw std::runtime_error("ELF files are not yet supported.");
    }
    else
    {
        return flashFromSourceFile();
    }
}

// See Updater.h for documentation of this method.
void Updater::eraseAllUnsecure()
{
    if (!isCommandSupported(kCommand_FlashEraseAllUnsecure))
    {
        throw std::runtime_error("FlashEraseAllUnsecure isn't supported!");
    }

    FlashEraseAllUnsecure cmd;
    Log::info("inject command '%s'\n", cmd.getName().c_str());
    inject(cmd);

    uint32_t fw_status = cmd.getResponseValues()->at(0);
    std::string fw_msg = cmd.getStatusMessage(fw_status);

    // Check the command status
    if (fw_status != kStatus_Success)
    {
        throw std::runtime_error(fw_msg);
    }
}

// See Updater.h for documentation of this method.
void Updater::unlock(string backdoor_key)
{
    if (!isCommandSupported(kCommand_FlashSecurityDisable))
    {
        throw std::runtime_error("FlashSecurityDisable isn't supported!");
    }
    if (backdoor_key.length() != 16)
    {
        throw std::runtime_error("Illegal BackdoorKey");
    }

    FlashSecurityDisable cmd(strtoul(backdoor_key.substr(8, 8).c_str(), NULL, 16),
                             strtoul(backdoor_key.substr(0, 8).c_str(), NULL, 16));
    Log::info("inject command '%s'\n", cmd.getName().c_str());
    inject(cmd);

    uint32_t fw_status = cmd.getResponseValues()->at(0);
    std::string fw_msg = cmd.getStatusMessage(fw_status);

    // Check the command status
    if (fw_status != kStatus_Success)
    {
        throw std::runtime_error(fw_msg);
    }
}

// See Updater.h for documentation of this method.
bool Updater::isCommandSupported(const cmd_t &command)
{
    // Inject the get-property(available-commands) command.
    GetProperty cmd(kProperty_AvailableCommands);
    Log::info("inject command '%s'\n", cmd.getName().c_str());
    inject(cmd);

    uint32_t fw_status = cmd.getResponseValues()->at(0);
    uint32_t fw_response = cmd.getResponseValues()->at(1);
    std::string fw_msg = cmd.getStatusMessage(fw_status);

    // Check the command status
    if (fw_status != kStatus_Success)
    {
        throw std::runtime_error(fw_msg);
    }

    // See if the command is supported.
    return ((fw_response & command.mask) == command.mask);
}

uint32_vector_t Updater::getProperty(property_t tag)
{
    // Inject the get-property(tag) command.
    GetProperty cmd(tag);
    Log::info("inject command '%s'\n", cmd.getName().c_str());
    inject(cmd);

    uint32_t fw_status = cmd.getResponseValues()->at(0);
    std::string fw_msg = cmd.getStatusMessage(fw_status);

    // Check the command status
    if (fw_status != kStatus_Success)
    {
        throw std::runtime_error(fw_msg);
    }

    return *cmd.getResponseValues();
}
// See Updater.h for documentation of this method.
void Updater::eraseFlashRegion(uint32_t start, uint32_t length)
{
    // Align the length to a sector boundary.
    uint32_t alignedLength = (-(-static_cast<int>(length) & -(static_cast<int>(m_sector_size))));

    // Inject the flash-erase-region(start, length) command.
    FlashEraseRegion cmd(start, alignedLength);
    Log::info("inject command '%s'\n", cmd.getName().c_str());
    inject(cmd);

    uint32_t fw_status = cmd.getResponseValues()->at(0);
    std::string fw_msg = cmd.getStatusMessage(fw_status);

    // Check the command status
    if (fw_status != kStatus_Success)
    {
        throw std::runtime_error(fw_msg);
    }
}

// See Updater.h for documentation of this method.
void Updater::eraseFlashAll(uint32_t memoryId)
{
    // Inject the flash-erase-all command.
    FlashEraseAll cmd(memoryId);
    Log::info("inject command '%s'\n", cmd.getName().c_str());
    inject(cmd);

    uint32_t fw_status = cmd.getResponseValues()->at(0);
    std::string fw_msg = cmd.getStatusMessage(fw_status);

    // Check the command status
    if (fw_status != kStatus_Success)
    {
        throw std::runtime_error(fw_msg);
    }
}

// See Updater.h for documentation of this method.
void Updater::programOnce(uint32_t index, uint32_t byteCount, string data)
{
    if (!isCommandSupported(kCommand_FlashProgramOnce))
    {
        throw std::runtime_error("FlashProgramOnce isn't supported!");
    }
    if ((byteCount != 4) && (byteCount != 8))
    {
        throw std::runtime_error("Illegal byteCount! Must be 4 or 8");
    }
    if ((data.length() != 8) && (data.length() != 16))
    {
        throw std::runtime_error("Illegal data length. Must hex digits with no leading 0x");
    }

    FlashProgramOnce cmd(index, byteCount, strtoul(data.substr(0, 8).c_str(), NULL, 16),
                         strtoul(data.substr(8, 8).c_str(), NULL, 16));
    Log::info("inject command '%s'\n", cmd.getName().c_str());
    inject(cmd);

    uint32_t fw_status = cmd.getResponseValues()->at(0);
    std::string fw_msg = cmd.getStatusMessage(fw_status);

    // Check the command status
    if (fw_status != kStatus_Success)
    {
        throw std::runtime_error(fw_msg);
    }
}

// See Updater.h for documentation of this method.
void Updater::writeMemory(DataSource::Segment *segment)
{
    // Inject the write-memory(segment) command.
    WriteMemory cmd(segment);
    cmd.registerProgress(&m_progress);
    Log::info("inject command '%s'\n", cmd.getName().c_str());
    inject(cmd);

    uint32_t fw_status = cmd.getResponseValues()->at(0);
    std::string fw_msg = cmd.getStatusMessage(fw_status);

    // Check the command status
    if (fw_status != kStatus_Success)
    {
        throw std::runtime_error(fw_msg);
    }
}

// See Updater.h for documentation of this method.
void Updater::writeMemory(uint32_t address, const uchar_vector_t &data)
{
    // Inject the write-memory(segment) command.
    WriteMemory cmd(address, data);
    Log::info("inject command '%s'\n", cmd.getName().c_str());
    inject(cmd);

    uint32_t fw_status = cmd.getResponseValues()->at(0);
    std::string fw_msg = cmd.getStatusMessage(fw_status);

    // Check the command status
    if (fw_status != kStatus_Success)
    {
        throw std::runtime_error(fw_msg);
    }
}

// See Updater.h for documentation of this method.
status_t Updater::flashFromSourceFile()
{
    m_sourceFile->open();

    DataSource *dataSource = m_sourceFile->createDataSource();

    m_progress.m_segmentCount = dataSource->getSegmentCount();

    for (uint32_t index = 0; index < dataSource->getSegmentCount(); ++index)
    {
        DataSource::Segment *segment = dataSource->getSegmentAt(index);

        if (segment->hasNaturalLocation())
        {
            dataSource->setTarget(new NaturalDataTarget());
        }
        else
        {
            dataSource->setTarget(new ConstantDataTarget(m_base_address));
        }

        // If base address is in flash, do erase operation to erase the necessary flash.
        if ((segment->getBaseAddress() >= m_flashStart) && (segment->getBaseAddress() < m_flashStart + m_flashSize))
        {
            m_operation.current_task = 0;
            m_operation.tasks[m_operation.current_task].current += segment->getLength();
            if (m_progressCallback)
            {
                m_progressCallback(&m_operation);
            }

            eraseFlashRegion(segment->getBaseAddress(), segment->getLength());
        }
    }
    for (uint32_t index = 0; index < dataSource->getSegmentCount(); ++index)
    {
        DataSource::Segment *segment = dataSource->getSegmentAt(index);

        // Write the file to the base address.
        m_operation.current_task = 1;
        m_operation.tasks[m_operation.current_task].current += segment->getLength();
        if (m_progressCallback)
        {
            m_progressCallback(&m_operation);
        }
        m_progress.m_segmentIndex = index + 1;
        writeMemory(segment);
    }

    delete dataSource;
    m_sourceFile->close();

    return kStatus_Success;
}

// See Updater.h for documentation of this method.
status_t Updater::flashFromSBFile(const char *filename)
{
    // Inject the receive-sb-file command.
    m_operation.current_task = 1;
    if (m_progressCallback)
    {
        m_progressCallback(&m_operation);
    }
    ReceiveSbFile cmd(filename);
    cmd.registerProgress(&m_progress);
    Log::info("inject command '%s'\n", cmd.getName().c_str());
    inject(cmd);

    // print command response values using the Logger.
    cmd.logResponses();

    uint32_t fw_status = cmd.getResponseValues()->at(0);
    std::string fw_msg = cmd.getStatusMessage(fw_status);

    // Check the command status
    if ((fw_status != kStatus_Success) && (fw_status != kStatus_AbortDataPhase))
    {
        throw std::runtime_error(fw_msg);
    }
    return fw_status;
}