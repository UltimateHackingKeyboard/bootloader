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
#if !defined(_StringMatcher_h_)
#define _StringMatcher_h_

#include <string>

namespace blfwk
{
/*!
 * \brief Abstract interface class used to select strings by name.
 */
class StringMatcher
{
public:
    //! \brief Performs a single string match test against testValue.
    //!
    //! \retval true The \a testValue argument matches.
    //! \retval false No match was made against the argument.
    virtual bool match(const std::string &testValue) = 0;
};

/*!
 * \brief String matcher subclass that matches all test strings.
 */
class WildcardMatcher : public StringMatcher
{
public:
    //! \brief Always returns true, indicating a positive match.
    virtual bool match(const std::string &testValue) { return true; }
};

/*!
 * \brief Simple string matcher that compares against a fixed value.
 */
class FixedMatcher : public StringMatcher
{
public:
    //! \brief Constructor. Sets the string to compare against to be \a fixedValue.
    FixedMatcher(const std::string &fixedValue)
        : m_value(fixedValue)
    {
    }

    //! \brief Returns whether \a testValue is the same as the value passed to the constructor.
    //!
    //! \retval true The \a testValue argument matches the fixed compare value.
    //! \retval false The argument is not the same as the compare value.
    virtual bool match(const std::string &testValue) { return testValue == m_value; }
protected:
    const std::string &m_value; //!< The section name to look for.
};

}; // namespace blfwk

#endif // _StringMatcher_h_
