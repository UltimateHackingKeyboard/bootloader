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

#include <stdint.h>
#include "port/fsl_port.h"
#include "board.h"
/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
/* Initialize Switch. */
void BOARD_InitSwitch(void)
{
    gpio_pin_config_t switch_config = { kGPIO_DigitalInput, 0 };

    GPIO_PinInit(BOARD_SW2_GPIO, BOARD_SW2_GPIO_PIN, &switch_config);
    GPIO_PinInit(BOARD_SW3_GPIO, BOARD_SW3_GPIO_PIN, &switch_config);
}

/* Read Switch value. */
bool BOARD_ReadSwitch(uint32_t switch_num)
{
    if (switch_num == kSwitch2)
    {
        return !(GPIO_ReadPinInput(BOARD_SW2_GPIO, BOARD_SW2_GPIO_PIN));
    }
    else if (switch_num == kSwitch3)
    {
        return !(GPIO_ReadPinInput(BOARD_SW3_GPIO, BOARD_SW3_GPIO_PIN));
    }
    else
    {
        return false;
    }
}

/* Initialize led. */
void BOARD_InitLED(void)
{
    gpio_pin_config_t LED_config = { kGPIO_DigitalOutput, 1 };
    GPIO_PinInit(BOARD_LED_GREEN_GPIO_PORT, BOARD_LED_GREEN_GPIO_PIN, &LED_config);
    GPIO_PinInit(BOARD_LED_RED_GPIO_PORT, BOARD_LED_RED_GPIO_PIN, &LED_config);
    GPIO_PinInit(BOARD_LED_BLUE_GPIO_PORT, BOARD_LED_BLUE_GPIO_PIN, &LED_config);
    GPIO_PinInit(BOARD_LED_YELLOW_GPIO_PORT, BOARD_LED_YELLOW_GPIO_PIN, &LED_config);
}
