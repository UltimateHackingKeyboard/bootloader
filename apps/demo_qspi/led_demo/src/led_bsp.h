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

#ifndef __LED_BSP_H__
#define __LED_BSP_H__

#include "fsl_device_registers.h"

#define LED_ON_LOW_LEVEL 1
#define LED_ON_HIGH_LEVEL 2

#define LED0 (1)
#define LED1 (2)
#define LED2 (4)

#if defined(TWR_K80F150M)
#define MAX_LED_IDX (LED1)
#define LED0_OFFSET 14
#define LED1_OFFSET 15
#define LED0_PORT (PORTD)
#define LED0_GPIO (GPIOD)
#define LED1_PORT (PORTD)
#define LED1_GPIO (GPIOD)
#define LED_POLARITY LED_ON_HIGH_LEVEL
#elif defined(FRDM_K82F)
#define MAX_LED_IDX (LED2)
#define LED0_OFFSET 8
#define LED1_OFFSET 9
#define LED2_OFFSET 10
#define LED0_PORT (PORTC)
#define LED0_GPIO (GPIOC)
#define LED1_PORT (PORTC)
#define LED1_GPIO (GPIOC)
#define LED2_PORT (PORTC)
#define LED2_GPIO (GPIOC)
#define LED_POLARITY LED_ON_LOW_LEVEL
#elif defined(TWR_POS_K81)
#define MAX_LED_IDX (LED2)
#define LED0_OFFSET 7
#define LED1_OFFSET 8
#define LED2_OFFSET 13
#define LED0_PORT (PORTC)
#define LED0_GPIO (GPIOC)
#define LED1_PORT (PORTC)
#define LED1_GPIO (GPIOC)
#define LED2_PORT (PORTC)
#define LED2_GPIO (GPIOC)
#define LED_POLARITY LED_ON_LOW_LEVEL
#elif defined(TWR_KL8272M)
#define MAX_LED_IDX (LED1)
#define LED0_OFFSET 14
#define LED1_OFFSET 15
#define LED0_PORT (PORTD)
#define LED0_GPIO (GPIOD)
#define LED1_PORT (PORTD)
#define LED1_GPIO (GPIOD)
#define LED_POLARITY LED_ON_HIGH_LEVEL
#elif defined(FRDM_KL82Z)
#define MAX_LED_IDX (LED2)
#define LED0_OFFSET 0
#define LED1_OFFSET 1
#define LED2_OFFSET 2
#define LED0_PORT (PORTC)
#define LED0_GPIO (GPIOC)
#define LED1_PORT (PORTC)
#define LED1_GPIO (GPIOC)
#define LED2_PORT (PORTC)
#define LED2_GPIO (GPIOC)
#define LED_POLARITY LED_ON_LOW_LEVEL
#elif defined(TWR_POS_KL81)
#define MAX_LED_IDX (LED2)
#define LED0_OFFSET 7
#define LED1_OFFSET 8
#define LED2_OFFSET 13
#define LED0_PORT (PORTC)
#define LED0_GPIO (GPIOC)
#define LED1_PORT (PORTC)
#define LED1_GPIO (GPIOC)
#define LED2_PORT (PORTC)
#define LED2_GPIO (GPIOC)
#define LED_POLARITY LED_ON_LOW_LEVEL
#else
#error This board is not supported!
#endif

#endif
