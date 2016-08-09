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

#include "blfwk/UsbHidPacketizer.h"
#include "blfwk/Logging.h"
#include "blfwk/smart_ptr.h"
#include "blfwk/utils.h"
#include "bootloader/bootloader.h"
#ifdef LINUX
#include <string.h>
#endif

using namespace blfwk;

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////

// See usb_hid_packetizer.h for documentation of this method.
UsbHidPacketizer::UsbHidPacketizer(UsbHidPeripheral *peripheral, uint32_t packetTimeoutMs)
    : Packetizer(peripheral, packetTimeoutMs)
{
    m_continuousReadCount = 0;
}

// See usb_hid_packetizer.h for documentation of this method.
UsbHidPacketizer::~UsbHidPacketizer()
{
    delete m_peripheral;
}

// See usb_hid_packetizer.h for documentation of this method.
status_t UsbHidPacketizer::writePacket(const uint8_t *packet, uint32_t byteCount, packet_type_t packetType)
{
    assert(m_peripheral);
    if (byteCount)
    {
        assert(packet);
    }

    // Determine report ID based on packet type.
    uint8_t reportID;
    switch (packetType)
    {
        case kPacketType_Command:
            reportID = kBootloaderReportID_CommandOut;
            break;
        case kPacketType_Data:
            reportID = kBootloaderReportID_DataOut;
            break;
        default:
            Log::error("usbhid: unsupported packet type %d\n", (int)packetType);
            return kStatus_Fail;
    };

    if (m_isAbortEnabled && (reportID == kBootloaderReportID_DataOut))
    {
        // Check if the target has sent an abort report.
        if (pollForAbortPacket())
        {
            Log::info("usb hid detected receiver data abort\n");
            return kStatus_AbortDataPhase;
        }
    }

    // Construct report contents.
    memset(&m_report, 0, sizeof(m_report));
    m_report.header.reportID = reportID;
    m_report.header.packetLengthLsb = byteCount & 0xff;
    m_report.header.packetLengthMsb = (byteCount >> 8) & 0xff;

    // If not a zero-length report, copy in packet data.
    if (byteCount)
    {
        memcpy(m_report.packet, packet, byteCount);
    }

    m_continuousReadCount = 0;

    return getPeripheral()->write((uint8_t *)&m_report, sizeof(m_report), m_packetTimeoutMs);
}

// See usb_hid_packetizer.h for documentation of this method.
status_t UsbHidPacketizer::readPacket(uint8_t **packet, uint32_t *packetLength, packet_type_t packetType)
{
    assert(m_peripheral);
    assert(packet);
    assert(packetLength);
    *packet = NULL;
    *packetLength = 0;

    // Determine report ID based on packet type.
    uint8_t reportID;
    switch (packetType)
    {
        case kPacketType_Command:
            reportID = kBootloaderReportID_CommandIn;
            break;
        case kPacketType_Data:
            reportID = kBootloaderReportID_DataIn;
            break;
        default:
            Log::error("usbhid: unsupported packet type %d\n", (int)packetType);
            return kStatus_Fail;
    };

    // Read report.
    uint32_t actualBytes = 0;
    uint16_t lengthInPacket = 0;
    uint32_t retryCnt = 0;
    do
    {
        status_t retVal =
            m_peripheral->read((unsigned char *)&m_report, sizeof(m_report), &actualBytes, m_packetTimeoutMs);
        if (retVal != kStatus_Success)
        {
            return retVal;
        }

        if (!retryCnt)
        {
            m_continuousReadCount++;
        }

        // Check the report ID.
        if (m_report.header.reportID != reportID)
        {
            Log::error("usbhid: received unexpected report=%x\n", m_report.header.reportID);
            return kStatus_Fail;
        }

        // Extract the packet length encoded as bytes 1 and 2 of the report. The packet length
        // is transferred in little endian byte order.
        lengthInPacket = m_report.header.packetLengthLsb | (m_report.header.packetLengthMsb << 8);

        // See if we received the data abort packet,
        // if the data abort packet was received, try to read pending generic response packet.
        if (lengthInPacket == 0)
        {
            Log::info("usbhid: received data phase abort\n");

            // If continuous read occurs, that means this is a read-memory command,
            // host tool shouldn't wait for pending packet because there are no pending packets.
            if (m_continuousReadCount >= kContinuousReadMargin)
            {
                break;
            }
            retryCnt++;
        }
    } while (actualBytes && !lengthInPacket && retryCnt < kPollPacketMaxRetryCnt);

    // Make sure we got all of the packet. Target will send the maximum
    // report size, so there may be extra trailing bytes.
    if ((actualBytes - sizeof(m_report.header)) < lengthInPacket)
    {
        Log::error("usbhid: received only %d bytes of packet with length %d\n", actualBytes - sizeof(m_report.header),
                   lengthInPacket);
        return kStatus_Fail;
    }

    // Return results.
    *packet = m_report.packet;
    *packetLength = lengthInPacket;

    return kStatus_Success;
}

// See usb_hid_packetizer.h for documentation of this method.
void UsbHidPacketizer::flushInput()
{
    uint32_t actualBytes = 0;
    do
    {
        m_peripheral->read((unsigned char *)&m_report, sizeof(m_report), &actualBytes, m_packetTimeoutMs);
    } while (actualBytes > 0);
}

// See usb_hid_packetizer.h for documentation of this method.
void UsbHidPacketizer::abortPacket()
{
    // Abort data phase by writing a zero-length command packet.
    writePacket(NULL, 0, kPacketType_Command);
    flushInput();
}

bool UsbHidPacketizer::pollForAbortPacket()
{
    // Just check to see if there is data to be read from hid device.
    // No reason to wait (milliseconds = 0), because we aren't really expecting anything.
    uint32_t actualBytes = 0;
    m_peripheral->read((unsigned char *)&m_abortReport, sizeof(m_abortReport), &actualBytes, kPollAbortTimeoutMs);
    if (actualBytes == 0)
    {
        // No abort packet
        return false;
    }
    else
    {
        // Got an abort packet
        return true;
    }
}

// See usb_hid_packetizer.h for documentation of this method.
uint32_t UsbHidPacketizer::getMaxPacketSize()
{
    return kMinPacketBufferSize;
}

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
