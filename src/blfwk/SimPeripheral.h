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

#ifndef _sim_peripheral_h_
#define _sim_peripheral_h_

#include "blfwk/Peripheral.h"

namespace blfwk
{
/*!
 * @brief Peripheral that operates in the simulation space.
 *
 * Simulation peripherals are connected together using the streams provided to the init() method.
 * For example, to connect a "host" peripheral to a "device" peripheral, specify the host's output
 * stream as the device's input stream.
 */
class SimPeripheral : public Peripheral
{
public:
    //! @brief Default Constructor.
    SimPeripheral(uchar_deque_t *inStream, uchar_deque_t *outStream)
        : m_inStream(inStream)
        , m_outStream(outStream)
    {
    }

    //! @brief Read bytes.
    //!
    //! @param buffer Pointer to buffer.
    //! @param requestedBytes Number of bytes to read.
    //! @param actualBytes Number of bytes actually read.
    //! @param timeoutMs Time in milliseconds to wait for read to complete.
    virtual status_t read(uint8_t *buffer, uint32_t requestedBytes, uint32_t *actualBytes, uint32_t timeoutMs);

    //! @brief Write bytes.
    //!
    //! @param buffer Pointer to buffer to write
    //! @param byteCount Number of bytes to write
    virtual status_t write(const uint8_t *buffer, uint32_t byteCount);

protected:
    uchar_deque_t *m_inStream;  //!< Writes go to this stream.
    uchar_deque_t *m_outStream; //!< Reads come from this stream.
};

} // namespace blfwk

#endif // _sim_peripheral_h_

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
