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

#ifndef _usb_hid_packetizer_h_
#define _usb_hid_packetizer_h_

#include "Packetizer.h"
#include "UsbHidPeripheral.h"
#include "hidapi.h"

#include "bootloader_common.h"

#include "bootloader_hid_report_ids.h"

//! @addtogroup usb_hid_packetizer
//! @{

namespace blfwk
{
/*!
 * @brief Provides source and sink for packets that go over USB HID class.
 */
class UsbHidPacketizer : public Packetizer
{
public:
    //! @brief Constants
    enum _usbhid_contants
    {
        kReadFlushTimeoutMs = 100000,
#if defined(BL_WITHOUT_RECEIVE_SB_FILE_CMD)
        kPollAbortTimeoutMs = 0,
#else
        kPollAbortTimeoutMs = 10,
#endif
        kPollPacketMaxRetryCnt = 50,
        kContinuousReadMargin = 2,
    };
public:
    //! @brief Default Constructor.
    UsbHidPacketizer(UsbHidPeripheral *peripheral, uint32_t readPacketTimeoutMs);

    //! @brief Destructor.
    virtual ~UsbHidPacketizer();

    //! @brief Read a packet.
    //!
    //! Provides the address of a buffer containing the packet.
    //!
    //! @param packet Pointer location to write packet pointer
    //! @param packetLength Number of bytes in returned packet
    virtual status_t readPacket(uint8_t **packet, uint32_t *packetLength, packet_type_t packetType);

    //! @brief Write a packet.
    //!
    //! @param packet Pointer to packet to write
    //! @param byteCount Number of bytes in packet
    virtual status_t writePacket(const uint8_t *packet, uint32_t byteCount, packet_type_t packetType);

    //! @brief Abort data phase.
    virtual void abortPacket();

    //! @brief Send framing packet ack/nak.
    virtual void sync(){};

    //! @brief Finalize.
    virtual void finalize(){};

    //! @brief Enable simulator command processor pump.
    virtual void enableSimulatorPump() {}
    //! @brief Pump simulator command processor.
    virtual void pumpSimulator() {}
    //! @brief Set aborted flag.
    virtual void setAborted(bool aborted) {}
    //! @brief Returns the max packet size supported
    virtual uint32_t getMaxPacketSize();

    //! @brief Peripheral accessor.
    virtual UsbHidPeripheral *getPeripheral() { return (UsbHidPeripheral *)m_peripheral; }
protected:
    //! @brief Flush input from device.
    virtual void flushInput();

    //! @brief Poll overlapped read for receiver data phase abort.
    bool pollForAbortPacket();

protected:
    bl_hid_report_t m_report;      //!< Used for building and receiving the report.
    bl_hid_report_t m_abortReport; //!< Used for received abort report.

private:
    uint32_t
        m_continuousReadCount; //!< Used for distinguish abort report for write-memory/receive-sb-file or read-memory
};

} // namespace blfwk

//! @}

#endif // _usb_hid_packetizer_h_

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
