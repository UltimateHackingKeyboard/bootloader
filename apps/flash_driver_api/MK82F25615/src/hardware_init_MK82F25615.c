/*
 * Copyright (c) 2013-2016, Freescale Semiconductor, Inc.
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

#include "application_common.h"
#include "fsl_device_registers.h"
#include "lpuart/fsl_lpuart.h"
#include "target_config.h"
#include <assert.h>
#include <stdio.h>

////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////

void init_hardware(void)
{
    // Enable clocks to ports.
    SIM->SCGC5 |= (SIM_SCGC5_PORTA_MASK | SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTC_MASK | SIM_SCGC5_PORTD_MASK |
                   SIM_SCGC5_PORTE_MASK);

    // Select the IRC48M as LPUART0 clock source.
    SIM->SOPT2 = SIM_SOPT2_LPUARTSRC(1) | SIM_SOPT2_PLLFLLSEL(0x03) | SIM_SOPT2_TRACECLKSEL_MASK;

    SystemCoreClock = kDefaultClock;
}

uint32_t get_uart_clock(uint32_t instance)
{
    return kHIRC;
}

void init_term_uart(void)
{
    // Init pin mux for term uart.
    PORTC->PCR[15] = PORT_PCR_MUX(3); // UART4_TX is ALT3 for pin PTC15
    PORTC->PCR[14] = PORT_PCR_MUX(3); // UART4_RX is ALT3 for pin PTC14

    // Ungate the LPUART clock.
    SIM->SCGC2 |= SIM_SCGC2_LPUART4_MASK;

    lpuart_config_t lpuartCfg;
    LPUART_GetDefaultConfig(&lpuartCfg);

    lpuartCfg.baudRate_Bps = TERMINAL_BAUD;
    lpuartCfg.enableTx = true;
    lpuartCfg.parityMode = kLPUART_ParityDisabled;
    lpuartCfg.stopBitCount = kLPUART_OneStopBit;

    LPUART_Init(LPUART4, &lpuartCfg, get_uart_clock(0));
}

int fputc(int ch, FILE *fp)
{
    LPUART_WriteBlocking(LPUART4, (const uint8_t *)&ch, 1);

    return ch;
}

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
