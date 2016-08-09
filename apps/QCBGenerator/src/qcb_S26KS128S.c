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

// This is the QCB for the case that one S26KS128S is connected to QuadSPI0A port.
const qspi_config_t qspi_config_block = {
    .tag = kQspiConfigTag,
    .version = {.version = kQspiVersionTag },
    .lengthInBytes = 512,
    .word_addressable = 1,
    .data_hold_time = 1,
    .sflash_A1_size = 0x1000000,            // 16MB
    .sclk_freq = kQspiSerialClockFreq_High, // High frequency, in DDR mode, it means 96MHz/4 = 24MHz
    .busy_bit_offset =
        0x0001000F, // bit 15 represent busy bit, polarity of this bit is 0, namely busy bit is 0 if device is busy.
    .sflash_type = kQspiFlashPad_Octal,   // Serial Nor Flash works under octal-pad mode
    .sflash_port = kQspiPort_EnablePortA, // Only PortA are enabled
    .ddr_mode_enable = 1,
    .dqs_enable = 1, // DQS function is enabled.
    .look_up_table =
        {
                // Seq0 : Read
                [0] = 0x2B1847A0, // Read command with continuous burst type
                [1] = 0x0F104F10, // 16bit column address,  16 dummy cycles
                [2] = 0x03003B80, // Read 128bytes and STOP.

                // Seq1: Write Enable
                [4] = 0x2B184700, [5] = 0x47004F10, [6] = 0x4755,

                // Seq2: Erase All
                [8] = 0x2B184700, [9] = 0x47004F10, [10] = 0x4710,

                // Seq3: Read Status
                [12] = 0x2B1847A0, // Read command with continuous burst type
                [13] = 0x0F104F10, // 16bit column address,  16 dummy cycles
                [14] = 0x3B02,     // Read 2bytes and stop.

                // Seq4: 8 I/O Page Program
                [16] = 0x2B184700, [17] = 0x3F804F10,

                // Seq6: Pre Erase
                [24] = 0x2B184700, [25] = 0x47004F10, [26] = 0x4780,

                // Seq7: Erase Sector
                [28] = 0x2B184700, [29] = 0x47004F10, [30] = 0x24004730,

                // Seq9: PreWriteEnable
                [36] = 0x2B184700, [37] = 0x47004F10, [38] = 0x47AA,

                // Seq10: PrePageProgram
                [40] = 0x2B184700, [41] = 0x47004F10, [42] = 0x47A0,

                // Seq11: PreReadStatus
                [44] = 0x2B184700, [45] = 0x47004F10, [46] = 0x4770,

        },
    .column_address_space = 3,
    .differential_clock_pin_enable = 1, // Differential clock is enabled.
    .dqs_latency_enable = 1,            // External DQS input signal is used.
    .dqs_fa_delay_chain_sel = 0x10,
    .pagesize = 512,                 // Page Size : 512 bytes
    .sectorsize = 0x40000,           // Sector Size: 256KB
    .ips_command_second_divider = 4, // Set second divider for QSPI serial clock to 16
    .need_multi_phases = 1,          // multiple phases are needed for Erase, Program, etc.
    .is_spansion_hyperflash = 1,     // This device belongs to HyperFlash family.
    .pre_read_status_cmd_address_offset = 0x555 << 1,
    .pre_unlock_cmd_address_offset = 0x555 << 1,
    .unlock_cmd_address_offset = 0x2AA << 1,
    .pre_program_cmd_address_offset = 0x555 << 1,
    .pre_erase_cmd_address_offset = 0x555 << 1,
    .erase_all_cmd_address_offset = 0x555 << 1,
};