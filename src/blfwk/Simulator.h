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

#ifndef _Simulator_h_
#define _Simulator_h_

#include "Bootloader.h"
#include "Command.h"
#include "SimulatorMemory.h"
#include "SimPacketizer.h"
#include "Peripheral.h"
#include "Logging.h"

#include "bootloader/bl_command.h"
#include "bootloader/bl_context.h"

namespace blfwk
{
/*!
 * @brief Represents the host bootloader.
 *
 * This class provides a convenient way to access other bootloader
 * framework objects.
 */
class Simulator : public Bootloader
{
public:
    //! @brief A vector of memory stores.
    typedef std::vector<blfwk::MemoryStore *> memory_vector_t;

    //! @brief Get the singleton simulator object.
    static Simulator &getSimulator()
    {
        //! @brief Singleton object.
        static Simulator theSimulator;
        return theSimulator;
    }

    //! @brief Destructor.
    virtual ~Simulator();

    //! @brief Initialize.
    void init();

    //! @brief Configure and open state files.
    //!
    //! Must be called to open or create state files.
    //!
    //! @param pathToDir Directory for state files.
    //! @param forceCreate True to re-create state files even if they exist.
    bool openStateFiles(const std::string &pathToDir, bool forceCreate);

    //! @name Accessors.
    //@{

    //! @brief Get the host packetizer.
    SimPacketizer *getHost() const { return dynamic_cast<SimPacketizer *>(m_hostPacketizer); }
    //! @brief Get the device packetizer.
    SimPacketizer *getDevice() const { return m_devicePacketizer; }
    //! @brief Get a device state memory store.
    //!
    //! index Index into memory map for the simulated device.
    MemoryStore *getMemoryStore(int index) const { return m_memoryStore[index]; }
    //@}

protected:
    //! @brief Constructor.
    Simulator();
    SimPacketizer *m_devicePacketizer; //!< Packet interface to recieve commands on.
    uchar_deque_t m_commandStream;
    uchar_deque_t m_responseStream;
    command_processor_data_t m_commandProcessor;
    bool m_areStateFilesOpen;      //!< True if state files are in use
    memory_vector_t m_memoryStore; //!< Vector of memory stores, one per map entry.
    OptionsStore m_optionsStore;   //!< Persistent options store.
    property_store_t m_propertyStore;
    peripheral_descriptor_t m_activePeripheral; //!< Descriptor for the active peripheral.
    FileLogger *m_logger;                       //!< Singleton logger instance.
};

} // namespace blfwk

#endif // _Simulator_h_

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
