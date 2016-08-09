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
#include "led_bsp.h"

//! @brief Intialize necessary IPs.
void hardware_init(void);
//! @brief Toggle LEDs according to specified parameter leds.
void led_toggle(uint32_t leds);

int main(void)
{
    hardware_init();
    milliseconds_delay_init();

    uint32_t led_idx = LED0;
    while (1)
    {
        led_toggle(led_idx);
        milliseconds_delay(500);
        led_toggle(led_idx);

        led_idx <<= 1;
        if (led_idx > MAX_LED_IDX)
        {
            led_idx = LED0;
        }
    }
}

void hardware_init(void)
{
#if defined(SIM_SCGC5_PORTA_MASK)
    SIM->SCGC5 |= (SIM_SCGC5_PORTA_MASK | SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTC_MASK | SIM_SCGC5_PORTD_MASK |
                   SIM_SCGC5_PORTE_MASK);
#else
    SIM->SCGC5 |=
        (SIM_SCGC5_PTA_MASK | SIM_SCGC5_PTB_MASK | SIM_SCGC5_PTC_MASK | SIM_SCGC5_PTD_MASK | SIM_SCGC5_PTE_MASK);
#endif

    // Enable the LED pins GPIO
    LED0_PORT->PCR[LED0_OFFSET] = PORT_PCR_MUX(1);
    LED1_PORT->PCR[LED1_OFFSET] = PORT_PCR_MUX(1);
#if MAX_LED_IDX == LED2
    LED2_PORT->PCR[LED2_OFFSET] = PORT_PCR_MUX(1);
#endif // #if MAX_LED_IDX == LED2

    // Configure port to output mode
    LED0_GPIO->PDDR |= (1 << LED0_OFFSET);
    LED1_GPIO->PDDR |= (1 << LED1_OFFSET);
#if MAX_LED_IDX == LED2
    LED2_GPIO->PDDR |= (1 << LED2_OFFSET);
#endif // #if MAX_LED_IDX == LED2

// If led will be turned on with low level, need to turn all of them off at startup.
#if LED_POLARITY == LED_ON_LOW_LEVEL
    LED0_GPIO->PTOR |= (1 << LED0_OFFSET);
    LED1_GPIO->PTOR |= (1 << LED1_OFFSET);
#if MAX_LED_IDX == LED2
    LED2_GPIO->PTOR |= (1 << LED2_OFFSET);
#endif // #if MAX_LED_IDX == LED2
#endif // #if LED_POLARITY == LED_ON_LOW_LEVEL
}

void led_toggle(uint32_t leds)
{
    if (leds & LED0)
    {
        LED0_GPIO->PTOR |= (1 << LED0_OFFSET);
    }
    if (leds & LED1)
    {
        LED1_GPIO->PTOR |= (1 << LED1_OFFSET);
    }
#if MAX_LED_IDX == LED2
    if (leds & LED2)
    {
        LED2_GPIO->PTOR |= (1 << LED2_OFFSET);
    }
#endif // #if MAX_LED_IDX == LED2
}
