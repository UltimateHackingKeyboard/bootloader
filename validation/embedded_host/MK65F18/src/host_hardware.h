/*
 * Copyright (c) 2013 - 2014, Freescale Semiconductor, Inc.
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
#if !defined(__HOST_HARDWARE_H__)
#define __HOST_HARDWARE_H__

#include "bootloader_common.h"
#include "microseconds/microseconds.h"
#include "dspi/fsl_dspi.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#define UART_INSTANCE 4
#define SPI_INSTANCE 2
#define I2C_INSTANCE 0
#define FLEXCAN_INSTANCE 0

/*! @brief uart baud rate value limit */
enum _uart_baud_value
{
    kUART_MIN_BAUD = 19200,
    kUART_MAX_BAUD = 230400,
    kUART_DEFAULT_BAUD = 57600
};

/*! @brief FelxCAN frequency */
enum _flexcan_freq_value
{
    kFLEXCAN_125K = 125,
    kFLEXCAN_250K = 250,
    kFLEXCAN_500K = 500,
    kFLEXCAN_750K = 750,
    kFLEXCAN_1000K = 1000,
};

/*******************************************************************************
 * API
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*! @brief initialize all hardware */
void hardware_init(void);

/*! @brief receiving host char command process */
bool wait_uart_char(uint8_t *data);
uint8_t wait_uart_char_blocking(void);

/*! @brief spi config speed process */
void configure_spi_speed(uint32_t speedkhz);

/*! @brief spi receiving data process */
status_t receive_spi_data(uint8_t *dest, uint32_t readLength);

/*! @brief spi send data process */
status_t send_spi_data(uint8_t *src, uint32_t writeLength);

/*! @brief i2c config speed process */
void configure_i2c_speed(uint32_t speedkhz);

/*! @brief i2c sending data process */
status_t send_i2c_data(uint8_t *src, uint32_t writeLength);

/*! @brief i2c receiving data process */
status_t receive_i2c_data(uint8_t *dest, uint32_t readLength);

/*! @brief uart config speed process */
void configure_uart_speed(uint32_t baud);

/*! @brief uart send data process */
status_t send_uart_data(uint8_t *src, uint32_t writeLength);

/*! @brief uart receiving data process */
status_t receive_uart_data(uint8_t *dest, uint32_t readLength);

/*! @brief flexCAN config speed process */
void configure_can_speed(uint32_t speed);

/*! @brief flexCAN sending data process */
status_t send_can_data(uint8_t *src, uint32_t writeLength);

/*! @brief flexCAN receiving data process */
status_t receive_can_data(uint8_t *dest, uint32_t readLength);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* __HOST_HARDWARE_H__ */
