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

#include "blsh.h"
#include "bllibc.h"
#include "host_hardware.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief input buffer size */
#define k_cmdBufferSize 256

/*! @brief input History depth */
#define k_cmdHistoryDepth 16

/*! @brief max input command args */
#define k_cmdMaxArgs 16

/*******************************************************************************
 * Variables
 ******************************************************************************/
/*! @brief help command definition */
static void help_func(uint8_t argc, uint8_t **argv);
static blsh_cmd_t help_cmd = { "help", "Display commands list and usage", "help", help_func, 0, 0 };
static blsh_cmd_t *root_cmd = &help_cmd;

/*! @brief exit command definition */
static void exit_func(uint8_t argc, uint8_t **argv);
static blsh_cmd_t exit_cmd = { "exit", "Exit the blsh", "exit", exit_func, 0, 0 };

/*! @brief blsh input buffer and index
 */
static uint8_t s_inputBuffer[k_cmdHistoryDepth][k_cmdBufferSize + 1] = { 0 };
static uint32_t s_curCmdIndex = 0;
static uint32_t s_curBufIndex = 0;

/*! @brief blsh exit flag */
static uint8_t s_blsh_exit = 0;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

static void blsh_handle(uint8_t c);
static void line_execute(uint8_t *line);
static uint32_t command_parse(blsh_cmd_t **_cmd, uint8_t **_str);
static void command_execute(blsh_cmd_t *cmd, uint8_t *str);

/*******************************************************************************
 * Code
 ******************************************************************************/

void blsh_init(void)
{
    command_add(&exit_cmd);

    blsh_printf("\r\n **************************************** ");
    blsh_printf("\r\n ***       Welcome to blsh            *** ");
    blsh_printf("\r\n **************************************** ");
    blsh_printf("\r\n > "); /* Start a new line */
}

void blsh_run(void)
{
    uint8_t c;
    if (blsh_getchar(&c))
    {
        blsh_handle(c);
    }
}

uint8_t blsh_exit(void)
{
    return s_blsh_exit;
}

void command_add(blsh_cmd_t *cmd)
{
    blsh_cmd_t *index;

    if (!root_cmd)
    {
        root_cmd = cmd;
    }
    else
    {
        index = root_cmd;
        while (index->next)
            index = index->next;
        index->next = cmd;
    }
}

/*!
 * @brief handle input char
 *
 * @param c input char.
 */
static void blsh_handle(uint8_t c)
{
    uint8_t *line = s_inputBuffer[s_curBufIndex];

    if ((c == '\n') || (c == '\r')) /* Confirm the command */
    {
        /* Echo */
        blsh_putchar(c);

        while (*line && (*line == ' '))
            line++;
        if (*line)
        {
            microseconds_init();
            line_execute(line);
            microseconds_shutdown();

            s_curBufIndex = (s_curBufIndex + 1) % k_cmdHistoryDepth;
            s_curCmdIndex = 0;
            s_inputBuffer[s_curBufIndex][0] = 0;
        }
        /* Start a new line */
        if (!s_blsh_exit)
            blsh_printf("\r\n > ");
    }
    else if ((c == 0x08) || (c == 0x7f)) /* Backspace and delete */
    {
        if (s_curCmdIndex > 0)
        {
            line[--s_curCmdIndex] = 0;
            blsh_printf("\b \b");
        }
    }
    else if (c == 0x1b) /* Command turning */
    {
        uint8_t key_value[3] = { 0 };
        key_value[0] = c;
        key_value[1] = wait_uart_char_blocking();
        key_value[2] = wait_uart_char_blocking();

        if (key_value[2] == 0x41) /* Up */
        {
            uint8_t prevLine = (s_curBufIndex + k_cmdHistoryDepth - 1) % k_cmdHistoryDepth;

            if (s_inputBuffer[prevLine][0])
            {
                while (s_curCmdIndex-- > 0)
                    blsh_printf("\b \b");
                line = s_inputBuffer[prevLine];
                s_curCmdIndex = strlen((char *)line);
                s_curBufIndex = prevLine;
                blsh_printf("\r > %s", line);
            }
        }
        else if (key_value[2] == 0x42) /* Down */
        {
            uint8_t nextLine = (s_curBufIndex + 1) % k_cmdHistoryDepth;

            if (s_inputBuffer[nextLine][0])
            {
                while (s_curCmdIndex-- > 0)
                    blsh_printf("\b \b");
                line = s_inputBuffer[nextLine];
                s_curCmdIndex = strlen((char *)line);
                s_curBufIndex = nextLine;
                blsh_printf("\r > %s", line);
            }
        }
        else
        {
            blsh_printf("%s", key_value);
        }
    }
    else /* Input command */
    {
        if (s_curCmdIndex < k_cmdBufferSize)
        {
            /* Echo */
            blsh_putchar(c);
            line[s_curCmdIndex++] = c;
            line[s_curCmdIndex] = 0;
        }
    }
}

/*!
 * @brief process input line
 *
 * @param line input line.
 */
static void line_execute(uint8_t *line)
{
    uint8_t *str = line;
    blsh_cmd_t *cmd = root_cmd;
    uint32_t ret = 0;

    while (1)
    {
        ret = command_parse(&cmd, &str);

        if (ret == k_match)
        {
            if (cmd)
            {
                command_execute(cmd, str);
                break;
            }
        }
        else if (ret == k_ambig)
        {
            blsh_printf("\r\n Error: Ambiguity command: %s", str);
            break;
        }
        else if (ret == k_unmatch)
        {
            blsh_printf("\r\n Error: Invalid command: %s", str);
            break;
        }
        else
        {
            break;
        }
    }
}

/*!
 * @brief parse the command line
 *
 * @param _cmd command root.
 * @param _str input command.
 */
static uint32_t command_parse(blsh_cmd_t **_cmd, uint8_t **_str)
{
    uint8_t *str = *_str;
    /* uint32_t matched_len = 0; */
    blsh_cmd_t *cmd;
    /* blsh_cmd_t *matched_cmd = 0; */
    uint32_t ret = 0;

    /* Eliminate start blanks */
    while (*str == ' ')
        str++;
    if (!*str)
    {
        *_str = str;
        return k_nullMatch;
    }

    for (cmd = *_cmd; cmd; cmd = cmd->next)
    {
        ret = bl_strstart(cmd->name, str);

        if (ret == k_fullMatch)
        {
            while (*str && (*str != ' '))
                str++;
            while (*str == ' ')
                str++;
            *_str = str;
            *_cmd = cmd;
            return k_match;
        }
        else
        {
        }
    }

    return k_unmatch;
}

/*!
 * @brief execute the command
 *
 * @param cmd input command.
 * @param str input string.
 */
static void command_execute(blsh_cmd_t *cmd, uint8_t *str)
{
    uint8_t temp[k_cmdBufferSize] = { 0 };
    uint8_t *string = temp;
    uint8_t *argv[k_cmdMaxArgs];
    uint8_t argc = 0;

    memcpy(temp, str, strlen((char *)str));
    argv[argc++] = cmd->name;
    while (*string && (argc < k_cmdMaxArgs))
    {
        while (*string == ' ')
            string++;
        if (*string == 0)
        {
            break;
        }
        argv[argc++] = string;
        while (*string && (*string != ' '))
            string++;
        if (!*string)
        {
            break;
        }
        *string++ = 0;
    }

    if (cmd->function)
    {
        cmd->function(argc, argv);
    }
}

/*!
 * @brief process help command
 *
 * @param argc the count of arguments inputed to shell.
 * @param argv the value of arguments inputed to shell.
 */
static void help_func(uint8_t argc, uint8_t **argv)
{
    blsh_cmd_t *cmd = 0;

    blsh_printf("\r\n Command List: \r\n ");
    for (cmd = root_cmd; cmd; cmd = cmd->next)
    {
        blsh_printf("%s\r\n \t\t\t %s\r\n ", cmd->usage, cmd->help);
    }
}

/*!
 * @brief process exit command
 *
 * @param argc the count of arguments inputed to shell.
 * @param argv the value of arguments inputed to shell.
 */
static void exit_func(uint8_t argc, uint8_t **argv)
{
    s_blsh_exit = 1;
    blsh_printf("\r\n Bye \r\n");
}
