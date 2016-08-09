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

void init_hardware(void)
{
    // Enable clocks to ports.
    SIM->SCGC5 |= (SIM_SCGC5_PORTA_MASK | SIM_SCGC5_PORTB_MASK);

    // Select the MCGIRCLK as UART0 clock source.
    SIM->SOPT2 |= SIM_SOPT2_LPUART0SRC_MASK;

    // Update SystemCoreClock. Out of reset, the LIRC is enabled. FOPT bits set the OUTDIV1 value.
    uint32_t lirc = (((MCG->C2 & MCG_C2_IRCS_MASK) >> MCG_C2_IRCS_SHIFT) == 1) ? kLIRC8M : kLIRC2M;
    SystemCoreClock = lirc / (((SIM->CLKDIV1 & SIM_CLKDIV1_OUTDIV1_MASK) >> SIM_CLKDIV1_OUTDIV1_SHIFT) + 1);
}

uint32_t get_uart_clock(uint32_t instance)
{
    uint32_t lirc = (((MCG->C2 & MCG_C2_IRCS_MASK) >> MCG_C2_IRCS_SHIFT) == 1) ? kLIRC8M : kLIRC2M;
    return lirc >> ((MCG->SC & MCG_SC_FCRDIV_MASK) >> MCG_SC_FCRDIV_SHIFT);
}

void init_term_uart(void)
{
    // Init pin mux for term uart.
    PORTA->PCR[2] = PORT_PCR_MUX(2); // UART0_TX is ALT2 for pin PTA2
    PORTA->PCR[1] = PORT_PCR_MUX(2); // UART0_RX is ALT2 for pin PTA1

    // Ungate the LPUART clock.
    SIM->SCGC5 |= SIM_SCGC5_LPUART0_MASK;

    lpuart_config_t lpuartCfg;
    LPUART_GetDefaultConfig(&lpuartCfg);

    lpuartCfg.baudRate_Bps = TERMINAL_BAUD;
    lpuartCfg.enableTx = true;
    lpuartCfg.parityMode = kLPUART_ParityDisabled;
    lpuartCfg.stopBitCount = kLPUART_OneStopBit;

    LPUART_Init(LPUART0, &lpuartCfg, get_uart_clock(0));
}

int fputc(int ch, FILE *fp)
{
    LPUART_WriteBlocking(LPUART0, (const uint8_t *)&ch, 1);

    return ch;
}

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
