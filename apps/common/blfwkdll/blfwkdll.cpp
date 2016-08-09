/*
* Copyright (c) 2013-15, Freescale Semiconductor, Inc.
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

#include "blfwkdll.h"
#include "blfwk/Bootloader.h"
#include "blfwk/Updater.h"
#include "blfwk/SerialPacketizer.h"
#include "blfwk/Crc.h"

namespace blfwkdll
{
// See blfwkdll.h for documentation of this method.
Updater::Updater(PeripheralConfig *config)
{
    blfwk::Peripheral::PeripheralConfigData *pinnedConfig = (blfwk::Peripheral::PeripheralConfigData *)config;
    updater = NULL;
    try
    {
        updater = new blfwk::Updater(*pinnedConfig);
    }
    catch (exception e)
    {
        throw e;
    }
}

// See blfwkdll.h for documentation of this method.
Updater::~Updater()
{
    // Clean up unmanaged code.
    if (updater != NULL)
    {
        delete (blfwk::Updater *)updater;
        updater = NULL;
    }
}

// See blfwkdll.h for documentation of this method.
void Updater::registerCallback(void (*progress)(int, int, int), bool *abort)
{
    ((blfwk::Updater *)updater)->registerCallback(progress, abort);
}

// See blfwkdll.h for documentation of this method.
void Updater::eraseAllUnsecure()
{
    try
    {
        ((blfwk::Updater *)updater)->eraseAllUnsecure();
    }
    catch (const std::exception &e)
    {
        throw e;
    }
}

// See blfwkdll.h for documentation of this method.
void Updater::unlockWithKey(const std::string &backdoorKey)
{
    try
    {
        ((blfwk::Updater *)updater)->unlock(backdoorKey);
    }
    catch (const std::exception &e)
    {
        throw e;
    }
}

/* clang-format off */
/* the for each statement is non-standard and not supported by clang format */
// See blfwkdll.h for documentation of this method.
bool Updater::isCommandSupported(const std::string &command)
{
    try
    {
        for each(blfwk::cmd_t var in blfwk::kCommands)
            {
                if (command.compare(var.name) == 0)
                {
                    return ((blfwk::Updater *)updater)->isCommandSupported(var);
                }
            }
        return false;
    }
    catch (const std::exception &e)
    {
        throw e;
    }
}
/* clang-format on */

// See blfwkdll.h for documentation of this method.
uint32_t Updater::flashFirmware(std::string *filename, uint32_t baseAddress)
{
    try
    {
        uint32_t status;
        status = ((blfwk::Updater *)updater)->flashFirmware(filename->c_str(), baseAddress);
        return status;
    }
    catch (const std::exception &e)
    {
        throw e;
    }
}

// See blfwkdll.h for documentation of this method.
void Updater::reset()
{
    try
    {
        ((blfwk::Updater *)updater)->reset();
        // delete updater;
        // updater = NULL;
    }
    catch (const std::exception &e)
    {
        // delete this;
        throw e;
    }
}

// See blfwkdll.h for documentation of this method.
uint32_t Updater::getSerialProtocolVersion()
{
    try
    {
        return ((blfwk::Updater *)updater)->getPacketizer()->getVersion().version;
    }
    catch (const std::exception &e)
    {
        throw e;
    }
}

// See blfwkdll.h for documentation of this method.
void Updater::getProperty(PROPERTY_TAG tag, uint32_t *responseWords)
{
    blfwk::property_t propertytag = blfwk::kProperties.at(tag);
    std::vector<uint32_t> value = ((blfwk::Updater *)updater)->getProperty(propertytag);
    for (size_t i = 0; i < value.size(); i++)
    {
        responseWords[i] = value.at(i);
    }
}

// See blfwkdll.h for documentation of this method.
uint32_t Updater::getSectorSize()
{
    return ((blfwk::Updater *)updater)->getSectorSize();
}

// See blfwkdll.h for documentation of this method.
uint32_t Updater::getFlshSize()
{
    return ((blfwk::Updater *)updater)->getFlshSize();
}

// See blfwkdll.h for documentation of this method.
void Updater::ping(int32_t retries, uint32_t delay, uint32_t comSpeed)
{
    try
    {
        ((blfwk::Updater *)updater)->ping(retries, delay, comSpeed);
    }
    catch (const std::exception &e)
    {
        throw e;
    }
}

// See blfwkdll.h for documentation of this method.
void Updater::eraseFlashRegion(uint32_t start, uint32_t length)
{
    try
    {
        ((blfwk::Updater *)updater)->eraseFlashRegion(start, length);
    }
    catch (const std::exception &e)
    {
        throw e;
    }
}

// See blfwkdll.h for documentation of this method.
void Updater::eraseFlashAll(uint32_t memoryId)
{
    try
    {
        ((blfwk::Updater *)updater)->eraseFlashAll(memoryId);
    }
    catch (const std::exception &e)
    {
        throw e;
    }
}

// See blfwkdll.h for documentation of this method.
void Updater::programOnce(uint32_t index, uint32_t byteCount, const std::string &data)
{
    try
    {
        ((blfwk::Updater *)updater)->programOnce(index, byteCount, data);
    }
    catch (const std::exception &e)
    {
        throw e;
    }
}

// See blfwkdll.h for documentation of this method.
uint32_t Crc::calculate_application_crc32(const uint8_t *start, uint32_t length)
{
    return blfwk::Crc::calculate_application_crc32(start, length);
}

} // namespace blfwkdll;
