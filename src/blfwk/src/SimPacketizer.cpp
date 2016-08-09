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

#include "blfwk/SimPacketizer.h"
#include "blfwk/Logging.h"
#include "bootloader/bl_command.h"
#include "bootloader/bootloader.h"

using namespace blfwk;

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////

// See SimPacketizer.h for documentation of this method.
SimPacketizer::SimPacketizer(SimPeripheral *peripheral)
    : Packetizer(dynamic_cast<Peripheral *>(peripheral), kSimReadTimeoutMs)
    , m_isPumpEnabled(false)
    , m_isAborted(false)
{
}

// See SimPacketizer.h for documentation of this method.
SimPacketizer::~SimPacketizer()
{
    delete m_peripheral;
}

// See SimPacketizer.h for documentation of this method.
void SimPacketizer::finalize()
{
}

// See SimPacketizer.h for documentation of this method.
status_t SimPacketizer::writePacket(const uint8_t *packet, uint32_t byteCount, packet_type_t packetType)
{
    assert(packet);

    // Check for receiver data phase abort.
    if (m_isAborted)
    {
        m_isAborted = false;
        return kStatus_AbortDataPhase;
    }

    // Write framing packet header.
    uint8_t buffer = (uint8_t)byteCount;
    status_t status = m_peripheral->write(&buffer, 1);

    // Write the packet.
    if (byteCount && (status == kStatus_Success))
    {
        status = m_peripheral->write(packet, byteCount);
    }

    pumpSimulator();
    return status;
}

// See SimPacketizer.h for documentation of this method.
status_t SimPacketizer::readPacket(uint8_t **packet, uint32_t *packetLength, packet_type_t packetType)
{
    assert(packet);
    assert(packetLength);
    *packet = NULL;
    *packetLength = 0;

    // Read framing packet header.
    uint8_t buffer;
    status_t status = m_peripheral->read(&buffer, 1, NULL, 0);
    if (status != kStatus_Success)
    {
        // fatal error in sumulator
        Log::error("Error: no data for readPacket\n");
        return status;
    }

    // Read the packet.
    int length = (int)(buffer);
    if (length == 0)
    {
        // zero length packet
        return kStatus_Success;
    }

    status = m_peripheral->read(m_buffer, length, NULL, 0);
    if (status != kStatus_Success)
    {
        Log::error("Error: malformed packet\n");
        return kStatus_Fail;
    }

    *packet = m_buffer;
    *packetLength = length;
    return kStatus_Success;
}

void SimPacketizer::pumpSimulator()
{
    if (m_isPumpEnabled)
    {
        bootloader_command_pump();
    }
}

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
