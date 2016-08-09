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

#include "fsl_device_registers.h"
#include "milliseconds_delay.h"

#define LED1_OFFSET 3
#define LED2_OFFSET 9
#define LED3_OFFSET 10
#define LED4_OFFSET 11

#define LED1 (1) // green
#define LED2 (2) // yellow
#define LED3 (4) // orange
#define LED4 (8) // blue

#define LED1_GPIO (GPIOB)
#define LED2_GPIO (GPIOB)
#define LED3_GPIO (GPIOB)
#define LED4_GPIO (GPIOB)

#define LED1_PORT (PORTB)
#define LED2_PORT (PORTB)
#define LED3_PORT (PORTB)
#define LED4_PORT (PORTB)

static void init_hardware(void)
{
    SIM->SCGC5 |= (SIM_SCGC5_PORTA_MASK | SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTC_MASK | SIM_SCGC5_PORTD_MASK |
                   SIM_SCGC5_PORTE_MASK);

    // Enable the LED pins GPIO
    LED1_PORT->PCR[LED1_OFFSET] = PORT_PCR_MUX(1);
    LED2_PORT->PCR[LED2_OFFSET] = PORT_PCR_MUX(1);
    LED3_PORT->PCR[LED3_OFFSET] = PORT_PCR_MUX(1);
    LED4_PORT->PCR[LED4_OFFSET] = PORT_PCR_MUX(1);

    // Set ports to outputs
    PTB->PDDR |= (1 << LED1_OFFSET) | (1 << LED2_OFFSET) | (1 << LED3_OFFSET) | (1 << LED4_OFFSET);
}

static void led_toggle(uint32_t leds)
{
    if (leds & LED1)
    {
        LED1_GPIO->PTOR |= (1 << LED1_OFFSET);
    }
    if (leds & LED2)
    {
        LED2_GPIO->PTOR |= (1 << LED2_OFFSET);
    }
    if (leds & LED3)
    {
        LED3_GPIO->PTOR |= (1 << LED3_OFFSET);
    }
    if (leds & LED4)
    {
        LED4_GPIO->PTOR |= (1 << LED4_OFFSET);
    }
}

int main(void)
{
    init_hardware();
    milliseconds_delay_init();
    uint32_t leds = LED1;
    while (1)
    {
        led_toggle(leds);
        milliseconds_delay(500);
        led_toggle(leds);

        leds <<= 1;
        if (leds > LED4)
        {
            leds = LED1;
        }
    }
}
