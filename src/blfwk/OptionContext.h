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
#if !defined(_OptionContext_h_)
#define _OptionContext_h_

#include <string>
#include "Value.h"

namespace blfwk
{
/*!
 * \brief Pure abstract interface class to a table of options.
 */
class OptionContext
{
public:
    //! @brief Force a virtual destructor.
    virtual ~OptionContext() {}
    //! \brief Detemine whether the named option is present in the table.
    //! \param name The name of the option to query.
    //! \retval true The option is present and has a value.
    //! \retval false No option with that name is in the table.
    virtual bool hasOption(const std::string &name) const = 0;

    //! \brief Returns the option's value.
    //! \param name The name of the option.
    //! \return The value for the option named \a name.
    //! \retval NULL No option is in the table with that name.
    virtual const Value *getOption(const std::string &name) const = 0;

    //! \brief Adds or changes an option's value.
    //!
    //! If the option was not already present in the table, it is added.
    //! Otherwise the old value is replaced.
    //!
    //! \param name The option's name.
    //! \param value New value for the option.
    virtual void setOption(const std::string &name, Value *value) = 0;

    //! \brief Removes an option from the table.
    //! \param name The name of the option to remove.
    virtual void deleteOption(const std::string &name) = 0;
};

}; // namespace blfwk

#endif // _OptionContext_h_
