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
#if !defined(_StSRecordFile_h_)
#define _StSRecordFile_h_

//#include <stdint.h>
#include "stdafx.h"
#include <istream>
#include <string>
#include <vector>
#include <stdexcept>

enum
{
    //! The required first character of an S-record.
    SRECORD_START_CHAR = 'S',

    //! The minimum length of a S-record. This is the type (2) + count (2) + addr (4) + cksum (2).
    SRECORD_MIN_LENGTH = 10,

    //! Index of the first character of the address field.
    SRECORD_ADDRESS_START_CHAR_INDEX = 4
};

/*!
 * \brief S-record parser.
 *
 * This class takes an input stream and parses it as an S-record file. While
 * the individual records that comprise the file are available for access, the
 * class also provides a higher-level view of the contents. It processes the
 * individual records and builds an image of what the memory touched by the
 * file looks like. Then you can access the contiguous sections of memory.
 */
class StSRecordFile
{
public:
    /*!
     * Structure representing each individual line of the S-record input data.
     */
    struct SRecord
    {
        unsigned m_type;      //!< Record number type, such as 9 for "S9", 3 for "S3" and so on.
        unsigned m_count;     //!< Number of character pairs (bytes) from address through checksum.
        uint32_t m_address;   //!< The address specified as part of the S-record.
        unsigned m_dataCount; //!< Number of bytes of data.
        uint8_t *m_data;      //!< Pointer to data, or NULL if no data for this record type.
        uint8_t m_checksum;   //!< The checksum byte present in the S-record.
    };

    //! Iterator type.
    typedef std::vector<SRecord>::const_iterator const_iterator;

public:
    //! \brief Constructor.
    StSRecordFile(std::istream &inStream);

    //! \brief Destructor.
    virtual ~StSRecordFile();

    //! \name File name
    //@{
    virtual void setName(const std::string &inName) { m_name = inName; }
    virtual std::string getName() const { return m_name; }
    //@}

    //! \name Parsing
    //@{
    //! \brief Determine if the file is an S-record file.
    virtual bool isSRecordFile();

    //! \brief Parses the entire S-record input stream.
    virtual void parse();
    //@}

    //! \name Record access
    //@{
    //! \return the number of S-records that have been parsed from the input stream.
    inline unsigned getRecordCount() const { return static_cast<unsigned>(m_records.size()); }
    //! \return iterator for
    inline const_iterator getBegin() const { return m_records.begin(); }
    inline const_iterator getEnd() const { return m_records.end(); }
    //@}

    //! \name Operators
    //@{
    inline const SRecord &operator[](unsigned inIndex) { return m_records[inIndex]; }
    //@}

protected:
    std::istream &m_stream;         //!< The input stream for the S-record data.
    std::vector<SRecord> m_records; //!< Vector of S-records in the input data.

    std::string m_name; //!< File name. (optional)

    //! \name Parsing utilities
    //@{
    virtual void parseLine(std::string &inLine);

    bool isHexDigit(char c);
    int hexDigitToInt(char digit);
    int readHexByte(std::string &inString, int inIndex);
    //@}
};

/*!
 * \brief Simple exception thrown to indicate an error in the input SRecord data format.
 */
class StSRecordParseException : public std::runtime_error
{
public:
    //! \brief Default constructor.
    StSRecordParseException(const std::string &inMessage)
        : std::runtime_error(inMessage)
    {
    }
};

#endif // _StSRecordFile_h_
