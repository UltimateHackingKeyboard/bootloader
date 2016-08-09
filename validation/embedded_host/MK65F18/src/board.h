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

#ifndef _BOARD_H_
#define _BOARD_H_

#include "gpio/fsl_gpio.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief The board name */
#define BOARD_NAME "TWR-K65F180M"

/*! @brief The UART to use for debug messages. */
#define BOARD_USE_UART
#define BOARD_DEBUG_UART_TYPE DEBUG_CONSOLE_DEVICE_TYPE_UART
#define BOARD_DEBUG_UART_BASEADDR (uint32_t) UART2
#define BOARD_DEBUG_UART_CLKSRC BUS_CLK

#ifndef BOARD_DEBUG_UART_BAUDRATE
#define BOARD_DEBUG_UART_BAUDRATE 115200
#endif /* BOARD_DEBUG_UART_BAUDRATE */

/*! @brief The CAN instance used for board */
#define BOARD_CAN_BASEADDR CAN0

/*! @brief The i2c instance used for i2c connection by default */
#define BOARD_I2C_BASEADDR I2C0

/*! @brief The Flextimer instance/channel used for board */
#define BOARD_FTM_BASEADDR FTM0
#define BOARD_FTM_CHANNEL 2

/*! @brief The TPM instance/channel used for board */
#define BOARD_TPM_BASEADDR TPM2
#define BOARD_TPM_CHANNEL 0

/*! @brief The Enet instance used for board. */
#define BOARD_ENET_BASEADDR ENET

/*! @brief The FlexBus instance used for board.*/
#define BOARD_FLEXBUS_BASEADDR FB

#define BOARD_TSI_ELECTRODE_CNT 2

/*! @brief Indexes of the TSI channels for on board electrodes */
#define BOARD_TSI_ELECTRODE_1 11
#define BOARD_TSI_ELECTRODE_2 12

/*! @brief The SDHC instance/channel used for board */
#define BOARD_SDHC_BASEADDR SDHC
#define BOARD_SDHC_CD_GPIO_IRQ_HANDLER PORTA_IRQHandler

/*! @brief The CMP instance/channel used for board. */
#define BOARD_CMP_BASEADDR CMP2
#define BOARD_CMP_CHANNEL 2

/*! @brief The i2c instance used for sai demo */
#define BOARD_SAI_DEMO_I2C_BASEADDR I2C0

/*! @brief The rtc instance used for rtc_func */
#define BOARD_RTC_FUNC_BASEADDR RTC

/*! @brief If connected the TWR_MEM, this is spi sd card */
#define BOARD_SDCARD_CARD_DETECTION_GPIO_PORT GPIOD
#define SDCARD_CARD_DETECTION_GPIO_PIN 15
#define SDCARD_CARD_WRITE_PROTECTION_GPIO_PORT GPIOC
#define SDCARD_CARD_WRITE_PROTECTION_GPIO_PIN 13
#define SDCARD_SPI_HW_BASEADDR SPI1
#define SDCARD_CARD_INSERTED 0

/*! @brief Define the port interrupt number for the board switches */
enum
{
    kSwitch1,
    kSwitch2,
    kSwitch3,
};
#define BOARD_SW2_GPIO GPIOA
#define BOARD_SW2_PORT PORTA
#define BOARD_SW2_GPIO_PIN 4
#define BOARD_SW2_IRQ PORTA_IRQn
#define BOARD_SW2_IRQ_HANDLER PORTA_IRQHandler
#define BOARD_SW2_NAME "SW2"
#define BOARD_SW2_MASK (1u << BOARD_SW2_GPIO_PIN)

#define BOARD_SW3_GPIO GPIOA
#define BOARD_SW3_PORT PORTA
#define BOARD_SW3_GPIO_PIN 10
#define BOARD_SW3_IRQ PORTA_IRQn
#define BOARD_SW3_IRQ_HANDLER PORTA_IRQHandler
#define BOARD_SW3_NAME "SW3"
#define BOARD_SW3_MASK (1u << BOARD_SW3_GPIO_PIN)

#define BOARD_SW_IRQ_HANDLER PORTA_IRQHandler

#define BOARD_LED_RED_GPIO_PORT GPIOB
#define BOARD_LED_RED_GPIO_PIN 5
#define BOARD_LED_RED_MASK (1u << BOARD_LED_RED_GPIO_PIN)
#define BOARD_LED_GREEN_GPIO_PORT GPIOA
#define BOARD_LED_GREEN_GPIO_PIN 28
#define BOARD_LED_GREEN_MASK (1u << BOARD_LED_GREEN_GPIO_PIN)
#define BOARD_LED_BLUE_GPIO_PORT GPIOA
#define BOARD_LED_BLUE_GPIO_PIN 29
#define BOARD_LED_BLUE_MASK (1u << BOARD_LED_BLUE_GPIO_PIN)
#define BOARD_LED_YELLOW_GPIO_PORT GPIOB
#define BOARD_LED_YELLOW_GPIO_PIN 4
#define BOARD_LED_YELLOW_MASK (1u << BOARD_LED_YELLOW_GPIO_PIN)

#define LED_RED_ON GPIO_ClearPinsOutput(BOARD_LED_RED_GPIO_PORT, BOARD_LED_RED_MASK)
#define LED_RED_OFF GPIO_SetPinsOutput(BOARD_LED_RED_GPIO_PORT, BOARD_LED_RED_MASK)
#define LED_GREEN_ON GPIO_ClearPinsOutput(BOARD_LED_GREEN_GPIO_PORT, BOARD_LED_GREEN_MASK)
#define LED_GREEN_OFF GPIO_SetPinsOutput(BOARD_LED_GREEN_GPIO_PORT, BOARD_LED_GREEN_MASK)
#define LED_BLUE_ON GPIO_ClearPinsOutput(BOARD_LED_BLUE_GPIO_PORT, BOARD_LED_BLUE_MASK)
#define LED_BLUE_OFF GPIO_SetPinsOutput(BOARD_LED_BLUE_GPIO_PORT, BOARD_LED_BLUE_MASK)
#define LED_YELLOW_ON GPIO_ClearPinsOutput(BOARD_LED_YELLOW_GPIO_PORT, BOARD_LED_YELLOW_MASK)
#define LED_YELLOW_OFF GPIO_SetPinsOutput(BOARD_LED_YELLOW_GPIO_PORT, BOARD_LED_YELLOW_MASK)
/*! @brief Define the port interrupt number for the usb id gpio pin */
#define BOARD_ID_GPIO GPIOE
#define BOARD_ID_PORT PORTE
#define BOARD_ID_GPIO_PIN 10U
#define BOARD_ID_IRQ PORTE_IRQn

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*******************************************************************************
 * API
 ******************************************************************************/
extern void BOARD_InitHardware(void);
void BOARD_InitSwitch(void);
void BOARD_InitLED(void);
bool BOARD_ReadSwitch(uint32_t switch_num);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* _BOARD_H_ */
