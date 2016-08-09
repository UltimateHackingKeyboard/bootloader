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

#include <ctype.h>
#include <algorithm>
#include "string.h"
#include "blfwk/stdafx.h"
#include "blfwk/EndianUtilities.h"
#include "blfwk/GHSSecInfo.h"
#include "blfwk/Logging.h"
#include "blfwk/SBSourceFile.h"

using namespace blfwk;

SBSourceFile::SBSourceFile(const std::string &path)
    : BinarySourceFile(path, kSBSourceFile)
{
}

SBSourceFile::~SBSourceFile()
{
}

bool SBSourceFile::isSBFile(std::istream &stream)
{
    try
    {
        boot_image_header_t header; //!< Header from the SB boot image.

        // readImageHeader
        // seek to beginning of the stream/file and read the plaintext header
        stream.seekg(0, std::ios_base::beg);
        if (stream.read((char *)&header, sizeof(header)).bad())
        {
            throw SBFileException("failed to read SB image header");
        }

        header.m_flags = ENDIAN_LITTLE_TO_HOST_U16(header.m_flags);
        header.m_imageBlocks = ENDIAN_LITTLE_TO_HOST_U32(header.m_imageBlocks);
        header.m_firstBootTagBlock = ENDIAN_LITTLE_TO_HOST_U32(header.m_firstBootTagBlock);
        header.m_firstBootableSectionID = ENDIAN_LITTLE_TO_HOST_U32(header.m_firstBootableSectionID);
        header.m_keyCount = ENDIAN_LITTLE_TO_HOST_U16(header.m_keyCount);
        header.m_keyDictionaryBlock = ENDIAN_LITTLE_TO_HOST_U16(header.m_keyDictionaryBlock);
        header.m_headerBlocks = ENDIAN_LITTLE_TO_HOST_U16(header.m_headerBlocks);
        header.m_sectionCount = ENDIAN_LITTLE_TO_HOST_U16(header.m_sectionCount);
        header.m_sectionHeaderSize = ENDIAN_LITTLE_TO_HOST_U16(header.m_sectionHeaderSize);
        header.m_timestamp = ENDIAN_LITTLE_TO_HOST_U64(header.m_timestamp);

        // check header signature 1
        if (header.m_signature[0] != 'S' || header.m_signature[1] != 'T' || header.m_signature[2] != 'M' ||
            header.m_signature[3] != 'P')
        {
            throw SBFileException("invalid SB signature 1");
        }

        // check header signature 2 for version 1.1 and greater
        if ((header.m_majorVersion > 1 || (header.m_majorVersion == 1 && header.m_minorVersion >= 1)) &&
            (header.m_signature2[0] != 's' || header.m_signature2[1] != 'g' || header.m_signature2[2] != 't' ||
             header.m_signature2[3] != 'l'))
        {
            Log::log(Logger::kWarning, "warning: invalid SB signature 2\n");
        }

        return true;
    }
    catch (...)
    {
        return false;
    }
}

DataSource *SBSourceFile::createDataSource()
{
    throw std::runtime_error("SBSourceFile::createDataSource() has not been implemented.");
}
