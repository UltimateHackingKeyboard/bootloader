/*
 * Copyright (c) 2013, Freescale Semiconductor, Inc.
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

#define LED0_OFFSET 5
#define LED1_OFFSET 16
#define LED2_OFFSET 17

#define DELAY_1MS (1000)

static void init_hardware(void)
{
    SIM->SCGC5 |= (SIM_SCGC5_PORTA_MASK | SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTC_MASK | SIM_SCGC5_PORTD_MASK |
                   SIM_SCGC5_PORTE_MASK);

    SIM->SOPT2 |= SIM_SOPT2_PLLFLLSEL_MASK; // set PLLFLLSEL to select the PLL for this clock source

#if defined(TOWER)

    PORTA->PCR[5] = PORT_PCR_MUX(1);
    PORTA->PCR[16] = PORT_PCR_MUX(1);
    PORTA->PCR[17] = PORT_PCR_MUX(1);

    FPTA->PDDR |= (1 << LED0_OFFSET) | (1 << LED1_OFFSET) | (1 << LED2_OFFSET);

#elif defined(FREEDOM)
    PORTB->PCR[18] = PORT_PCR_MUX(1); // Set Pin B18 to GPIO function
    PORTB->PCR[19] = PORT_PCR_MUX(1); // Set Pin B19 to GPIO function
    PORTD->PCR[1] = PORT_PCR_MUX(1);  // Set Pin D1 to GPIO function
    FPTB->PDDR |= (1 << 18);          // Red LED, Negative Logic (0=on, 1=off)
    FPTB->PDDR |= (1 << 19);          // Green LED, Negative Logic (0=on, 1=off)
    FPTD->PDDR |= (1 << 1);           // Blue LED, Negative Logic (0=on, 1=off)

#endif // FREEDOM
}

#define LED0 1
#define LED1 2
#define LED2 4

#if defined(TOWER)

static void led_toggle(uint32_t leds)
{
    if (leds & LED0)
    {
        FPTA->PTOR |= (1 << LED0_OFFSET);
    }
    if (leds & LED1)
    {
        FPTA->PTOR |= (1 << LED1_OFFSET);
    }
    if (leds & LED2)
    {
        FPTA->PTOR |= (1 << LED2_OFFSET);
    }
}

#elif defined(FREEDOM)

// RGB-LED Control: 1=on, 0=off, for each of the 3 colors
void RGB(int32_t Red, int32_t Green, int32_t Blue)
{
    if (Red == 1)
        FPTB->PCOR |= (1 << 18);
    else
        FPTB->PSOR |= (1 << 18);

    if (Green == 1)
        FPTB->PCOR |= (1 << 19);
    else
        FPTB->PSOR |= (1 << 19);

    if (Blue == 1)
        FPTD->PCOR |= (1 << 1);
    else
        FPTD->PSOR |= (1 << 1);
}

#endif // FREEDOM

void delay(void)
{
    volatile uint32_t delayTicks = 2000000;

    while (delayTicks--)
    {
        __ASM("nop");
    }
}

int main(void)
{
    init_hardware();
    // Note: for ROM development, use this version of delay function,
    // Which is in order to test if the VTCOR is correct.
    milliseconds_delay_init();

#if defined(TOWER)

    uint32_t leds = LED0;
    while (1)
    {
        led_toggle(leds);
        milliseconds_delay(DELAY_1MS);
        led_toggle(leds);

        leds <<= 1;
        if (leds > LED2)
        {
            leds = LED0;
        }
    }

#elif defined(FREEDOM)

    RGB(0, 0, 0); // Start with all LEDs off

    while (1)
    {
        RGB(1, 0, 0);
        milliseconds_delay(DELAY_1MS);
        RGB(0, 1, 0);
        milliseconds_delay(DELAY_1MS);
        RGB(0, 0, 1);
        milliseconds_delay(DELAY_1MS);
    }

#endif // FREEDOM
}
