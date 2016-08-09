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
#if !defined(_DataTarget_h_)
#define _DataTarget_h_

#include "stdafx.h"
#include "DataSource.h"

namespace blfwk
{
// Forward declaration
class DataSource;

/*!
 * \brief Abstract base class for the target address or range of data.
 *
 * Targets at the most basic level have a single address, and potentially
 * an address range. Unbounded targets have a beginning address but no
 * specific end address, while bounded targets do have an end address.
 *
 * Users of a data target can access the begin and end addresses directly.
 * However, the most powerful way to use a target is with the
 * getRangeForSegment() method. This method returns the target address range
 * for a segment of a data source. The value of the resulting range can be
 * completely dependent upon the segment's properties, those of its data
 * source, and the type of data target.
 *
 * \see blfwk::DataSource
 */
class DataTarget
{
public:
    //! \brief Simple structure that describes an addressed region of memory.
    //! \todo Decide if the end address is inclusive or not.
    struct AddressRange
    {
        uint32_t m_begin;
        uint32_t m_end;
    };

public:
    //! \brief Default constructor.
    DataTarget()
        : m_source(0)
    {
    }

    //! \brief Destructor.
    virtual ~DataTarget() {}
    //! \brief Whether the target is just a single address or has an end to it.
    virtual bool isBounded() { return false; }
    virtual uint32_t getBeginAddress() { return 0; }
    virtual uint32_t getEndAddress() { return 0; }
    //! \brief Return the address range for a segment of a data source.
    virtual DataTarget::AddressRange getRangeForSegment(DataSource &source, DataSource::Segment &segment) = 0;

    inline void setSource(DataSource *source) { m_source = source; }
    inline DataSource *getSource() const { return m_source; }
protected:
    DataSource *m_source; //!< Corresponding data source for this target.
};

/*!
 * \brief Target with a constant values for the addresses.
 *
 * This target type supports can be both bounded and unbounded. It always has
 * at least one address, the beginning address. The end address is optional,
 * and if not provided makes the target unbounded.
 */
class ConstantDataTarget : public DataTarget
{
public:
    //! \brief Constructor taking only a begin address.
    ConstantDataTarget(uint32_t start)
        : DataTarget()
        , m_begin(start)
        , m_end(0)
        , m_hasEnd(false)
    {
    }

    //! \brief Constructor taking both begin and end addresses.
    ConstantDataTarget(uint32_t start, uint32_t end)
        : DataTarget()
        , m_begin(start)
        , m_end(end)
        , m_hasEnd(true)
    {
    }

    //! \brief The target is bounded if an end address was specified.
    virtual bool isBounded() { return m_hasEnd; }
    virtual uint32_t getBeginAddress() { return m_begin; }
    virtual uint32_t getEndAddress() { return m_end; }
    //! \brief Return the address range for a segment of a data source.
    virtual DataTarget::AddressRange getRangeForSegment(DataSource &source, DataSource::Segment &segment);

protected:
    uint32_t m_begin; //!< Start address.
    uint32_t m_end;   //!< End address.
    bool m_hasEnd;    //!< Was an end address specified?
};

/*!
 * \brief Target address that is the "natural" location of whatever the source data is.
 *
 * The data source used with the target must have a natural location. If
 * getRangeForSegment() is called with a segment that does not have a natural
 * location, a semantic_error will be thrown.
 */
class NaturalDataTarget : public DataTarget
{
public:
    //! \brief Default constructor.
    NaturalDataTarget()
        : DataTarget()
    {
    }

    //! \brief Natural data targets are bounded by their source's segment lengths.
    virtual bool isBounded() { return true; }
    //! \brief Return the address range for a segment of a data source.
    virtual DataTarget::AddressRange getRangeForSegment(DataSource &source, DataSource::Segment &segment);
};

}; // namespace blfwk

#endif // _DataTarget_h_
