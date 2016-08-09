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

#include "host_hardware.h"
#include "blsh/host_blsh_cmd.h"
#include "blsh/host_command.h"
#include "microseconds/microseconds.h"
#include "board.h"
#include "gpio/fsl_gpio.h"
#include "executable_image.h"

enum
{
    kSwitchStatus_Idle = 0,
    kSwitchStatus_Lock = 1,
    kSwitchStatus_Confirm = 2
};

static uint32_t s_switch2_press = 0;
static uint32_t s_switch3_press = kSPI_mode;

void embedded_host_blsh_init(void);
void flash_image_status_callback(recordStatus_t status);

/*!
 * @brief embedded host main function.
 */
#if defined(__CC_ARM) || defined(__GNUC__)
int main(void)
#else
void main(void)
#endif
{
    hardware_init();

    host_blsh_cmd_init();
    embedded_host_blsh_init();

    while (!blsh_exit())
    {
        /* Wait blsh command */
        blsh_run();

        /* Fisrt press to lock the selection */
        if (s_switch2_press == kSwitchStatus_Lock)
        {
            LED_YELLOW_ON;
        }
        /* Second press to ensure the selection */
        else if (s_switch2_press == kSwitchStatus_Confirm)
        {
            microseconds_init();
            /* Enter spi transfer mode */
            if (s_switch3_press == kSPI_mode)
            {
                configure_transfer_bus(kSPI_mode, 100);
            }
            /* Enter i2c transfer mode */
            else if (s_switch3_press == kI2C_mode)
            {
                configure_transfer_bus(kI2C_mode, 100);
            }
            /* Enter uart transfer mode */
            else if (s_switch3_press == kUART_mode)
            {
                configure_transfer_bus(kUART_mode, 57600);
            }
            else if (s_switch3_press == kCAN_mode)
            {
                configure_transfer_bus(kCAN_mode, 125);
            }

            flash_image(flash_image_status_callback);
            microseconds_shutdown();

            LED_YELLOW_OFF;
            s_switch2_press = kSwitchStatus_Idle;
        }
    }

#if (defined(__CC_ARM) || defined(__GNUC__))
    return 1;
#endif
}

void flash_image_status_callback(recordStatus_t status)
{
    if (status != kRecordStatus_Success)
    {
        LED_RED_ON;
        blsh_printf("\r\n Flash image fail! \r\n > ");
    }
    else
    {
        LED_YELLOW_OFF;
        LED_GREEN_OFF;
        LED_BLUE_OFF;
        LED_RED_OFF;
        s_switch3_press = kSPI_mode;

        blsh_printf("\r\n Flash image success. \r\n > ");
    }
}

void embedded_host_blsh_init(void)
{
    command_add(&flash_image_cmd);
    command_add(&write_memory_cmd);
    command_add(&read_memory_cmd);
    command_add(&fill_memory_cmd);
    command_add(&flash_security_disable_cmd);
    command_add(&flash_erase_all_unsecure_cmd);
    command_add(&flash_erase_all_cmd);
    command_add(&flash_erase_region_cmd);
    command_add(&execute_cmd);
    command_add(&call_cmd);
    command_add(&flash_program_once_cmd);
    command_add(&flash_read_once_cmd);
    command_add(&flash_read_resource_cmd);
}

/*!
 * @brief Switch interrupt irq hander.
 */
void BOARD_SW_IRQ_HANDLER(void)
{
    /* Clear external interrupt flag. */
    uint32_t int_flags = GPIO_GetPinsInterruptFlags(BOARD_SW3_GPIO);
    GPIO_ClearPinsInterruptFlags(BOARD_SW3_GPIO, 1U << BOARD_SW3_GPIO_PIN);
    GPIO_ClearPinsInterruptFlags(BOARD_SW2_GPIO, 1U << BOARD_SW2_GPIO_PIN);

    if (int_flags & BOARD_SW2_MASK)
    {
        s_switch2_press++;

        if (s_switch2_press > kSwitchStatus_Confirm)
        {
            s_switch2_press = kSwitchStatus_Idle;
        }
    }
    else if (int_flags & BOARD_SW3_MASK)
    {
        if (!s_switch2_press)
        {
            if (++s_switch3_press > kCAN_mode)
            {
                s_switch3_press = kSPI_mode;
            }

            if (s_switch3_press == kSPI_mode)
            {
                LED_GREEN_OFF;
                LED_BLUE_OFF;
            }
            if (s_switch3_press == kI2C_mode)
            {
                LED_GREEN_ON;
                LED_BLUE_OFF;
            }
            else if (s_switch3_press == kUART_mode)
            {
                LED_GREEN_OFF;
                LED_BLUE_ON;
            }
            else if (s_switch3_press == kCAN_mode)
            {
                LED_GREEN_ON;
                LED_BLUE_ON;
            }
        }
        else
        {
            s_switch2_press = kSwitchStatus_Idle;
            LED_YELLOW_OFF;
        }
    }
}
