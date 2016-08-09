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
#include "port/fsl_port.h"
#include "pin_mux.h"

/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * @brief Initialize all pins used in this example
 *
 * @param disablePortClockAfterInit disable port clock after pin
 * initialization or not.
 */
void BOARD_InitPins(void)
{
    port_pin_config_t pinConfig;
    pinConfig.pullSelect = kPORT_PullUp;
    pinConfig.openDrainEnable = kPORT_OpenDrainEnable;

    /* Ungate the port clock */
    SIM->SCGC5 |= (SIM_SCGC5_PORTA_MASK | SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTC_MASK | SIM_SCGC5_PORTD_MASK |
                   SIM_SCGC5_PORTE_MASK);

    /* Initialize UART2(OpenSDA) pins below */
    PORT_SetPinMux(PORTE, 16u, kPORT_MuxAlt3); /* Affects PORTE_PCR16 register */
    PORT_SetPinMux(PORTE, 17u, kPORT_MuxAlt3); /* Affects PORTE_PCR17 register */

    /* Enable pins for UART4 on PTE24 - PTE25. */
    PORT_SetPinMux(PORTE, 25u, kPORT_MuxAlt3); /* UART4_RX is ALT3 for pin PTE25 */
    PORT_SetPinMux(PORTE, 24u, kPORT_MuxAlt3); /* UART4_TX is ALT3 for pin PTE24 */

    /* Enable pins for I2C0 on PTE18 - PTE19. */
    PORT_SetPinConfig(PORTE, 18u, &pinConfig); /* I2C0_SCL set for open drain */
    PORT_SetPinConfig(PORTE, 19u, &pinConfig); /* I2C0_SDA set for open drain */
    PORT_SetPinMux(PORTE, 18u, kPORT_MuxAlt4); /* I2C0_SCL is ALT4 for pin PTE18 */
    PORT_SetPinMux(PORTE, 19u, kPORT_MuxAlt4); /* I2C0_SDA is ALT4 for pin PTE19 */

    /* Enable pins for SPI0 on PTD0 - PTD3. */
    PORT_SetPinMux(PORTD, 11u, kPORT_MuxAlt2); /* SPI0_PCS0 is ALT2 for pin PTD11 */
    PORT_SetPinMux(PORTD, 12u, kPORT_MuxAlt2); /* SPI0_SCK  is ALT2 for pin PTD12 */
    PORT_SetPinMux(PORTD, 13u, kPORT_MuxAlt2); /* SPI0_SOUT is ALT2 for pin PTD13 */
    PORT_SetPinMux(PORTD, 14u, kPORT_MuxAlt2); /* SPI0_SIN  is ALT2 for pin PTD14 */

    /* LED PTA28 */
    PORT_SetPinMux(PORTA, 28u, kPORT_MuxAsGpio);
    PORT_SetPinMux(PORTA, 29u, kPORT_MuxAsGpio);
    PORT_SetPinMux(PORTB, 4u, kPORT_MuxAsGpio);
    PORT_SetPinMux(PORTB, 5u, kPORT_MuxAsGpio);

    /* SW2 PTA4 */
    PORT_SetPinMux(PORTA, 4u, kPORT_MuxAsGpio);
    /* SW3 PTA10 */
    PORT_SetPinMux(PORTA, 10u, kPORT_MuxAsGpio);

    /* Enable pins for FLEXCAN0 on PTA30 - PTA31. */
    PORT_SetPinMux(PORTA, 30u, kPORT_MuxAlt2); /* FLEXCAN0_TX is ALT2 for pin PTA30 */
    PORT_SetPinMux(PORTA, 31u, kPORT_MuxAlt2); /* FLEXCAN0_RX is ALT2 for pin PTA31 */
}