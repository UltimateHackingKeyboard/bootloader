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

#ifndef _Peripheral_h_
#define _Peripheral_h_

#include "BusPal.h"
#include "bootloader_common.h"
#include <string>

//! @addtogroup host_peripherals
//! @{

namespace blfwk
{
/*!
 * @brief Represents a peripheral.
 *
 * Interface class for objects that provide the source for commands or sink for responses.
 */
class Peripheral
{
public:
    enum _host_peripheral_types
    {
        kHostPeripheralType_None,
        kHostPeripheralType_UART,
        kHostPeripheralType_BUSPAL_UART,
        kHostPeripheralType_USB_HID,
        kHostPeripheralType_SIM
    };

    struct PeripheralConfigData
    {
        _host_peripheral_types peripheralType;
        std::string comPortName;
        long comPortSpeed;
        uint32_t packetTimeoutMs;
        unsigned short usbHidVid;
        unsigned short usbHidPid;
        std::string usbHidSerialNumber;
        bool ping;
        BusPal::BusPalConfigData busPalConfig;
    };

    virtual ~Peripheral(){};

    //! @brief Read bytes.
    //!
    //! @param buffer Pointer to buffer
    //! @param requestedBytes Number of bytes to read
    //! @param timeoutMs Time in milliseconds to wait for read to complete.
    //! @param actualBytes Number of bytes actually read.
    virtual status_t read(uint8_t *buffer, uint32_t requestedBytes, uint32_t *actualBytes, uint32_t timeout) = 0;

    //! @brief Write bytes.
    virtual status_t write(const uint8_t *buffer, uint32_t byteCount) = 0;
};

} // namespace blfwk

//! @}

#endif // _Peripheral_h_

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
