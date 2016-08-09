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

#ifndef _Bootloader_h_
#define _Bootloader_h_

#include "Command.h"
#include "Packetizer.h"
#include "Peripheral.h"
#include "Logging.h"

#include <time.h>

//! @addtogroup blfwk
//! @{

namespace blfwk
{
/*!
 * @brief Represents the host bootloader.
 *
 * This class provides a convenient way to access other bootloader
 * framework objects.
 */
class Bootloader
{
public:
    //! @brief Default Constructor for Simulator.
    Bootloader();

    //! @brief Constructor.
    Bootloader(const Peripheral::PeripheralConfigData &config);

    //! @brief Destructor.
    virtual ~Bootloader();

    //! @brief Inject a command into the bootloader.
    //!
    //! @param cmd The command to send
    void inject(Command &cmd)
    {
        clock_t start = clock();
        cmd.sendTo(*m_hostPacketizer);
        clock_t finish = clock();
        Log::debug("  - took %2.3f seconds\n", (double)(finish - start) / CLOCKS_PER_SEC);
    }

    //! @brief Flush state.
    void flush();

    //! \brief Execute the execute command.
    void execute(uint32_t entry_point, uint32_t param = 0, uint32_t stack_pointer = 0);

    //! \brief Execute the reset command.
    void reset();

    //! \brief Execute the get-property(current-version) command.
    standard_version_t getVersion();

    //! \brief Execute the get-property(flash-security-state) command.
    uint32_t getSecurityState();

    //! \brief Send a ping if applicable.
    void ping(int retries, unsigned int delay, int comSpeed);

    //! @name Accessors.
    //@{

    //! @brief Get the host packetizer.
    Packetizer *getPacketizer() const { return m_hostPacketizer; }
    //@}

protected:
    Packetizer *m_hostPacketizer; //!< Packet interface to send commands on.
    FileLogger *m_logger;         //!< Singleton logger instance.
};

} // namespace blfwk

//! @}

#endif // _Bootloader_h_

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
