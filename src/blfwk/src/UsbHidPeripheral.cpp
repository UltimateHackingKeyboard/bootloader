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

#include "blfwk/UsbHidPeripheral.h"
#include "blfwk/format_string.h"
#include "blfwk/smart_ptr.h"
#include "blfwk/Logging.h"

#include "bootloader_hid_report_ids.h"

using namespace blfwk;

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////

// See UsbHidPeripheral.h for documentation of this method.
UsbHidPeripheral::UsbHidPeripheral()
    : m_vendor_id(kDefault_Vid)
    , m_product_id(kDefault_Pid)
{
    if (!init())
    {
        throw std::runtime_error(
            format_string("Error: UsbHidPeripheral() cannot open USB HID device (vid=0x%04x, pid=0x%04x).", m_vendor_id,
                          m_product_id));
    }
}

// See UsbHidPeripheral.h for documentation of this method.
UsbHidPeripheral::UsbHidPeripheral(unsigned short vendor_id, unsigned short product_id, const char *serial_number)
    : m_vendor_id(vendor_id)
    , m_product_id(product_id)
{
    // Convert to a wchar_t*
    std::string s(serial_number);
    m_serial_number.assign(s.begin(), s.end());

    if (!init())
    {
        throw std::runtime_error(
            format_string("Error: UsbHidPeripheral() cannot open USB HID device (vid=0x%04x, pid=0x%04x, sn=%s).",
                          vendor_id, product_id, s.c_str()));
    }
}

// See UsbHidPeripheral.h for documentation of this method.
bool UsbHidPeripheral::init()
{
    // Open the device using the VID, PID,
    // and optionally the Serial number.
    m_device = hid_open(m_vendor_id, m_product_id, m_serial_number.c_str());
    if (!m_device)
    {
        return false;
    }

    return true;
}

// See UsbHidPeripheral.h for documentation of this method.
UsbHidPeripheral::~UsbHidPeripheral()
{
    if (m_device)
    {
        hid_close(m_device);
        /* Free static HIDAPI objects. */
        hid_exit();
    }
}

// See UsbHidPeripheral.h for documentation of this method.
status_t UsbHidPeripheral::read(uint8_t *buffer, uint32_t requestedBytes, uint32_t *actualBytes, uint32_t timeout)
{
    assert(buffer);

    // Read the requested number of bytes.
    int count = hid_read_timeout(m_device, buffer, requestedBytes, timeout);
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

    // Bail if we got an error (-1), or if the number of bytes read was less than
    // the report header.
    if (count < (int)sizeof(bl_hid_header_t))
    {
        if (count == -1)
        {
            return kStatus_Fail;
        }
        else
        {
            return kStatus_Timeout;
        }
    }

    return kStatus_Success;
}

// See UsbHidPeripheral.h for documentation of this method.
status_t UsbHidPeripheral::write(const uint8_t *buffer, uint32_t byteCount, uint32_t timeoutMS)
{
    assert(buffer);

    if (Log::getLogger()->getFilterLevel() == Logger::kDebug2)
    {
        // Log bytes written in hex
        Log::debug2("[");
        for (uint32_t i = 0; i < byteCount; i++)
        {
            Log::debug2("%02x", buffer[i]);
            if (i != (byteCount - 1))
            {
                Log::debug2(" ");
            }
        }
        Log::debug2("]\n");
    }

#ifdef LINUX
    int count = hid_write(m_device, buffer, byteCount);
#else
    int count = hid_write_timeout(m_device, buffer, byteCount, timeoutMS);
#endif
    if (count < 0)
    {
        const wchar_t *errorMessage = hid_error(m_device);
        if (errorMessage)
        {
            int len = wcslen(errorMessage);
            char *msg = new char[len + 1];
            wcstombs(msg, errorMessage, len + 1);
            Log::error("%s", msg);
            delete[] msg;
        }
        return kStatus_Fail;
    }

    return kStatus_Success;
}

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
