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

#ifndef _BusPalPeripheral_h_
#define _BusPalPeripheral_h_

#include "UartPeripheral.h"
#include "BusPal.h"

//! @addtogroup bus_pal_peripheral
//! @{

namespace blfwk
{
/*!
 * @brief Peripheral that talks to the target device over BusPal UART hardware.
 */
class BusPalUartPeripheral : public UartPeripheral
{
public:
    //! @brief Parameterized constructor that opens the serial port.
    //!
    //! Opens and configures the port. Throws exception if port configuration fails.
    //!
    //! Note: following COM port configuration is assumed: 8 bits, 1 stop bit, no parity.
    //!
    //! @param port OS file path for COM port. For example "COM1" on Windows.
    //! @param speed Port speed, e.g. 9600.
    BusPalUartPeripheral(const char *port, long speed, const BusPal::BusPalConfigData &config);

    //! @brief Destructor.
    virtual ~BusPalUartPeripheral();

    //! @brief configure the bus pal with the passed in options
    void configure(const BusPal::BusPalConfigData &config);

    //! @brief Read bytes.
    //!
    //! @param buffer Pointer to buffer
    //! @param requestedBytes Number of bytes to read
    virtual status_t read(uint8_t *buffer, uint32_t requestedBytes, uint32_t *actualBytes, uint32_t timeoutMs);

    //! @brief Write bytes.
    //!
    //! @param buffer Pointer to buffer to write
    //! @param byteCount Number of bytes to write
    virtual status_t write(const uint8_t *buffer, uint32_t byteCount);

protected:
    BusPal *m_busPal; //!< Represents Bus Pal hardware.
};

} // namespace blfwk

//! @}

#endif // _BusPalPeripheral_h_

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
