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

#include "blfwk/Bootloader.h"
#include "blfwk/BusPalPeripheral.h"
#include "blfwk/SerialPacketizer.h"
#include "blfwk/UartPeripheral.h"
#include "blfwk/UsbHidPacketizer.h"
#include "blfwk/UsbHidPeripheral.h"
#include "blfwk/format_string.h"
#include "blfwk/utils.h"
#include "blfwk/json.h"
#include "packet/serial_packet.h"

using namespace blfwk;
using namespace std;

////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////
enum
{
    kBuspalReadRetries = 3
};

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////
// See host_bootloader.h for documentation of this method.
Bootloader::Bootloader()
    : m_hostPacketizer(NULL)
    , m_logger(NULL)
{
    // create logger instance
    if (Log::getLogger() == NULL)
    {
        this->m_logger = new FileLogger("bootloader.log");
        this->m_logger->setFilterLevel(Logger::kDebug2 /*Logger::kInfo*/);
        Log::setLogger(this->m_logger);
    }
}

// See host_bootloader.h for documentation of this method.
Bootloader::Bootloader(const Peripheral::PeripheralConfigData &config)
    : m_hostPacketizer(NULL)
    , m_logger(NULL)
{
    // create logger instance
    if (Log::getLogger() == NULL)
    {
        this->m_logger = new FileLogger("bootloader.log");
        this->m_logger->setFilterLevel(Logger::kDebug2 /*Logger::kInfo*/);
        Log::setLogger(this->m_logger);
    }

    switch (config.peripheralType)
    {
        case Peripheral::kHostPeripheralType_UART:
        {
            UartPeripheral *peripheral = new UartPeripheral(config.comPortName.c_str(), config.comPortSpeed);
            m_hostPacketizer = new SerialPacketizer(peripheral, config.packetTimeoutMs);

            if (config.ping)
            {
                // Send initial ping.
                try
                {
                    ping(0, 0, config.comPortSpeed);
                }
                catch (const std::exception &e)
                {
                    delete m_hostPacketizer;
                    m_hostPacketizer = NULL;
                    throw std::runtime_error(format_string("Error: Initial ping failure: %s", e.what()));
                }
            }

            break;
        }
        case Peripheral::kHostPeripheralType_USB_HID:
        {
            UsbHidPeripheral *peripheral =
                new UsbHidPeripheral(config.usbHidVid, config.usbHidPid, config.usbHidSerialNumber.c_str());
            m_hostPacketizer = new UsbHidPacketizer(peripheral, config.packetTimeoutMs);

            break;
        }
        case Peripheral::kHostPeripheralType_BUSPAL_UART:
        {
            BusPalUartPeripheral *peripheral =
                new BusPalUartPeripheral(config.comPortName.c_str(), config.comPortSpeed, config.busPalConfig);
            m_hostPacketizer = new SerialPacketizer(peripheral, config.packetTimeoutMs);

            // Send initial ping.
            // Bus pal peripheral interface will take care of the delays for us.
            if (config.ping)
            {
                uint32_t buspalReadRetries;
#if defined(DEBUG)
                buspalReadRetries = 0;
#else
                buspalReadRetries = kBuspalReadRetries;
#endif
                try
                {
                    ping(buspalReadRetries, 0, 0);
                }
                catch (const std::exception &e)
                {
                    throw std::runtime_error(format_string("Error: Initial ping failure: %s", e.what()));
                }
            }

            break;
        }
        default:
            throw std::runtime_error(format_string("Error: Unsupported peripheral type(%d).", config.peripheralType));
    }
}

// See host_bootloader.h for documentation of this method.
Bootloader::~Bootloader()
{
    flush();

    // Delete packetizer should close handles and free memory on Peripheral.
    delete m_hostPacketizer;
    m_hostPacketizer = NULL;
}

// See host_bootloader.h for documentation of this method.
void Bootloader::flush()
{
    // Finalize the packet interface.
    if (m_hostPacketizer)
    {
        m_hostPacketizer->finalize();
    }
}

// See host_bootloader.h for documentation of this method.
void Bootloader::execute(uint32_t entry_point, uint32_t param, uint32_t stack_pointer)
{
    // Inject the execute(start_address, param, stack_pointer) command.
    Execute cmd(entry_point, param, stack_pointer);
    Log::info("Inject command '%s'\n", cmd.getName().c_str());
    this->inject(cmd);

    uint32_t fw_status = cmd.getResponseValues()->at(0);
    std::string fw_msg = cmd.getStatusMessage(fw_status);

    // Check the command status
    if (fw_status != kStatus_Success)
    {
        throw std::runtime_error(fw_msg);
    }
}

// See host_bootloader.h for documentation of this method.
void Bootloader::reset()
{
    // Inject the reset command.
    Reset cmd;
    Log::info("Inject command '%s'\n", cmd.getName().c_str());
    this->inject(cmd);

    uint32_t fw_status = cmd.getResponseValues()->at(0);
    std::string fw_msg = cmd.getStatusMessage(fw_status);

    // Check the command status
    if (fw_status != kStatus_Success)
    {
        throw std::runtime_error(fw_msg);
    }
}

// See host_bootloader.h for documentation of this method.
standard_version_t Bootloader::getVersion()
{
    // Inject the reset command.
    GetProperty cmd(kProperty_CurrentVersion);
    Log::info("inject command '%s'\n", cmd.getName().c_str());
    this->inject(cmd);

    uint32_t fw_status = cmd.getResponseValues()->at(0);
    std::string fw_msg = cmd.getStatusMessage(fw_status);

    // Check the command status
    if (fw_status != kStatus_Success)
    {
        throw std::runtime_error(fw_msg);
    }

    return standard_version_t(cmd.getResponseValues()->at(1));
}

// See host_bootloader.h for documentation of this method.
uint32_t Bootloader::getSecurityState()
{
    // Inject the reset command.
    GetProperty cmd(kProperty_FlashSecurityState);
    Log::info("inject command '%s'\n", cmd.getName().c_str());
    this->inject(cmd);

    uint32_t fw_status = cmd.getResponseValues()->at(0);
    std::string fw_msg = cmd.getStatusMessage(fw_status);

    // Check the command status
    if (fw_status != kStatus_Success)
    {
        throw std::runtime_error(fw_msg);
    }

    return cmd.getResponseValues()->at(1);
}

// See host_bootloader.h for documentation of this method.
void Bootloader::ping(int retries, unsigned int delay, int comSpeed)
{
    this->flush();

    SerialPacketizer *pPacketizer = dynamic_cast<SerialPacketizer *>(m_hostPacketizer);
    if (pPacketizer)
    {
        status_t status = pPacketizer->ping(retries, delay, NULL, comSpeed);
        if (status != kStatus_Success)
        {
            this->flush();

            Reset cmd; // dummy command to get access to status text.
            // report ping failure in JSON output mode.
            Json::Value root;
            root["command"] = "ping";
            root["status"] = Json::Value(Json::objectValue);
            root["status"]["value"] = static_cast<int32_t>(status);
            root["status"]["description"] =
                format_string("%d (0x%X) %s", status, status, cmd.getStatusMessage(status).c_str());
            root["response"] = Json::Value(Json::arrayValue);

            Json::StyledWriter writer;
            Log::json(writer.write(root).c_str());

            throw std::runtime_error(cmd.getStatusMessage(status));
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
