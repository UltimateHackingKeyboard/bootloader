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

#include "blfwk/SimPeripheral.h"
#include "blfwk/Logging.h"

using namespace blfwk;

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////

// See sim_peripheral.h for documentation of this method.
status_t SimPeripheral::read(uint8_t *buffer, uint32_t requestedBytes, uint32_t *actualBytes, uint32_t timeoutMs)
{
    if (m_inStream->empty())
        return kStatus_Fail;

    uint32_t bytesRead = 0;
    for (int i = 0; i < (int)requestedBytes; ++i)
    {
        if (m_inStream->empty())
            break;
        unsigned char val = m_inStream->front();
        m_inStream->pop_front();
        buffer[i] = val;
        ++bytesRead;
    }

    if (actualBytes)
    {
        *actualBytes = bytesRead;
    }

    if (Log::getLogger()->getFilterLevel() == Logger::kDebug2)
    {
        // Log bytes read in hex
        Log::debug2("<");
        for (int i = 0; i < (int)bytesRead; i++)
        {
            Log::debug2("%02x", buffer[i]);
            if (i != (bytesRead - 1))
            {
                Log::debug2(" ");
            }
        }
        Log::debug2(">\n");
    }

    return kStatus_Success;
}

// See sim_peripheral.h for documentation of this method.
status_t SimPeripheral::write(const uint8_t *buffer, uint32_t byteCount)
{
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

    for (int i = 0; i < (int)byteCount; ++i)
    {
        m_outStream->push_back(buffer[i]);
    }

    return kStatus_Success;
}

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
