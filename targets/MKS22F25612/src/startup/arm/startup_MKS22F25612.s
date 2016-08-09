; * ---------------------------------------------------------------------------------------
; *  @file:    startup_MKS22F25612.s
; *  @purpose: CMSIS Cortex-M4 Core Device Startup File
; *            MKS22F25612
; *  @version: 1.0
; *  @date:    2015-6-23
; *  @build:   b150820
; * ---------------------------------------------------------------------------------------
; *
; * Copyright (c) 1997 - 2015 , Freescale Semiconductor, Inc.
; * All rights reserved.
; *
; * Redistribution and use in source and binary forms, with or without modification,
; * are permitted provided that the following conditions are met:
; *
; * o Redistributions of source code must retain the above copyright notice, this list
; *   of conditions and the following disclaimer.
; *
; * o Redistributions in binary form must reproduce the above copyright notice, this
; *   list of conditions and the following disclaimer in the documentation and/or
; *   other materials provided with the distribution.
; *
; * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
; *   contributors may be used to endorse or promote products derived from this
; *   software without specific prior written permission.
; *
; * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
; * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
; * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
; * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
; * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
; * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
; * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
; * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
; * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
; * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
; *
; *------- <<< Use Configuration Wizard in Context Menu >>> ------------------
; *
; *****************************************************************************/


                PRESERVE8
                THUMB


; Vector Table Mapped to Address 0 at Reset

                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors
                EXPORT  __Vectors_End
                EXPORT  __Vectors_Size
                IMPORT  |Image$$ARM_LIB_STACK$$ZI$$Limit|

__Vectors       DCD     |Image$$ARM_LIB_STACK$$ZI$$Limit| ; Top of Stack
                DCD     Reset_Handler  ; Reset Handler
                DCD     NMI_Handler                         ;NMI Handler
                DCD     HardFault_Handler                   ;Hard Fault Handler
                DCD     MemManage_Handler                   ;MPU Fault Handler
                DCD     BusFault_Handler                    ;Bus Fault Handler
                DCD     UsageFault_Handler                  ;Usage Fault Handler
                DCD     0                                   ;Reserved
                DCD     0                                   ;Reserved
                DCD     0                                   ;Reserved
                DCD     0                                   ;Reserved
                DCD     SVC_Handler                         ;SVCall Handler
                DCD     DebugMon_Handler                    ;Debug Monitor Handler
                DCD     0                                   ;Reserved
                DCD     PendSV_Handler                      ;PendSV Handler
                DCD     SysTick_Handler                     ;SysTick Handler

                                                            ;External Interrupts
                DCD     DMA0_IRQHandler                     ;DMA Channel 0 Transfer Complete
                DCD     DMA1_IRQHandler                     ;DMA Channel 1 Transfer Complete
                DCD     DMA2_IRQHandler                     ;DMA Channel 2 Transfer Complete
                DCD     DMA3_IRQHandler                     ;DMA Channel 3 Transfer Complete
                DCD     DMA4_IRQHandler                     ;DMA Channel 4 Transfer Complete
                DCD     DMA5_IRQHandler                     ;DMA Channel 5 Transfer Complete
                DCD     DMA6_IRQHandler                     ;DMA Channel 6 Transfer Complete
                DCD     DMA7_IRQHandler                     ;DMA Channel 7 Transfer Complete
                DCD     DMA8_IRQHandler                     ;DMA Channel 8 Transfer Complete
                DCD     DMA9_IRQHandler                     ;DMA Channel 9 Transfer Complete
                DCD     DMA10_IRQHandler                    ;DMA Channel 10 Transfer Complete
                DCD     DMA11_IRQHandler                    ;DMA Channel 11 Transfer Complete
                DCD     DMA12_IRQHandler                    ;DMA Channel 12 Transfer Complete
                DCD     DMA13_IRQHandler                    ;DMA Channel 13 Transfer Complete
                DCD     DMA14_IRQHandler                    ;DMA Channel 14 Transfer Complete
                DCD     DMA15_IRQHandler                    ;DMA Channel 15 Transfer Complete
                DCD     DMA_Error_IRQHandler                ;DMA Error Interrupt
                DCD     MCM_IRQHandler                      ;Normal Interrupt
                DCD     FTF_IRQHandler                      ;FTFA Command complete interrupt
                DCD     Read_Collision_IRQHandler           ;Read Collision Interrupt
                DCD     LVD_LVW_IRQHandler                  ;Low Voltage Detect, Low Voltage Warning
                DCD     LLWU_IRQHandler                     ;Low Leakage Wakeup Unit
                DCD     WDOG_EWM_IRQHandler                 ;WDOG Interrupt
                DCD     RNG_IRQHandler                      ;RNG Interrupt
                DCD     LPI2C0_IRQHandler                   ;LPI2C0 interrupt
                DCD     LPI2C1_IRQHandler                   ;LPI2C1 interrupt
                DCD     SPI0_IRQHandler                     ;SPI0 Interrupt
                DCD     SPI1_IRQHandler                     ;SPI1 Interrupt
                DCD     I2S0_Tx_IRQHandler                  ;I2S0 transmit interrupt
                DCD     I2S0_Rx_IRQHandler                  ;I2S0 receive interrupt
                DCD     LPUART0_IRQHandler                  ;LPUART0 status/error interrupt
                DCD     UART0_RX_TX_IRQHandler              ;UART0 Status Sources interrupt
                DCD     UART0_ERR_IRQHandler                ;UART0 Error Sources interrupt
                DCD     UART1_RX_TX_IRQHandler              ;UART1 Status Sources interrupt
                DCD     UART1_ERR_IRQHandler                ;UART1 Error Sources interrupt
                DCD     UART2_RX_TX_IRQHandler              ;UART2 Status Sources interrupt
                DCD     UART2_ERR_IRQHandler                ;UART2 Error Sources interrupt
                DCD     Reserved53_IRQHandler               ;Reserved interrupt 53
                DCD     Reserved54_IRQHandler               ;Reserved interrupt 54
                DCD     ADC0_IRQHandler                     ;ADC0 interrupt
                DCD     CMP0_IRQHandler                     ;CMP0 interrupt
                DCD     Reserved57_IRQHandler               ;Reserved interrupt 57
                DCD     TPM0_IRQHandler                     ;TPM0 Timer Overflow and Channels interrupt
                DCD     TPM1_IRQHandler                     ;TPM1 Timer Overflow and Channels interrupt
                DCD     TPM2_IRQHandler                     ;TPM2 Timer Overflow and Channels interrupt
                DCD     Reserved61_IRQHandler               ;Reserved interrupt 61
                DCD     RTC_IRQHandler                      ;RTC alarm interrupt
                DCD     RTC_Seconds_IRQHandler              ;RTC seconds interrupt
                DCD     PIT0_IRQHandler                     ;PIT timer channel 0 interrupt
                DCD     PIT1_IRQHandler                     ;PIT timer channel 1 interrupt
                DCD     PIT2_IRQHandler                     ;PIT timer channel 2 interrupt
                DCD     PIT3_IRQHandler                     ;PIT timer channel 3 interrupt
                DCD     PDB0_IRQHandler                     ;PDB0 Interrupt
                DCD     USB0_IRQHandler                     ;USB0 interrupt
                DCD     Reserved70_IRQHandler               ;Reserved interrupt 70
                DCD     Reserved71_IRQHandler               ;Reserved interrupt 71
                DCD     DAC0_IRQHandler                     ;DAC0 interrupt
                DCD     MCG_IRQHandler                      ;MCG Interrupt
                DCD     LPTMR0_IRQHandler                   ;LPTimer interrupt
                DCD     PORTA_IRQHandler                    ;Port A interrupt
                DCD     PORTB_IRQHandler                    ;Port B interrupt
                DCD     PORTC_IRQHandler                    ;Port C interrupt
                DCD     PORTD_IRQHandler                    ;Port D interrupt
                DCD     PORTE_IRQHandler                    ;Port E interrupt
                DCD     SWI_IRQHandler                      ;Software interrupt
                DCD     Reserved81_IRQHandler               ;Reserved interrupt 81
                DCD     Reserved82_IRQHandler               ;Reserved interrupt 82
                DCD     Reserved83_IRQHandler               ;Reserved interrupt 83
                DCD     Reserved84_IRQHandler               ;Reserved interrupt 84
                DCD     Reserved85_IRQHandler               ;Reserved interrupt 85
                DCD     FLEXIO_IRQHandler                   ;Flexible IO interrupt
                DCD     Reserved87_IRQHandler               ;Reserved interrupt 87
                DCD     Reserved88_IRQHandler               ;Reserved interrupt 88
                DCD     Reserved89_IRQHandler               ;Reserved interrupt 89
                DCD     Reserved90_IRQHandler               ;Reserved Interrupt 90
                DCD     CAN0_ORed_Message_buffer_IRQHandler ;CAN0 OR'd message buffers interrupt
                DCD     CAN0_Bus_Off_IRQHandler             ;CAN0 bus off interrupt
                DCD     CAN0_Error_IRQHandler               ;CAN0 error interrupt
                DCD     CAN0_Tx_Warning_IRQHandler          ;CAN0 Tx warning interrupt
                DCD     CAN0_Rx_Warning_IRQHandler          ;CAN0 Rx warning interrupt
                DCD     CAN0_Wake_Up_IRQHandler             ;CAN0 wake up interrupt
                DCD     Reserved97_IRQHandler               ;Reserved Interrupt 97
                DCD     Reserved98_IRQHandler               ;Reserved Interrupt 98
                DCD     Reserved99_IRQHandler               ;Reserved Interrupt 99
                DCD     Reserved100_IRQHandler              ;Reserved Interrupt 100
                DCD     Reserved101_IRQHandler              ;Reserved Interrupt 101
                DCD     Reserved102_IRQHandler              ;Reserved Interrupt 102
                DCD     Reserved103_IRQHandler              ;Reserved Interrupt 103
                DCD     I2S1_Tx_IRQHandler                  ;I2S1 transmit interrupt
                DCD     I2S1_Rx_IRQHandler                  ;I2S1 receive interrupt
                DCD     Reserved106_IRQHandler              ;Reserved Interrupt 106
                DCD     Reserved107_IRQHandler              ;Reserved Interrupt 107
                DCD     Reserved108_IRQHandler              ;Reserved Interrupt 108
                DCD     Reserved109_IRQHandler              ;Reserved Interrupt 109
                DCD     CAN1_ORed_Message_buffer_IRQHandler ;CAN0 OR'd message buffers interrupt
                DCD     CAN1_Bus_Off_IRQHandler             ;CAN1 bus off interrupt
                DCD     CAN1_Error_IRQHandler               ;CAN1 error interrupt
                DCD     CAN1_Tx_Warning_IRQHandler          ;CAN1 Tx warning interrupt
                DCD     CAN1_Rx_Warning_IRQHandler          ;CAN1 Rx warning interrupt
                DCD     CAN1_Wake_Up_IRQHandler             ;CAN1 wake up interrupt
                DCD     DefaultISR                          ;116
                DCD     DefaultISR                          ;117
                DCD     DefaultISR                          ;118
                DCD     DefaultISR                          ;119
                DCD     DefaultISR                          ;120
                DCD     DefaultISR                          ;121
                DCD     DefaultISR                          ;122
                DCD     DefaultISR                          ;123
                DCD     DefaultISR                          ;124
                DCD     DefaultISR                          ;125
                DCD     DefaultISR                          ;126
                DCD     DefaultISR                          ;127
                DCD     DefaultISR                          ;128
                DCD     DefaultISR                          ;129
                DCD     DefaultISR                          ;130
                DCD     DefaultISR                          ;131
                DCD     DefaultISR                          ;132
                DCD     DefaultISR                          ;133
                DCD     DefaultISR                          ;134
                DCD     DefaultISR                          ;135
                DCD     DefaultISR                          ;136
                DCD     DefaultISR                          ;137
                DCD     DefaultISR                          ;138
                DCD     DefaultISR                          ;139
                DCD     DefaultISR                          ;140
                DCD     DefaultISR                          ;141
                DCD     DefaultISR                          ;142
                DCD     DefaultISR                          ;143
                DCD     DefaultISR                          ;144
                DCD     DefaultISR                          ;145
                DCD     DefaultISR                          ;146
                DCD     DefaultISR                          ;147
                DCD     DefaultISR                          ;148
                DCD     DefaultISR                          ;149
                DCD     DefaultISR                          ;150
                DCD     DefaultISR                          ;151
                DCD     DefaultISR                          ;152
                DCD     DefaultISR                          ;153
                DCD     DefaultISR                          ;154
                DCD     DefaultISR                          ;155
                DCD     DefaultISR                          ;156
                DCD     DefaultISR                          ;157
                DCD     DefaultISR                          ;158
                DCD     DefaultISR                          ;159
                DCD     DefaultISR                          ;160
                DCD     DefaultISR                          ;161
                DCD     DefaultISR                          ;162
                DCD     DefaultISR                          ;163
                DCD     DefaultISR                          ;164
                DCD     DefaultISR                          ;165
                DCD     DefaultISR                          ;166
                DCD     DefaultISR                          ;167
                DCD     DefaultISR                          ;168
                DCD     DefaultISR                          ;169
                DCD     DefaultISR                          ;170
                DCD     DefaultISR                          ;171
                DCD     DefaultISR                          ;172
                DCD     DefaultISR                          ;173
                DCD     DefaultISR                          ;174
                DCD     DefaultISR                          ;175
                DCD     DefaultISR                          ;176
                DCD     DefaultISR                          ;177
                DCD     DefaultISR                          ;178
                DCD     DefaultISR                          ;179
                DCD     DefaultISR                          ;180
                DCD     DefaultISR                          ;181
                DCD     DefaultISR                          ;182
                DCD     DefaultISR                          ;183
                DCD     DefaultISR                          ;184
                DCD     DefaultISR                          ;185
                DCD     DefaultISR                          ;186
                DCD     DefaultISR                          ;187
                DCD     DefaultISR                          ;188
                DCD     DefaultISR                          ;189
                DCD     DefaultISR                          ;190
                DCD     DefaultISR                          ;191
                DCD     DefaultISR                          ;192
                DCD     DefaultISR                          ;193
                DCD     DefaultISR                          ;194
                DCD     DefaultISR                          ;195
                DCD     DefaultISR                          ;196
                DCD     DefaultISR                          ;197
                DCD     DefaultISR                          ;198
                DCD     DefaultISR                          ;199
                DCD     DefaultISR                          ;200
                DCD     DefaultISR                          ;201
                DCD     DefaultISR                          ;202
                DCD     DefaultISR                          ;203
                DCD     DefaultISR                          ;204
                DCD     DefaultISR                          ;205
                DCD     DefaultISR                          ;206
                DCD     DefaultISR                          ;207
                DCD     DefaultISR                          ;208
                DCD     DefaultISR                          ;209
                DCD     DefaultISR                          ;210
                DCD     DefaultISR                          ;211
                DCD     DefaultISR                          ;212
                DCD     DefaultISR                          ;213
                DCD     DefaultISR                          ;214
                DCD     DefaultISR                          ;215
                DCD     DefaultISR                          ;216
                DCD     DefaultISR                          ;217
                DCD     DefaultISR                          ;218
                DCD     DefaultISR                          ;219
                DCD     DefaultISR                          ;220
                DCD     DefaultISR                          ;221
                DCD     DefaultISR                          ;222
                DCD     DefaultISR                          ;223
                DCD     DefaultISR                          ;224
                DCD     DefaultISR                          ;225
                DCD     DefaultISR                          ;226
                DCD     DefaultISR                          ;227
                DCD     DefaultISR                          ;228
                DCD     DefaultISR                          ;229
                DCD     DefaultISR                          ;230
                DCD     DefaultISR                          ;231
                DCD     DefaultISR                          ;232
                DCD     DefaultISR                          ;233
                DCD     DefaultISR                          ;234
                DCD     DefaultISR                          ;235
                DCD     DefaultISR                          ;236
                DCD     DefaultISR                          ;237
                DCD     DefaultISR                          ;238
                DCD     DefaultISR                          ;239
__Vectors_End

	IF		BL_HAS_BOOTLOADER_CONFIG == 1
        ;__bootloaderConfigurationArea ; 0x3c0
		DCD     0x6766636b    ; [00:03] tag - 'kcfg' Tag value used to validate the bootloader configuration data. Must be set to 'kcfg'.
        DCD     0xFFFFFFFF    ; [04:07] crcStartAddress
        DCD     0xFFFFFFFF    ; [08:0b] crcByteCount
        DCD     0xFFFFFFFF    ; [0c:0f] crcExpectedValue
        DCB     0xFF          ; [10:10] enabledPeripherals
        DCB     0xFF          ; [11:11] i2cSlaveAddress
        DCW     5000           ; [12:13] peripheralDetectionTimeoutMs - Timeout in milliseconds for peripheral detection before jumping to application code
        DCW     0xFFFF        ; [14:15] usbVid
        DCW     0xFFFF        ; [16:17] usbPid
        DCD     0xFFFFFFFF    ; [18:1b] usbStringsPointer
        DCB     0xFF          ; [1c:1c] clockFlags - High Speed and other clock options
        DCB     0xFF          ; [1d:1d] clockDivider - One's complement of clock divider, zero divider is divide by 1
        DCW     0xFFFF        ; [1e:1f] reserved
        ; Fill to align with flash configuration field. 
        DCD     0xFFFFFFFF
        DCD     0xFFFFFFFF
        DCD     0xFFFFFFFF
        DCD     0xFFFFFFFF
        DCD     0xFFFFFFFF
        DCD     0xFFFFFFFF
        DCD     0xFFFFFFFF			
        DCD     0xFFFFFFFF        ; Reserved for user TRIM value
	ELSE      
        ; Fill to align with flash configuration field. 
        DCD     0xFFFFFFFF
        DCD     0xFFFFFFFF
        DCD     0xFFFFFFFF
        DCD     0xFFFFFFFF
        DCD     0xFFFFFFFF
        DCD     0xFFFFFFFF
        DCD     0xFFFFFFFF
        DCD     0xFFFFFFFF
        DCD     0xFFFFFFFF
        DCD     0xFFFFFFFF
        DCD     0xFFFFFFFF
        DCD     0xFFFFFFFF
        DCD     0xFFFFFFFF
        DCD     0xFFFFFFFF
        DCD     0xFFFFFFFF     			
        DCD     0xFFFFFFFF      ; Reserved for user TRIM value
	ENDIF // BL_HAS_BOOTLOADER_CONFIG

__Vectors_Size 	EQU     __Vectors_End - __Vectors

; <h> Flash Configuration
;   <i> 16-byte flash configuration field that stores default protection settings (loaded on reset)
;   <i> and security information that allows the MCU to restrict access to the FTFL module.
;   <h> Backdoor Comparison Key
;     <o0>  Backdoor Comparison Key 0.  <0x0-0xFF:2>
;     <o1>  Backdoor Comparison Key 1.  <0x0-0xFF:2>
;     <o2>  Backdoor Comparison Key 2.  <0x0-0xFF:2>
;     <o3>  Backdoor Comparison Key 3.  <0x0-0xFF:2>
;     <o4>  Backdoor Comparison Key 4.  <0x0-0xFF:2>
;     <o5>  Backdoor Comparison Key 5.  <0x0-0xFF:2>
;     <o6>  Backdoor Comparison Key 6.  <0x0-0xFF:2>
;     <o7>  Backdoor Comparison Key 7.  <0x0-0xFF:2>
BackDoorK0      EQU     0xFF
BackDoorK1      EQU     0xFF
BackDoorK2      EQU     0xFF
BackDoorK3      EQU     0xFF
BackDoorK4      EQU     0xFF
BackDoorK5      EQU     0xFF
BackDoorK6      EQU     0xFF
BackDoorK7      EQU     0xFF
;   </h>
;   <h> Program flash protection bytes (FPROT)
;     <i> Each program flash region can be protected from program and erase operation by setting the associated PROT bit.
;     <i> Each bit protects a 1/32 region of the program flash memory.
;     <h> FPROT0
;       <i> Program Flash Region Protect Register 0
;       <i> 1/32 - 8/32 region
;       <o.0>   FPROT0.0
;       <o.1>   FPROT0.1
;       <o.2>   FPROT0.2
;       <o.3>   FPROT0.3
;       <o.4>   FPROT0.4
;       <o.5>   FPROT0.5
;       <o.6>   FPROT0.6
;       <o.7>   FPROT0.7
nFPROT0         EQU     0x00
FPROT0          EQU     nFPROT0:EOR:0xFF
;     </h>
;     <h> FPROT1
;       <i> Program Flash Region Protect Register 1
;       <i> 9/32 - 16/32 region
;       <o.0>   FPROT1.0
;       <o.1>   FPROT1.1
;       <o.2>   FPROT1.2
;       <o.3>   FPROT1.3
;       <o.4>   FPROT1.4
;       <o.5>   FPROT1.5
;       <o.6>   FPROT1.6
;       <o.7>   FPROT1.7
nFPROT1         EQU     0x00
FPROT1          EQU     nFPROT1:EOR:0xFF
;     </h>
;     <h> FPROT2
;       <i> Program Flash Region Protect Register 2
;       <i> 17/32 - 24/32 region
;       <o.0>   FPROT2.0
;       <o.1>   FPROT2.1
;       <o.2>   FPROT2.2
;       <o.3>   FPROT2.3
;       <o.4>   FPROT2.4
;       <o.5>   FPROT2.5
;       <o.6>   FPROT2.6
;       <o.7>   FPROT2.7
nFPROT2         EQU     0x00
FPROT2          EQU     nFPROT2:EOR:0xFF
;     </h>
;     <h> FPROT3
;       <i> Program Flash Region Protect Register 3
;       <i> 25/32 - 32/32 region
;       <o.0>   FPROT3.0
;       <o.1>   FPROT3.1
;       <o.2>   FPROT3.2
;       <o.3>   FPROT3.3
;       <o.4>   FPROT3.4
;       <o.5>   FPROT3.5
;       <o.6>   FPROT3.6
;       <o.7>   FPROT3.7
nFPROT3         EQU     0x00
FPROT3          EQU     nFPROT3:EOR:0xFF
;     </h>
;   </h>
;   <h> Flash nonvolatile option byte (FOPT)
;     <i> Allows the user to customize the operation of the MCU at boot time.
;     <o.0> LPBOOT
;       <0=> Low-power boot
;       <1=> Normal boot
;     <o.1> EZPORT_DIS
;       <0=> EzPort operation is disabled
;       <1=> EzPort operation is enabled
;     <o.2> NMI_DIS
;       <0=> NMI interrupts are always blocked
;       <1=> NMI_b pin/interrupts reset default to enabled
;     <o.5> FAST_INIT
;       <0=> Slower initialization
;       <1=> Fast Initialization
FOPT          EQU     0xFF
;   </h>
;   <h> Flash security byte (FSEC)
;     <i> WARNING: If SEC field is configured as "MCU security status is secure" and MEEN field is configured as "Mass erase is disabled",
;     <i> MCU's security status cannot be set back to unsecure state since Mass erase via the debugger is blocked !!!
;     <o.0..1> SEC
;       <2=> MCU security status is unsecure
;       <3=> MCU security status is secure
;         <i> Flash Security
;     <o.2..3> FSLACC
;       <2=> Freescale factory access denied
;       <3=> Freescale factory access granted
;         <i> Freescale Failure Analysis Access Code
;     <o.4..5> MEEN
;       <2=> Mass erase is disabled
;       <3=> Mass erase is enabled
;     <o.6..7> KEYEN
;       <2=> Backdoor key access enabled
;       <3=> Backdoor key access disabled
;         <i> Backdoor Key Security Enable
FSEC          EQU     0xFE
;   </h>
; </h>
                IF      :LNOT::DEF:RAM_TARGET
                AREA    FlashConfig, DATA, READONLY
__FlashConfig
                DCB     BackDoorK0, BackDoorK1, BackDoorK2, BackDoorK3
                DCB     BackDoorK4, BackDoorK5, BackDoorK6, BackDoorK7
                DCB     FPROT0    , FPROT1    , FPROT2    , FPROT3
                DCB     FSEC      , FOPT      , 0xFF      , 0xFF
                ENDIF


                AREA    |.text|, CODE, READONLY

; Reset Handler

Reset_Handler   PROC
                EXPORT  Reset_Handler             [WEAK]
                IMPORT  SystemInit
                IMPORT  init_data_bss
                IMPORT  __main

                IF      :LNOT::DEF:RAM_TARGET
                LDR R0, =FlashConfig    ; dummy read, workaround for flashConfig
                ENDIF

                CPSID   I               ; Mask interrupts
                LDR     R0, =SystemInit
                BLX     R0
                LDR     R0, =init_data_bss
                BLX     R0
                CPSIE   i               ; Unmask interrupts
                LDR     R0, =__main
                BX      R0
                ENDP


; Dummy Exception Handlers (infinite loops which can be modified)
NMI_Handler\
                PROC
                EXPORT  NMI_Handler         [WEAK]
                B       .
                ENDP
HardFault_Handler\
                PROC
                EXPORT  HardFault_Handler         [WEAK]
                B       .
                ENDP
MemManage_Handler\
                PROC
                EXPORT  MemManage_Handler         [WEAK]
                B       .
                ENDP
BusFault_Handler\
                PROC
                EXPORT  BusFault_Handler         [WEAK]
                B       .
                ENDP
UsageFault_Handler\
                PROC
                EXPORT  UsageFault_Handler         [WEAK]
                B       .
                ENDP
SVC_Handler\
                PROC
                EXPORT  SVC_Handler         [WEAK]
                B       .
                ENDP
DebugMon_Handler\
                PROC
                EXPORT  DebugMon_Handler         [WEAK]
                B       .
                ENDP
PendSV_Handler\
                PROC
                EXPORT  PendSV_Handler         [WEAK]
                B       .
                ENDP
SysTick_Handler\
                PROC
                EXPORT  SysTick_Handler         [WEAK]
                B       .
                ENDP
Default_Handler\
                PROC
                EXPORT  DMA0_IRQHandler         [WEAK]
                EXPORT  DMA1_IRQHandler         [WEAK]
                EXPORT  DMA2_IRQHandler         [WEAK]
                EXPORT  DMA3_IRQHandler         [WEAK]
                EXPORT  DMA4_IRQHandler         [WEAK]
                EXPORT  DMA5_IRQHandler         [WEAK]
                EXPORT  DMA6_IRQHandler         [WEAK]
                EXPORT  DMA7_IRQHandler         [WEAK]
                EXPORT  DMA8_IRQHandler         [WEAK]
                EXPORT  DMA9_IRQHandler         [WEAK]
                EXPORT  DMA10_IRQHandler         [WEAK]
                EXPORT  DMA11_IRQHandler         [WEAK]
                EXPORT  DMA12_IRQHandler         [WEAK]
                EXPORT  DMA13_IRQHandler         [WEAK]
                EXPORT  DMA14_IRQHandler         [WEAK]
                EXPORT  DMA15_IRQHandler         [WEAK]
                EXPORT  DMA_Error_IRQHandler         [WEAK]
                EXPORT  MCM_IRQHandler         [WEAK]
                EXPORT  FTF_IRQHandler         [WEAK]
                EXPORT  Read_Collision_IRQHandler         [WEAK]
                EXPORT  LVD_LVW_IRQHandler         [WEAK]
                EXPORT  LLWU_IRQHandler         [WEAK]
                EXPORT  WDOG_EWM_IRQHandler         [WEAK]
                EXPORT  RNG_IRQHandler         [WEAK]
                EXPORT  LPI2C0_IRQHandler         [WEAK]
                EXPORT  LPI2C1_IRQHandler         [WEAK]
                EXPORT  SPI0_IRQHandler         [WEAK]
                EXPORT  SPI1_IRQHandler         [WEAK]
                EXPORT  I2S0_Tx_IRQHandler         [WEAK]
                EXPORT  I2S0_Rx_IRQHandler         [WEAK]
                EXPORT  LPUART0_IRQHandler         [WEAK]
                EXPORT  UART0_RX_TX_IRQHandler         [WEAK]
                EXPORT  UART0_ERR_IRQHandler         [WEAK]
                EXPORT  UART1_RX_TX_IRQHandler         [WEAK]
                EXPORT  UART1_ERR_IRQHandler         [WEAK]
                EXPORT  UART2_RX_TX_IRQHandler         [WEAK]
                EXPORT  UART2_ERR_IRQHandler         [WEAK]
                EXPORT  Reserved53_IRQHandler         [WEAK]
                EXPORT  Reserved54_IRQHandler         [WEAK]
                EXPORT  ADC0_IRQHandler         [WEAK]
                EXPORT  CMP0_IRQHandler         [WEAK]
                EXPORT  Reserved57_IRQHandler         [WEAK]
                EXPORT  TPM0_IRQHandler         [WEAK]
                EXPORT  TPM1_IRQHandler         [WEAK]
                EXPORT  TPM2_IRQHandler         [WEAK]
                EXPORT  Reserved61_IRQHandler         [WEAK]
                EXPORT  RTC_IRQHandler         [WEAK]
                EXPORT  RTC_Seconds_IRQHandler         [WEAK]
                EXPORT  PIT0_IRQHandler         [WEAK]
                EXPORT  PIT1_IRQHandler         [WEAK]
                EXPORT  PIT2_IRQHandler         [WEAK]
                EXPORT  PIT3_IRQHandler         [WEAK]
                EXPORT  PDB0_IRQHandler         [WEAK]
                EXPORT  USB0_IRQHandler         [WEAK]
                EXPORT  Reserved70_IRQHandler         [WEAK]
                EXPORT  Reserved71_IRQHandler         [WEAK]
                EXPORT  DAC0_IRQHandler         [WEAK]
                EXPORT  MCG_IRQHandler         [WEAK]
                EXPORT  LPTMR0_IRQHandler         [WEAK]
                EXPORT  PORTA_IRQHandler         [WEAK]
                EXPORT  PORTB_IRQHandler         [WEAK]
                EXPORT  PORTC_IRQHandler         [WEAK]
                EXPORT  PORTD_IRQHandler         [WEAK]
                EXPORT  PORTE_IRQHandler         [WEAK]
                EXPORT  SWI_IRQHandler         [WEAK]
                EXPORT  Reserved81_IRQHandler         [WEAK]
                EXPORT  Reserved82_IRQHandler         [WEAK]
                EXPORT  Reserved83_IRQHandler         [WEAK]
                EXPORT  Reserved84_IRQHandler         [WEAK]
                EXPORT  Reserved85_IRQHandler         [WEAK]
                EXPORT  FLEXIO_IRQHandler         [WEAK]
                EXPORT  Reserved87_IRQHandler         [WEAK]
                EXPORT  Reserved88_IRQHandler         [WEAK]
                EXPORT  Reserved89_IRQHandler         [WEAK]
                EXPORT  Reserved90_IRQHandler         [WEAK]
                EXPORT  CAN0_ORed_Message_buffer_IRQHandler         [WEAK]
                EXPORT  CAN0_Bus_Off_IRQHandler         [WEAK]
                EXPORT  CAN0_Error_IRQHandler         [WEAK]
                EXPORT  CAN0_Tx_Warning_IRQHandler         [WEAK]
                EXPORT  CAN0_Rx_Warning_IRQHandler         [WEAK]
                EXPORT  CAN0_Wake_Up_IRQHandler         [WEAK]
                EXPORT  Reserved97_IRQHandler         [WEAK]
                EXPORT  Reserved98_IRQHandler         [WEAK]
                EXPORT  Reserved99_IRQHandler         [WEAK]
                EXPORT  Reserved100_IRQHandler         [WEAK]
                EXPORT  Reserved101_IRQHandler         [WEAK]
                EXPORT  Reserved102_IRQHandler         [WEAK]
                EXPORT  Reserved103_IRQHandler         [WEAK]
                EXPORT  I2S1_Tx_IRQHandler         [WEAK]
                EXPORT  I2S1_Rx_IRQHandler         [WEAK]
                EXPORT  Reserved106_IRQHandler         [WEAK]
                EXPORT  Reserved107_IRQHandler         [WEAK]
                EXPORT  Reserved108_IRQHandler         [WEAK]
                EXPORT  Reserved109_IRQHandler         [WEAK]
                EXPORT  CAN1_ORed_Message_buffer_IRQHandler         [WEAK]
                EXPORT  CAN1_Bus_Off_IRQHandler         [WEAK]
                EXPORT  CAN1_Error_IRQHandler         [WEAK]
                EXPORT  CAN1_Tx_Warning_IRQHandler         [WEAK]
                EXPORT  CAN1_Rx_Warning_IRQHandler         [WEAK]
                EXPORT  CAN1_Wake_Up_IRQHandler         [WEAK]
                EXPORT  DefaultISR         [WEAK]
DMA0_IRQHandler
DMA1_IRQHandler
DMA2_IRQHandler
DMA3_IRQHandler
DMA4_IRQHandler
DMA5_IRQHandler
DMA6_IRQHandler
DMA7_IRQHandler
DMA8_IRQHandler
DMA9_IRQHandler
DMA10_IRQHandler
DMA11_IRQHandler
DMA12_IRQHandler
DMA13_IRQHandler
DMA14_IRQHandler
DMA15_IRQHandler
DMA_Error_IRQHandler
MCM_IRQHandler
FTF_IRQHandler
Read_Collision_IRQHandler
LVD_LVW_IRQHandler
LLWU_IRQHandler
WDOG_EWM_IRQHandler
RNG_IRQHandler
LPI2C0_IRQHandler
LPI2C1_IRQHandler
SPI0_IRQHandler
SPI1_IRQHandler
I2S0_Tx_IRQHandler
I2S0_Rx_IRQHandler
LPUART0_IRQHandler
UART0_RX_TX_IRQHandler
UART0_ERR_IRQHandler
UART1_RX_TX_IRQHandler
UART1_ERR_IRQHandler
UART2_RX_TX_IRQHandler
UART2_ERR_IRQHandler
Reserved53_IRQHandler
Reserved54_IRQHandler
ADC0_IRQHandler
CMP0_IRQHandler
Reserved57_IRQHandler
TPM0_IRQHandler
TPM1_IRQHandler
TPM2_IRQHandler
Reserved61_IRQHandler
RTC_IRQHandler
RTC_Seconds_IRQHandler
PIT0_IRQHandler
PIT1_IRQHandler
PIT2_IRQHandler
PIT3_IRQHandler
PDB0_IRQHandler
USB0_IRQHandler
Reserved70_IRQHandler
Reserved71_IRQHandler
DAC0_IRQHandler
MCG_IRQHandler
LPTMR0_IRQHandler
PORTA_IRQHandler
PORTB_IRQHandler
PORTC_IRQHandler
PORTD_IRQHandler
PORTE_IRQHandler
SWI_IRQHandler
Reserved81_IRQHandler
Reserved82_IRQHandler
Reserved83_IRQHandler
Reserved84_IRQHandler
Reserved85_IRQHandler
FLEXIO_IRQHandler
Reserved87_IRQHandler
Reserved88_IRQHandler
Reserved89_IRQHandler
Reserved90_IRQHandler
CAN0_ORed_Message_buffer_IRQHandler
CAN0_Bus_Off_IRQHandler
CAN0_Error_IRQHandler
CAN0_Tx_Warning_IRQHandler
CAN0_Rx_Warning_IRQHandler
CAN0_Wake_Up_IRQHandler
Reserved97_IRQHandler
Reserved98_IRQHandler
Reserved99_IRQHandler
Reserved100_IRQHandler
Reserved101_IRQHandler
Reserved102_IRQHandler
Reserved103_IRQHandler
I2S1_Tx_IRQHandler
I2S1_Rx_IRQHandler
Reserved106_IRQHandler
Reserved107_IRQHandler
Reserved108_IRQHandler
Reserved109_IRQHandler
CAN1_ORed_Message_buffer_IRQHandler
CAN1_Bus_Off_IRQHandler
CAN1_Error_IRQHandler
CAN1_Tx_Warning_IRQHandler
CAN1_Rx_Warning_IRQHandler
CAN1_Wake_Up_IRQHandler
DefaultISR
                B      DefaultISR
                ENDP
                  ALIGN


                END
