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

#ifndef _UsbHidPeripheral_h_
#define _UsbHidPeripheral_h_

#include "Peripheral.h"
#include "hidapi.h"

//! @addtogroup host_usb_hid_peripheral
//! @{

namespace blfwk
{
/*!
 * @brief Represents a USB HID peripheral.
 *
 * Interface class for objects that provide the source for commands or sink for responses.
 */
class UsbHidPeripheral : public Peripheral
{
public:
    //! @brief Constants
    enum _usbhid_contants
    {
        kDefault_Vid = 0x15a2, //!< Freescale VID
        kDefault_Pid = 0x0073, //!< PID for KL25Z48M
    };

public:
    //! @brief Default constructor.
    //!
    //! Uses vendor_id = kDefault_Vid and product_id = kDefault_Pid.
    UsbHidPeripheral();

    //! @brief Parameterized constructor.
    //!
    //! @param vendor_id The Vendor ID of the USB HID device.
    //! @param product_id The Product ID of the USB HID device.
    //! @param serial_number The Serial Number of the USB HID device.
    UsbHidPeripheral(unsigned short vendor_id, unsigned short product_id, const char *serial_number);

    //! @brief Destructor.
    virtual ~UsbHidPeripheral();

    //! @brief Read bytes.
    //!
    //! @param buffer Pointer to buffer
    //! @param requestedBytes Number of bytes to read
    //! @param timeoutMs Time in milliseconds to wait for read to complete.
    //! @param actualBytes Number of bytes actually read.
    virtual status_t read(uint8_t *buffer, uint32_t requestedBytes, uint32_t *actualBytes, uint32_t timeoutMS);

    //! @brief Write bytes. This is a do nothing function implemented here to satisfy abstract base class
    //! requirements. This function is not used. The write(buffer, count, timeout) function is used
    //! in this child class instead of the write(buffer, cout) function declared in the base class.
    virtual status_t write(const uint8_t *buffer, uint32_t byteCount) { return kStatus_Success; }
    //! @brief Write bytes.
    //!
    //! @param buffer Pointer to buffer to write
    //! @param byteCount Number of bytes to write
    //! @param timeoutMs Time in milliseconds to wait for write to complete.
    status_t write(const uint8_t *buffer, uint32_t byteCount, uint32_t timeoutMS);

    //! @brief Return USB Vendor ID
    unsigned short getVendorId() { return m_vendor_id; }
    //! @brief Return USB Product ID
    unsigned short getProductId() { return m_product_id; }
    //! @brief Return USB Serial Number
    const wchar_t *getSerialNumber() { return m_serial_number.c_str(); }
private:
    //! @brief Initialize.
    //!
    //! Opens the HID device.
    bool init();

    unsigned short m_vendor_id;
    unsigned short m_product_id;
    std::wstring m_serial_number;
    hid_device *m_device; //!< Device handle.
};

} // namespace blfwk

//! @}

#endif // _UsbHidPeripheral_h_

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
