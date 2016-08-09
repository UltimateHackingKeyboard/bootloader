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
#if !defined(_Blob_h_)
#define _Blob_h_

#include "stdafx.h"

//! \class  Blob
//!
//! \brief  Manages a binary object of arbitrary length.
//!
//! The data block is allocated with malloc() instead of the new
//! operator so that we can use realloc() to resize it.
//!
class Blob
{
public:
    //! \brief Default constructor.
    Blob();

    //! \brief Constructor.
    Blob(const uint8_t *data, unsigned length);

    //! \brief Copy constructor.
    Blob(const Blob &other);

    //! \brief Destructor.
    virtual ~Blob();

    //! \name Operations
    //@{
    //! \brief Replaces the blob's data.
    void setData(const uint8_t *data, unsigned length);

    //! \brief Change the size of the blob's data.
    void setLength(unsigned length);

    //! \brief Adds data to the end of the blob.
    void append(const uint8_t *newData, unsigned newDataLength);

    //! \brief Disposes of the data.
    void clear();

    //! \brief Tell the blob that it no longer owns its data.
    void relinquish();
    //@}

    //! \name Accessors
    //@{
    uint8_t *getData() { return m_data; }
    const uint8_t *getData() const { return m_data; }
    unsigned getLength() const { return m_length; }
    //@}

    //! \name Operators
    //@{
    operator uint8_t *() { return m_data; }
    operator const uint8_t *() const { return m_data; }
    //@}

protected:
    uint8_t *m_data;   //!< The binary data held by this object.
    unsigned m_length; //!< Number of bytes pointed to by #m_data.
};

#endif // _Blob_h_
