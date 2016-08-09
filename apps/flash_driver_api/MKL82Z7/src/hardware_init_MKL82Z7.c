/*
 * Copyright (c) 2013-2015, Freescale Semiconductor, Inc.
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

#if defined(FRDM_KL82Z)
#define TERM_UART LPUART0
#elif defined(TWR_KL82Z)
#define TERM_UART LPUART1
#endif

void init_hardware(void)
{
    // Enable clocks to ports.
    SIM->SCGC5 |=
        (SIM_SCGC5_PTA_MASK | SIM_SCGC5_PTB_MASK | SIM_SCGC5_PTC_MASK | SIM_SCGC5_PTD_MASK | SIM_SCGC5_PTE_MASK);

    // Select the IRC48M as LPUART0 clock source.
    SIM->SOPT2 = SIM_SOPT2_LPUARTSRC(1) | SIM_SOPT2_PLLFLLSEL(0x03);

    SystemCoreClock = kDefaultClock;
}

uint32_t get_uart_clock(uint32_t instance)
{
    return kHIRC;
}

void init_term_uart(void)
{
#if defined(FRDM_KL82Z)
    // Init pin mux for term uart.
    PORTB->PCR[17] = PORT_PCR_MUX(3); // UART0_TX is ALT3 for pin PTB17
    PORTB->PCR[16] = PORT_PCR_MUX(3); // UART0_RX is ALT3 for pin PTB16
    // Ungate the LPUART clock.
    SIM->SCGC5 |= SIM_SCGC5_LPUART0_MASK;
#elif defined(TWR_KL82Z)
    // Init pin mux for term uart.
    PORTC->PCR[4] = PORT_PCR_MUX(3); // UART1_TX is ALT3 for pin PTC4
    PORTC->PCR[3] = PORT_PCR_MUX(3); // UART1_RX is ALT3 for pin PTC3
    SIM->SCGC5 |= SIM_SCGC5_LPUART1_MASK;
#endif

    lpuart_config_t lpuartCfg;
    LPUART_GetDefaultConfig(&lpuartCfg);

    lpuartCfg.baudRate_Bps = TERMINAL_BAUD;
    lpuartCfg.enableTx = true;
    lpuartCfg.parityMode = kLPUART_ParityDisabled;
    lpuartCfg.stopBitCount = kLPUART_OneStopBit;

    LPUART_Init(TERM_UART, &lpuartCfg, get_uart_clock(0));
}

int fputc(int ch, FILE *fp)
{
    LPUART_WriteBlocking(TERM_UART, (const uint8_t *)&ch, 1);

    return ch;
}

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
