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

#include "blfwk/DataTarget.h"
#include "blfwk/DataSource.h"
#include "blfwk/BlfwkErrors.h"
#include <algorithm>

using namespace blfwk;

//! \exception blfwk::semantic_error Thrown if the source has multiple segments.
DataTarget::AddressRange ConstantDataTarget::getRangeForSegment(DataSource &source, DataSource::Segment &segment)
{
    // can't handle multi-segment data sources
    if (source.getSegmentCount() > 1)
    {
        throw semantic_error("constant targets only support single-segment sources");
    }

    // always relocate the segment to our begin address
    AddressRange range;
    range.m_begin = m_begin;

    if (isBounded())
    {
        // we have an end address. trim the result range to the segment size
        // or let the end address crop the segment.
        range.m_end = std::min<uint32_t>(m_end, m_begin + segment.getLength());
    }
    else
    {
        // we have no end address, so the segment size determines it.
        range.m_end = m_begin + segment.getLength();
    }

    return range;
}

//! If the \a segment has a natural location, the returned address range extends
//! from the segment's base address to its base address plus its length.
//!
//! \exception blfwk::semantic_error This exception is thrown if the \a segment
//!     does not have a natural location associated with it.
DataTarget::AddressRange NaturalDataTarget::getRangeForSegment(DataSource &source, DataSource::Segment &segment)
{
    if (!segment.hasNaturalLocation())
    {
        throw semantic_error("source has no natural location");
    }

    AddressRange range;
    range.m_begin = segment.getBaseAddress();
    range.m_end = segment.getBaseAddress() + segment.getLength();
    return range;
}
