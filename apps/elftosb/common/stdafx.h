/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
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

#ifndef stdafx_h_
#define stdafx_h_

// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

// Default to external release.
#ifndef SGTL_INTERNAL
#define SGTL_INTERNAL 0
#endif

#include <iostream>
#include <stdexcept>

#if defined(WIN32)
//#include <tchar.h>

// define this macro for use in VC++
#if !defined(__LITTLE_ENDIAN__)
#define __LITTLE_ENDIAN__ 1
#endif // !defined(__LITTLE_ENDIAN__)
#endif // defined(WIN32)

#if defined(Linux)
// For Linux systems only, types.h only defines the signed
// integer types.  This is not professional code.
// Update: They are defined in the header files in the more recent version of redhat enterprise gcc.
//#include "/usr/include/sys/types.h"
#include <stdint.h>
#include <limits.h>
// typedef unsigned long uint32_t;
// typedef unsigned short uint16_t;
// typedef unsigned char uint8_t;

//#define TCHAR char
//#define _tmain main

// give a default endian in case one is not defined on Linux (it should be, though)
#if !defined(__LITTLE_ENDIAN__) && !defined(__BIG_ENDIAN__)
#define __LITTLE_ENDIAN__ 1
#endif // !defined(__LITTLE_ENDIAN__) && !defined(__BIG_ENDIAN__)

#endif // defined(Linux)

// gcc on Mac OS X
#if defined(__GNUC__) && (defined(__APPLE_CPP__) || defined(__APPLE_CC__) || defined(__MACOS_CLASSIC__))
#include <TargetConditionals.h>

#if defined(TARGET_RT_LITTLE_ENDIAN) && TARGET_RT_LITTLE_ENDIAN
#if !defined(__LITTLE_ENDIAN__)
#define __LITTLE_ENDIAN__
#endif
#elif defined(TARGET_RT_BIG_ENDIAN) && TARGET_RT_BIG_ENDIAN
#if !defined(__BIG_ENDIAN__)
#define __BIG_ENDIAN__
#endif
#endif
#endif

#if !defined(TRUE)
#define TRUE 1
#endif // !defined(TRUE)

#if !defined(FALSE)
#define FALSE 0
#endif // !defined(FALSE)

#endif // stdafx_h_
