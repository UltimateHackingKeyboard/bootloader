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

#include "blfwk/UartPeripheral.h"
#include "blfwk/Logging.h"
#include "blfwk/format_string.h"
#include "blfwk/serial.h"

using namespace blfwk;

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////

// See uart_peripheral.h for documentation of this method.
UartPeripheral::UartPeripheral(const char *port, long speed)
    : m_fileDescriptor(-1)
{
    if (!init(port, speed))
    {
        throw std::runtime_error(
            format_string("Error: UartPeripheral() cannot open PC UART port(%s), speed(%d Hz).", port, speed));
    }
}

// See uart_peripheral.h for documentation of this method.
bool UartPeripheral::init(const char *port, long speed)
{
    assert(port);

    // Open the port.
    m_fileDescriptor = serial_open(const_cast<char *>(port));
    if (m_fileDescriptor == -1)
    {
        return false;
    }

    serial_setup(m_fileDescriptor, speed);

    // Flush garbage from receive buffer before setting read timeout.
    flushRX();

    // Set host serial timeout to 10 milliseconds. Higherlevel timeouts are implemented in
    // SerialPacketizer.cpp
    serial_set_read_timeout(m_fileDescriptor, kUartPeripheral_DefaultReadTimeoutMs);

    return true;
}

// See host_peripheral.h for documentation of this method.
UartPeripheral::~UartPeripheral()
{
    if (m_fileDescriptor != -1)
    {
        serial_close(m_fileDescriptor);
    }
}

// See host_peripheral.h for documentation of this method.
status_t UartPeripheral::read(uint8_t *buffer,
                              uint32_t requestedBytes,
                              uint32_t *actualBytes,
                              uint32_t unused_timeoutMs)
{
    assert(buffer);

    // Read the requested number of bytes.
    int count = serial_read(m_fileDescriptor, reinterpret_cast<char *>(buffer), requestedBytes);
    if (actualBytes)
    {
        *actualBytes = count;
    }

    if (Log::getLogger()->getFilterLevel() == Logger::kDebug2)
    {
        // Log bytes read in hex
        Log::debug2("<");
        for (int i = 0; i < (int)count; i++)
        {
            Log::debug2("%02x", buffer[i]);
            if (i != (count - 1))
            {
                Log::debug2(" ");
            }
        }
        Log::debug2(">\n");
    }

    if (count < (int)requestedBytes)
    {
        // Anything less than requestedBytes is a timeout error.
        return kStatus_Timeout;
    }

    return kStatus_Success;
}

// See uart_peripheral.h for documentation of this method.
void UartPeripheral::flushRX()
{
// An attempt was made on win32 to use a serial_flush function
// which would call PurgeComm(hCom, PURGE_RXABORT | PURGE_TXABORT | PURGE_RXCLEAR | PURGE_TXCLEAR)
// even though the function returned success there were still errant data in the RX buffer. Using reads
// to empty the RX buffer has worked

// This read loop never exits on the Mac, and doesn't appear to be necessary.
#if (defined(WIN32) || defined(LINUX))
    // Read up to the requested number of bytes.
    char *readBuf = reinterpret_cast<char *>(m_buffer);
    while (serial_read(m_fileDescriptor, readBuf, 16))
    {
        readBuf = reinterpret_cast<char *>(m_buffer);
    }
#endif // defined(WIN32) || defined(LINUX)
}

// See host_peripheral.h for documentation of this method.
status_t UartPeripheral::write(const uint8_t *buffer, uint32_t byteCount)
{
    assert(buffer);

    if (Log::getLogger()->getFilterLevel() == Logger::kDebug2)
    {
        // Log bytes written in hex
        Log::debug2("[");
        for (int i = 0; i < (int)byteCount; i++)
        {
            Log::debug2("%02x", buffer[i]);
            if (i != (byteCount - 1))
            {
                Log::debug2(" ");
            }
        }
        Log::debug2("]\n");
    }

    if (serial_write(m_fileDescriptor, reinterpret_cast<char *>(const_cast<uint8_t *>(buffer)), byteCount) == byteCount)
        return kStatus_Success;
    else
        return kStatus_Fail;
}

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
