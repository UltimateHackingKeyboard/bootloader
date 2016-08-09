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

#include <sstream>
#include <string>
#include <vector>
#include <stdint.h>
#include "blfwk/format_string.h"
#ifdef LINUX
#include <stdlib.h>
#endif

namespace utils
{
std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems)
{
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim))
    {
        elems.push_back(item);
    }
    return elems;
}

std::vector<std::string> string_split(const std::string &s, char delim)
{
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}

std::string string_hex(const std::string &s)
{
    std::string hex;
    std::string::const_iterator it = s.begin();
    for (; it != s.end(); ++it)
    {
        if (isxdigit(*it))
        {
            hex.append(1, *it);
        }
    }

    return hex;
}

bool stringtoi(const std::string &s, int32_t &number)
{
    if (s.empty())
        return false;

    char *p;
    int64_t temp;
    temp = strtoll(s.c_str(), &p, 0);
    if ((temp > INT32_MAX) || (temp < INT32_MIN))
    {
        return false;
    }
    number = static_cast<int32_t>(temp);
    return (p != NULL) && (*p == 0);
}

bool stringtoui(const std::string &s, uint32_t &number)
{
    if (s.empty())
        return false;
    if (s[0] == '-')
        return false;

    char *p;
    uint64_t temp;
    temp = strtoull(s.c_str(), &p, 0);
    if (temp > UINT32_MAX)
    {
        return false;
    }
    number = static_cast<uint32_t>(temp);
    return (p != NULL) && (*p == 0);
}

// GB, MB, KB, bytes
std::string scale_bytes(uint64_t sizeInBytes)
{
    double originalSize = (double)sizeInBytes;
    double scaledSize = 0;

    scaledSize = originalSize / (1024 * 1024 * 1024);
    if (scaledSize >= 1.0) // GB
    {
        if (sizeInBytes % (1024 * 1024 * 1024))
            return format_string("%.3f GB", scaledSize);
        else
            return format_string("%.f GB", scaledSize);
    }

    scaledSize = originalSize / (1024 * 1024);
    if (scaledSize >= 1.0) // MB
    {
        if (sizeInBytes % (1024 * 1024))
            return format_string("%.3f MB", scaledSize);
        else
            return format_string("%.f MB", scaledSize);
    }

    scaledSize = originalSize / 1024;
    if (scaledSize >= 1.0) // KB
    {
        if (sizeInBytes % 1024)
            return format_string("%.3f KB", scaledSize);
        else
            return format_string("%.f KB", scaledSize);
    }
    else // bytes
    {
        return format_string("%d bytes", sizeInBytes);
    }

} // ScaleBytes()

} // namespace utils

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
