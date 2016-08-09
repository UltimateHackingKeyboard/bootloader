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
#if !defined(_SRecordSourceFile_h_)
#define _SRecordSourceFile_h_

#include "SourceFile.h"
#include "StSRecordFile.h"
#include "StExecutableImage.h"

namespace blfwk
{
/*!
 * \brief Executable file in the Motorola S-record format.
 *
 * Instead of presenting each S-record in the file separately, this class
 * builds up a memory image of all of the records. Records next to each other
 * in memory are coalesced into a single memory region. The data source that
 * is returned from createDataSource() exposes these regions as its segments.
 *
 * Because the S-record format does not support the concepts, no support is
 * provided for named sections or symbols.
 */
class SRecordSourceFile : public SourceFile
{
public:
    //! \brief Default constructor.
    SRecordSourceFile(const std::string &path);

    //! \brief Destructor.
    virtual ~SRecordSourceFile() {}
    //! \brief Test whether the \a stream contains a valid S-record file.
    static bool isSRecordFile(std::istream &stream);

    //! \name Opening and closing
    //@{
    //! \brief Opens the file.
    virtual void open();

    //! \brief Closes the file.
    virtual void close();
    //@}

    //! \name Format capabilities
    //@{
    virtual bool supportsNamedSections() const { return false; }
    virtual bool supportsNamedSymbols() const { return false; }
    //@}

    //! \name Data sources
    //@{
    //! \brief Returns data source for the entire file.
    virtual DataSource *createDataSource();
    //@}

    //! \name Entry point
    //@{
    //! \brief Returns true if an entry point was set in the file.
    virtual bool hasEntryPoint();

    //! \brief Returns the entry point address.
    virtual uint32_t getEntryPointAddress();
    //@}

protected:
    StSRecordFile *m_file;                //!< S-record parser instance.
    StExecutableImage *m_image;           //!< Memory image of the S-record file.
    bool m_hasEntryRecord;                //!< Whether an S7,8,9 record was found.
    StSRecordFile::SRecord m_entryRecord; //!< Record for the entry point.

protected:
    //! \brief Build memory image of the S-record file.
    void buildMemoryImage();
};

}; // namespace blfwk

#endif // _SRecordSourceFile_h_
