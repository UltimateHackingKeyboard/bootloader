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

#ifndef _Memory_h_
#define _Memory_h_

#include "blfwk/host_types.h"

namespace blfwk
{
/*!
 * @brief Represents target device memory as a disk file.
 */
class MemoryStore
{
public:
    //! @brief Map indicies.
    enum
    {
        kMapIndexFlash = 0, //!< Flash memory
        kMapIndexSRAM = 1   //!< SRAM
    };

public:
    //! @brief Constructor that takes a map index.
    //!
    //! @param mapIndex Index into memory map array
    //! @param fillByte Optional byte erase value, default 0
    MemoryStore(int mapIndex, uint32_t fillByte = 0)
        : m_mapIndex(mapIndex)
        , m_fillByte(fillByte)
        , m_size(0)
        , m_startAddress(0)
        , m_memoryFile(NULL)
    {
    }

    //! @brief Open the store.
    //!
    //! @param pathToDir Directory for memory backing file.
    //! @param forceCreate True to re-create backing file even if it exists.
    bool open(const std::string &pathToDir, bool forceCreate);

    //! @brief Close the store.
    void close()
    {
        if (m_memoryFile)
        {
            fclose(m_memoryFile);
            m_memoryFile = NULL;
        }
    }

    //! @brief Read from memory.
    //!
    //! The requested offset is adjusted by the store's start address to create a zero-based
    //! file offset.
    //!
    //! @param offset Offset into memory region
    //! @param size Number of bytes to read
    //! @param buffer Destination buffer
    //! @return Number of bytes read
    size_t read(long int offset, size_t size, unsigned char *buffer);

    //! @brief Write to memory.
    //!
    //! The requested offset is adjusted by the store's start address to create a zero-based
    //! file offset.
    //!
    //! @param offset Offset into memory region
    //! @param size Number of bytes to write
    //! @param buffer Source buffer
    //! @return Number of bytes written
    size_t write(long int offset, size_t size, const unsigned char *buffer);

    //! @brief Erase memory.
    //!
    //! The requested offset is adjusted by the store's start address to create a zero-based
    //! file offset.
    //!
    //! @param offset Offset into memory region
    //! @param size Number of bytes to erase
    void erase(long int offset, size_t size);

    //! @brief Erase all memory.
    void erase() { erase(0, m_size); }
protected:
    int m_mapIndex;          //!< Index of memory map entry.
    uint8_t m_fillByte;      //!< Erase value.
    size_t m_size;           //!< Size of memory file.
    uint32_t m_startAddress; //!< Address address from map.
    FILE *m_memoryFile;      //!< Handle to memory file.
};

/*!
 * @brief Represents target Flash memory.
 */
class FlashMemoryStore : public MemoryStore
{
public:
    //! @brief Default Constructor.
    FlashMemoryStore()
        : MemoryStore(MemoryStore::kMapIndexFlash, ~0)
    {
    }
};

/*!
 * @brief Represents target SRAM memory.
 */
class SramMemoryStore : public MemoryStore
{
public:
    //! @brief Default Constructor.
    SramMemoryStore()
        : MemoryStore(MemoryStore::kMapIndexSRAM)
    {
    }
};

/*!
 * @brief Holds persistent options.
 */
class OptionsStore
{
public:
    //! @brief Constructor.
    OptionsStore()
        : m_optionsFile()
    {
    }

    //! @brief Initialize the store.
    //!
    //! @param pathToDir Directory for options file.
    //! @param forceCreate True to re-create options file even if it exists.
    bool init(const std::string &pathToDir, bool forceCreate);

    //! @brief Persist the store.
    void persist();

    //! @name Accessors.
    //@{

    //! @todo get/set for property store values

    //@}

protected:
    std::string m_optionsFile; //!< Options file name.
};

} // namespace blfwk

////////////////////////////////////////////////////////////////////////////////
// Prototypes
////////////////////////////////////////////////////////////////////////////////

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

//! @brief Read from simulated flash memory.
//!
//! @param address Simulated address.
//! @param length Number of bytes to read.
//! @param buffer Destination buffer.
//!
//! @retval kStatusMemoryReadFailed
//! @retval kStatus_Success
status_t sim_flash_read(uint32_t address, uint32_t length, uint8_t *buffer);

//! @brief Write to simulated flash memory.
//!
//! @param address Simulated address.
//! @param length Number of bytes to write.
//! @param buffer Source buffer.
//!
//! @retval kStatusMemoryWriteFailed
//! @retval kStatus_Success
status_t sim_flash_write(uint32_t address, uint32_t length, const uint8_t *buffer);

//! @brief Fill simulated flash memory.
//!
//! @param address Simulated address.
//! @param length Number of bytes to write.
//! @param pattern 4-byte pattern.
//!
//! @retval kStatusMemoryWriteFailed
//! @retval kStatus_Success
status_t sim_flash_fill(uint32_t address, uint32_t length, uint32_t pattern);

//! @brief Erase simulated flash memory.
//!
//! @param address Simulated address.
//! @param length Number of bytes to write.
//!
//! @retval kStatusMemoryWriteFailed
//! @retval kStatus_Success
status_t sim_flash_erase(uint32_t address, uint32_t length);

//! @brief Erase all simulated flash memory.
//!
//! @retval kStatusMemoryWriteFailed
//! @retval kStatus_Success
status_t sim_flash_erase_all(void);

//! @brief Read from simulated SRAM memory.
//!
//! @param address Simulated address.
//! @param length Number of bytes to read.
//! @param buffer Destination buffer.
//!
//! @retval kStatusMemoryReadFailed
//! @retval kStatus_Success
status_t sim_sram_mem_read(uint32_t address, uint32_t length, uint8_t *buffer);

//! @brief Write to simulated SRAM memory.
//!
//! @param address Simulated address.
//! @param length Number of bytes to write.
//! @param buffer Source buffer.
//!
//! @retval kStatusMemoryWriteFailed
//! @retval kStatus_Success
status_t sim_sram_mem_write(uint32_t address, uint32_t length, const uint8_t *buffer);

//! @brief Fill simulated SRAM memory.
//!
//! @param address Simulated address.
//! @param length Number of bytes to write.
//! @param pattern 4-byte pattern.
//!
//! @retval kStatusMemoryWriteFailed
//! @retval kStatus_Success
status_t sim_sram_mem_fill(uint32_t address, uint32_t length, uint32_t pattern);

//! Read from simulated device memory.
//!
//! Not supported.
//!
//! @retval kStatus_Success;
status_t sim_device_mem_read(uint32_t address, uint32_t length, uint8_t *buffer);

//! Write to simulated device memory.
//!
//! Not supported.
//!
//! @retval kStatus_Success;
status_t sim_device_mem_write(uint32_t address, uint32_t length, const uint8_t *buffer);

//! Fill simulated device memory.
//!
//! Not supported.
//!
//! @retval kStatus_Success;
status_t sim_device_mem_fill(uint32_t address, uint32_t length, uint32_t pattern);

#if defined(__cplusplus)
}
#endif // __cplusplus

#endif // _Memory_h_

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
