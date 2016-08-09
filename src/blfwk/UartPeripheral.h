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

#ifndef _uart_peripheral_h_
#define _uart_peripheral_h_

#include "Peripheral.h"
#include "packet/command_packet.h"

//! @addtogroup uart_peripheral
//! @{

namespace blfwk
{
/*!
 * @brief Peripheral that talks to the target device over COM port hardware.
 */
class UartPeripheral : public Peripheral
{
public:
    //! @breif Constants.
    enum _uart_peripheral_constants
    {
        // The read() implementation for the UartPeripheral does not use this the timeout parameter.
        kUartPeripheral_UnusedTimeout = 0,
        // Serial timeout is set to this default during init().
        kUartPeripheral_DefaultReadTimeoutMs = 1000,
        kUartPeripheral_DefaultBaudRate = 9600
    };

public:
    //! @brief Parameterized constructor that opens the serial port.
    //!
    //! Opens and configures the port. Throws exception if port configuration fails.
    //!
    //! Note: following COM port configuration is assumed: 8 bits, 1 stop bit, no parity.
    //!
    //! @param port OS file path for COM port. For example "COM1" on Windows.
    //! @param speed Port speed, e.g. 9600.
    UartPeripheral(const char *port, long speed = kUartPeripheral_DefaultBaudRate);

    //! @brief Destructor.
    virtual ~UartPeripheral();

    //! @brief Flush.
    //!
    //! should be called on an open COM port in order to flush any remaining data in the UART RX buffer
    void flushRX();

    //! @brief Read bytes.
    //!
    //! @param buffer Pointer to buffer.
    //! @param requestedBytes Number of bytes to read.
    //! @param actualBytes Number of bytes actually read.
    //! @param timeoutMs Time in milliseconds to wait for read to complete.
    virtual status_t read(uint8_t *buffer, uint32_t requestedBytes, uint32_t *actualBytes, uint32_t unused_timeoutMs);

    //! @brief Write bytes.
    //!
    //! @param buffer Pointer to buffer to write
    //! @param byteCount Number of bytes to write
    virtual status_t write(const uint8_t *buffer, uint32_t byteCount);

protected:
    //! @brief Initialize.
    //!
    //! Opens and configures the port.
    //!
    //! Note: following COM port configuration is assumed: 8 bits, 1 stop bit, no parity.
    //!
    //! @param port OS file path for COM port. For example "COM1" on Windows.
    //! @param speed Port speed, e.g. 9600.
    bool init(const char *port, long speed);

    int m_fileDescriptor;                    //!< Port file descriptor.
    uint8_t m_buffer[kDefaultMaxPacketSize]; //!< Buffer for bytes used to build read packet.
};

} // namespace blfwk

//! @}

#endif // _uart_peripheral_h_

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
