/*
 * Copyright (c) 2013 - 2014, Freescale Semiconductor, Inc.
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

#include "bllibc.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

uint32_t bl_strstart(uint8_t *dst, uint8_t *src)
{
    while (*src && (*src == *dst))
    {
        src++;
        dst++;
    }

    if ((*src == ' ') || (*src == 0))
    {
        if (*dst == 0)
            return k_fullMatch;
        else
            return k_partMatch;
    }
    else
        return k_unmatch;
}

bool bl_atoi(uint32_t *dst, uint8_t *str)
{
    int32_t ishex = 0;
    uint32_t ret = 0;

    if (*str == 0)
        return 0;

    if ((*str == '0') && (*(str + 1) == 'x'))
    {
        ishex = 1;
        str += 2;
    }

    while (*str)
    {
        if (ishex)
            ret *= 16;
        else
            ret *= 10;

        if ((*str >= '0') && (*str <= '9'))
        {
            ret += *str - '0';
        }
        else if (ishex && (*str >= 'a') && (*str <= 'f'))
        {
            ret += *str - 'a' + 10;
        }
        else if (ishex && (*str >= 'A') && (*str <= 'F'))
        {
            ret += *str - 'A' + 10;
        }
        else if (*str == '\0')
        {
            break;
        }
        else
        {
            *dst = 0;
            return false;
        }
        str++;
    }
    *dst = ret;

    return true;
}

uint8_t *bl_litoa(int64_t num)
{
    int32_t sign = num;
    int32_t i = 0;
    int32_t j = 0;
    uint8_t temp[100];
    static uint8_t str[100];

    if (sign < 0)
    {
        num = -num;
    }
    do
    {
        temp[i] = num % 10 + '0';
        num /= 10;
        i++;
    } while (num > 0);
    if (sign < 0)
    {
        temp[i++] = '-';
    }
    temp[i] = '\0';
    i--;
    while (i >= 0)
    {
        str[j] = temp[i];
        j++;
        i--;
    }
    str[j] = '\0';

    return str;
}

static uint8_t bl_htoi(uint8_t hex)
{
    if ((hex >= '0') && (hex <= '9'))
    {
        return hex - '0';
    }
    else if ((hex >= 'a') && (hex <= 'f'))
    {
        return 10 + hex - 'a';
    }
    else if ((hex >= 'A') && (hex <= 'F'))
    {
        return 10 + hex - 'A';
    }

    return 0;
}

uint8_t read_hex_byte(uint8_t *buffer, uint32_t index)
{
    uint8_t char_high = buffer[index];
    uint8_t char_low = buffer[index + 1];

    return (bl_htoi(char_high) << 4) | (bl_htoi(char_low));
}
