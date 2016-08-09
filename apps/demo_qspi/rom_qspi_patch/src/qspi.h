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

#ifndef __QSPI_H__
#define __QSPI_H__

#include <stdint.h>

////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////
#define QSPI_LUT_MAX_ENTRIES 64
#define QSPI_PRE_CMD_CNT 4 //!< the max number of pre commands
#define QSPI_FEATURE_ENABLE 1

typedef struct __sflash_configuration_parameter
{
    uint32_t tag;           //!< Set to magic number of 'kqcf'
    uint32_t version;       //!< version of config struct
                            //!< the version number i organized as following:
    uint32_t lengthInBytes; //!< Total length of strcut in bytes

    uint32_t dqs_loopback;          //!< Sets DQS LoopBack Mode to enable Dummy Pad MCR[24]
    uint32_t data_hold_time;        //!< Serial Flash Data In Hold time
    uint32_t reserved0[2];          //!< Reserved for K80
    uint32_t device_mode_config_en; //!< Determine if it is required to config working mode of external spi flash.
    uint32_t device_cmd;            //!< Command to be tranferred to device
    uint32_t write_cmd_ipcr;        //!< IPCR value of Write command
    uint32_t word_addressable;      //!< Determine if the serial flash is word addressable

    uint32_t cs_hold_time;         //!< CS hold time in terms of serial clock.(for example 1 serial clock cyle)
    uint32_t cs_setup_time;        //!< CS setup time in terms of serial clock.(for example 1 serial clock cyle)
    uint32_t sflash_A1_size;       //!< Size of flash connected on QSPI0A Ports and QSPI0A_SS0, in terms of Bytes
    uint32_t sflash_A2_size;       //!< Size of flash connected on QSPI0A Ports and QSPI0A_SS1, in terms of Bytes
    uint32_t sflash_B1_size;       //!< Size of flash connected on QSPI0B Ports and QSPI0B_SS0, in terms of Bytes
    uint32_t sflash_B2_size;       //!< Size of flash connected on QSPI0B Ports and QSPI0B_SS1, in terms of Bytes
    uint32_t sclk_freq;            //!< In  00 - 24MHz, 01 - 48MHz, 10 - 96MHz,(only for SDR Mode)
    uint32_t busy_bit_offset;      //!< Flash device busy bit offset in status register
    uint32_t sflash_type;          //!< SPI flash type: 0-Single,1--Dual 2--Quad, 3-- Octal
    uint32_t sflash_port;          //!< 0--Only Port-A, 1--Both PortA and PortB
    uint32_t ddr_mode_enable;      //!< Enable DDR mode if set to TRUE
    uint32_t dqs_enable;           //!< Enable DQS mode if set to TRUE.
    uint32_t parallel_mode_enable; //!< Enable Individual or parrallel mode.
    uint32_t portA_cs1;            //!< Enable PORTA CS1
    uint32_t portB_cs1;            //!< Enable PORTB CS1
    uint32_t fsphs;                //!< Full speed delay selection for SDR instructions
    uint32_t fsdly;                //!< Full speed phase selection for SDR instructions
    uint32_t ddrsmp;               //!< Select the sampling point for incomming data when serial flash is in DDR mdoe
    uint32_t
        look_up_table[QSPI_LUT_MAX_ENTRIES]; //!< Set of seq to perform optimum read on SFLASH as as per vendor SFLASH
    uint32_t column_address_space;           //!< The width of the column address
    uint32_t config_cmd_en;                  //!< Enable config commands
    uint32_t config_cmds[QSPI_PRE_CMD_CNT];  //!< Config comands, used to configure nor flash
    uint32_t config_cmds_args[QSPI_PRE_CMD_CNT]; //!< Config commands arguments
    uint32_t differential_clock_pin_enable;      //!< Differential flash clock pins enable
    uint32_t flash_CK2_clock_pin_enable;         //!< Flash CK2 clock pin enable
    uint32_t dqs_inverse_sel;                    //!< Select clock source for internal DQS generation
    uint32_t dqs_latency_enable;                 //!< DQS Latency Enable
    uint32_t dqs_loopback_internal;              //!< 0: dqs loopback from pad, 1: dqs loopback internally
    uint32_t dqs_phase_sel;                      //!< dqs phase sel
    uint32_t dqs_fa_delay_chain_sel;             //!< dqs fa delay chain selection
    uint32_t dqs_fb_delay_chain_sel;             //!< dqs fb delay chain selection
    uint32_t reserved1[2];                       //!< reserved
    uint32_t pagesize;                           //!< page Size of Serial Flash
    uint32_t sectorsize;                         //!< sector Size of Serial Flash

    uint32_t timeout_milliseconds; //!< timeout in terms of millisecond in case of infinite loop in qspi driver
                                   //!<  0 represents disabling timeout check. This value is valid since version 1.1.0
    uint32_t ips_command_second_divider; //!< second devider for all IPS commands.
    uint32_t need_multi_phases;          //!< Determine if multiple hases command are needed.
    uint32_t is_spansion_hyperflash;     //!< Determine if connected spi flash device belongs to Hyperflash family
    uint32_t pre_read_status_cmd_address_offset; //!< Address for PreReadStatus command
    uint32_t pre_unlock_cmd_address_offset;      //!< Address for PreWriteEnable command
    uint32_t unlock_cmd_address_offset;          //!< Address for WriteEnable command
    uint32_t pre_program_cmd_address_offset;     //!< Address for PreProgram command
    uint32_t pre_erase_cmd_address_offset;       //!< Address for PreErase command
    uint32_t erase_all_cmd_address_offset;       //!< Address for EraseAll command
    uint32_t reserved2[3];                       //!< Reserved words to make sure qspi config block is page-aligend.

} qspi_config_t, *SFLASH_CONFIGURATION_PARAM_PTR;

#endif // #define __QSPI_H__
