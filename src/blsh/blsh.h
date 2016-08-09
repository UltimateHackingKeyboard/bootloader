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

#ifndef __BLSH_H__
#define __BLSH_H__

#include <stdint.h>
#include <stdio.h>
#include "bootloader_common.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#define blsh_printf debug_printf
#define blsh_getchar wait_uart_char
#define blsh_putchar putchar

/*! @brief blsh command callback function */
typedef void (*blsh_func_t)(uint8_t argc, uint8_t **argv);

/*! @brief blsh command struct */
typedef struct _blsh_cmd
{
    uint8_t *name;          /* command input name, not 0. */
    uint8_t *help;          /* help string, can be 0. */
    uint8_t *usage;         /* usage string, can be 0. */
    blsh_func_t function;   /* function to launch on command, can be 0. */
    void *arg;              /* current argument when function called. */
    struct _blsh_cmd *next; /* next command, can be 0. */
} blsh_cmd_t;

/*******************************************************************************
 * API
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*! @brief blsh initialize */
void blsh_init(void);

/*! @brief blsh main loop */
void blsh_run(void);

/*! @brief exit blsh or not */
uint8_t blsh_exit(void);

/*! @brief add a new command */
void command_add(blsh_cmd_t *cmd);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* __BLSH_H__ */
