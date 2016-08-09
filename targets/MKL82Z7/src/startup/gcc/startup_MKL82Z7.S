/* ---------------------------------------------------------------------------------------*/
/*  @file:    startup_MKL82Z7.s                                                           */
/*  @purpose: CMSIS Cortex-M0P Core Device Startup File                                   */
/*            MKL82Z7                                                                     */
/*  @version: 2.0                                                                         */
/*  @date:    2015-9-24                                                                   */
/*  @build:   b151106                                                                     */
/* ---------------------------------------------------------------------------------------*/
/*                                                                                        */
/* Copyright (c) 1997 - 2015 , Freescale Semiconductor, Inc.                              */
/* All rights reserved.                                                                   */
/*                                                                                        */
/* Redistribution and use in source and binary forms, with or without modification,       */
/* are permitted provided that the following conditions are met:                          */
/*                                                                                        */
/* o Redistributions of source code must retain the above copyright notice, this list     */
/*   of conditions and the following disclaimer.                                          */
/*                                                                                        */
/* o Redistributions in binary form must reproduce the above copyright notice, this       */
/*   list of conditions and the following disclaimer in the documentation and/or          */
/*   other materials provided with the distribution.                                      */
/*                                                                                        */
/* o Neither the name of Freescale Semiconductor, Inc. nor the names of its               */
/*   contributors may be used to endorse or promote products derived from this            */
/*   software without specific prior written permission.                                  */
/*                                                                                        */
/* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND        */
/* ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED          */
/* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE                 */
/* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR       */
/* ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES         */
/* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;           */
/* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON         */
/* ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT                */
/* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS          */
/* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.                           */
/*****************************************************************************/
/* Version: GCC for ARM Embedded Processors                                  */
/*****************************************************************************/
    .syntax unified
    .arch armv6-m

    .section .isr_vector, "a"
    .align 2
    .globl __isr_vector
__isr_vector:
    .long   __StackTop                                      /* Top of Stack */
    .long   Reset_Handler                                   /* Reset Handler */
    .long   NMI_Handler                                     /* NMI Handler*/
    .long   HardFault_Handler                               /* Hard Fault Handler*/
    .long   0                                               /* Reserved*/
    .long   0                                               /* Reserved*/
    .long   0                                               /* Reserved*/
    .long   0                                               /* Reserved*/
    .long   0                                               /* Reserved*/
    .long   0                                               /* Reserved*/
    .long   0                                               /* Reserved*/
    .long   SVC_Handler                                     /* SVCall Handler*/
    .long   0                                               /* Reserved*/
    .long   0                                               /* Reserved*/
    .long   PendSV_Handler                                  /* PendSV Handler*/
    .long   SysTick_Handler                                 /* SysTick Handler*/

                                                            /* External Interrupts*/
    .long   DMA0_DMA4_IRQHandler                            /* DMA channel 0, 4 transfer complete*/
    .long   DMA1_DMA5_IRQHandler                            /* DMA channel 1, 5 transfer complete*/
    .long   DMA2_DMA6_IRQHandler                            /* DMA channel 2, 6 transfer complete*/
    .long   DMA3_DMA7_IRQHandler                            /* DMA channel 3, 7 transfer complete*/
    .long   DMA_Error_IRQHandler                            /* DMA channel 0 - 7 error*/
    .long   FLEXIO0_IRQHandler                              /* Flexible IO*/
    .long   TPM0_IRQHandler                                 /* Timer/PWM module 0*/
    .long   TPM1_IRQHandler                                 /* Timer/PWM module 1*/
    .long   TPM2_IRQHandler                                 /* Timer/PWM module 2*/
    .long   PIT0_IRQHandler                                 /* Periodic Interrupt Timer 0*/
    .long   SPI0_IRQHandler                                 /* Serial Peripheral Interface 0*/
    .long   EMVSIM0_IRQHandler                              /* EMVSIM0 common interrupt*/
    .long   LPUART0_IRQHandler                              /* LPUART0 status and error*/
    .long   LPUART1_IRQHandler                              /* LPUART1 status and error*/
    .long   I2C0_IRQHandler                                 /* Inter-Integrated Circuit 0*/
    .long   QSPI0_IRQHandler                                /* QuadSPI0 interrupt*/
    .long   Reserved32_IRQHandler                           /* DryIce tamper detect*/
    .long   PORTA_IRQHandler                                /* Pin detect Port A*/
    .long   PORTB_IRQHandler                                /* Pin detect Port B*/
    .long   PORTC_IRQHandler                                /* Pin detect Port C*/
    .long   PORTD_IRQHandler                                /* Pin detect Port D*/
    .long   PORTE_IRQHandler                                /* Pin detect Port E*/
    .long   LLWU_IRQHandler                                 /* Low Leakage Wakeup*/
    .long   LTC0_IRQHandler                                 /* Low power trusted cryptographic*/
    .long   USB0_IRQHandler                                 /* USB OTG interrupt*/
    .long   ADC0_IRQHandler                                 /* Analog-to-Digital Converter 0*/
    .long   LPTMR0_IRQHandler                               /* Low-Power Timer 0*/
    .long   RTC_Seconds_IRQHandler                          /* RTC seconds*/
    .long   INTMUX0_0_IRQHandler                            /* Selectable peripheral interrupt INTMUX0-0*/
    .long   INTMUX0_1_IRQHandler                            /* Selectable peripheral interrupt INTMUX0-1*/
    .long   INTMUX0_2_IRQHandler                            /* Selectable peripheral interrupt INTMUX0-2*/
    .long   INTMUX0_3_IRQHandler                            /* Selectable peripheral interrupt INTMUX0-3*/
    .long   LPTMR1_IRQHandler                               /* Low-Power Timer 1 (INTMUX source IRQ0)*/
    .long   Reserved49_IRQHandler                           /* Reserved interrupt (INTMUX source IRQ1)*/
    .long   Reserved50_IRQHandler                           /* Reserved interrupt (INTMUX source IRQ2)*/
    .long   Reserved51_IRQHandler                           /* Reserved interrupt (INTMUX source IRQ3)*/
    .long   SPI1_IRQHandler                                 /* Serial Peripheral Interface 1 (INTMUX source IRQ4)*/
    .long   LPUART2_IRQHandler                              /* LPUART2 status and error (INTMUX source IRQ5)*/
    .long   EMVSIM1_IRQHandler                              /* EMVSIM1 common interrupt (INTMUX source IRQ6)*/
    .long   I2C1_IRQHandler                                 /* Inter-Integrated Circuit 1 (INTMUX source IRQ7)*/
    .long   TSI0_IRQHandler                                 /* Touch Sensing Input 0 (INTMUX source IRQ8)*/
    .long   PMC_IRQHandler                                  /* PMC controller low-voltage detect, low-voltage warning (INTMUX source IRQ9)*/
    .long   FTFA_IRQHandler                                 /* FTFA command complete/read collision (INTMUX source IRQ10)*/
    .long   MCG_IRQHandler                                  /* Multipurpose clock generator (INTMUX source IRQ11)*/
    .long   WDOG_EWM_IRQHandler                             /* Single interrupt vector for  WDOG and EWM (INTMUX source IRQ12)*/
    .long   DAC0_IRQHandler                                 /* Digital-to-analog converter 0 (INTMUX source IRQ13)*/
    .long   TRNG0_IRQHandler                                /* True randon number generator (INTMUX source IRQ14)*/
    .long   Reserved63_IRQHandler                           /* Reserved interrupt (INTMUX source IRQ15)*/
    .long   CMP0_IRQHandler                                 /* Comparator 0 (INTMUX source IRQ16)*/
    .long   Reserved65_IRQHandler                           /* Reserved interrupt (INTMUX source IRQ17)*/
    .long   RTC_Alarm_IRQHandler                            /* Real time clock (INTMUX source IRQ18)*/
    .long   Reserved67_IRQHandler                           /* Reserved interrupt (INTMUX source IRQ19)*/
    .long   Reserved68_IRQHandler                           /* Reserved interrupt (INTMUX source IRQ20)*/
    .long   Reserved69_IRQHandler                           /* Reserved interrupt (INTMUX source IRQ21)*/
    .long   Reserved70_IRQHandler                           /* Reserved interrupt (INTMUX source IRQ22)*/
    .long   Reserved71_IRQHandler                           /* Reserved interrupt (INTMUX source IRQ23)*/
    .long   DMA4_IRQHandler                                 /* DMA channel 4 transfer complete (INTMUX source IRQ24)*/
    .long   DMA5_IRQHandler                                 /* DMA channel 5 transfer complete (INTMUX source IRQ25)*/
    .long   DMA6_IRQHandler                                 /* DMA channel 6 transfer complete (INTMUX source IRQ26)*/
    .long   DMA7_IRQHandler                                 /* DMA channel 7 transfer complete (INTMUX source IRQ27)*/
    .long   Reserved76_IRQHandler                           /* Reserved interrupt (INTMUX source IRQ28)*/
    .long   Reserved77_IRQHandler                           /* Reserved interrupt (INTMUX source IRQ29)*/
    .long   Reserved78_IRQHandler                           /* Reserved interrupt (INTMUX source IRQ30)*/
    .long   Reserved79_IRQHandler                           /* Reserved interrupt (INTMUX source IRQ31)*/

    .size    __isr_vector, . - __isr_vector


 /* Bootloader Config Area */
    .section .BootloaderConfig, "a"
#ifdef BL_HAS_BOOTLOADER_CONFIG

//__bootloaderConfigurationArea ; 0x3c0
    .long     0x6766636b    // [00:03] tag - Tag value used to validate the bootloader configuration data. Must be set to 'kcfg'
    .long     0xFFFFFFFF    // [04:07] crcStartAddress
    .long     0xFFFFFFFF    // [08:0b] crcByteCount
    .long     0xFFFFFFFF    // [0c:0f] crcExpectedValue
    .byte     0xFF          // [10:10] enabledPeripherals
    .byte     0xFF          // [11:11] i2cSlaveAddress
    .short    5000          // [12:13] peripheralDetectionTimeoutMs - Timeout in milliseconds for peripheral detection before jumping to application code
    .short    0xFFFF       // [14:15] usbVid
    .short    0xFFFF       // [16:17] usbPid
    .long     0xFFFFFFFF    // [18:1b] usbStringsPointer
    .byte     0xFF          // [1c:1c] clockFlags - High Speed and other clock options
    .byte     0xFF          // [1d:1d] clockDivider - One's complement of clock divider, zero divider is divide by 1
    .short    0xFFFF        // [1e:1f] reserved
    // Fill to align with flash configuration field.
    .long     0xFFFFFFFF
    .long     0xFFFFFFFF
    .long     0xFFFFFFFF
    .long     0xFFFFFFFF
    .long     0xFFFFFFFF
    .long     0xFFFFFFFF
    .long     0xFFFFFFFF
    .long     0xFFFFFFFF        // Reserved for user TRIM value
#else        
    //Fill to align with flash configuration field.
    .long     0xFFFFFFFF
    .long     0xFFFFFFFF
    .long     0xFFFFFFFF
    .long     0xFFFFFFFF
    .long     0xFFFFFFFF
    .long     0xFFFFFFFF
    .long     0xFFFFFFFF
    .long     0xFFFFFFFF
    .long     0xFFFFFFFF
    .long     0xFFFFFFFF
    .long     0xFFFFFFFF
    .long     0xFFFFFFFF
    .long     0xFFFFFFFF
    .long     0xFFFFFFFF
    .long     0xFFFFFFFF
    .long     0xFFFFFFFF      // Reserved for user TRIM value
#endif  // BL_HAS_BOOTLOADER_CONFIG


/* Flash Configuration */
    .section .FlashConfig, "a"
    .long 0xFFFFFFFF
    .long 0xFFFFFFFF
    .long 0xFFFFFFFF
    .long 0xFFFF3DFE

    .text
    .thumb

/* Reset Handler */

    .thumb_func
    .align 2
    .globl   Reset_Handler
    .weak    Reset_Handler
    .type    Reset_Handler, %function
Reset_Handler:
    cpsid   i               /* Mask interrupts */
    .equ    VTOR, 0xE000ED08
    ldr     r0, =VTOR
    ldr     r1, =__isr_vector
    str     r1, [r0]
#ifndef __NO_SYSTEM_INIT
    ldr   r0,=SystemInit
    blx   r0
#endif
    ldr   r0,=init_data_bss
    blx   r0

    cpsie   i               /* Unmask interrupts */
#ifndef __START
#define __START _start
#endif
#ifndef __ATOLLIC__
    ldr   r0,=__START
    blx   r0
#else
    ldr   r0,=__libc_init_array
    blx   r0
    ldr   r0,=main
    bx    r0
#endif
    .pool
    .size Reset_Handler, . - Reset_Handler

    .align 1
    .thumb_func
    .weak DefaultISR
    .type DefaultISR, %function
DefaultISR:
    ldr r0, =DefaultISR
    bx r0
    .size DefaultISR, . - DefaultISR

    .align 1
    .thumb_func
    .weak DMA0_DMA4_IRQHandler
    .type DMA0_DMA4_IRQHandler, %function
DMA0_DMA4_IRQHandler:
    ldr   r0,=DMA0_DMA4_DriverIRQHandler
    bx    r0
    .size DMA0_DMA4_IRQHandler, . - DMA0_DMA4_IRQHandler

    .align 1
    .thumb_func
    .weak DMA1_DMA5_IRQHandler
    .type DMA1_DMA5_IRQHandler, %function
DMA1_DMA5_IRQHandler:
    ldr   r0,=DMA1_DMA5_DriverIRQHandler
    bx    r0
    .size DMA1_DMA5_IRQHandler, . - DMA1_DMA5_IRQHandler

    .align 1
    .thumb_func
    .weak DMA2_DMA6_IRQHandler
    .type DMA2_DMA6_IRQHandler, %function
DMA2_DMA6_IRQHandler:
    ldr   r0,=DMA2_DMA6_DriverIRQHandler
    bx    r0
    .size DMA2_DMA6_IRQHandler, . - DMA2_DMA6_IRQHandler

    .align 1
    .thumb_func
    .weak DMA3_DMA7_IRQHandler
    .type DMA3_DMA7_IRQHandler, %function
DMA3_DMA7_IRQHandler:
    ldr   r0,=DMA3_DMA7_DriverIRQHandler
    bx    r0
    .size DMA3_DMA7_IRQHandler, . - DMA3_DMA7_IRQHandler

    .align 1
    .thumb_func
    .weak DMA_Error_IRQHandler
    .type DMA_Error_IRQHandler, %function
DMA_Error_IRQHandler:
    ldr   r0,=DMA_Error_DriverIRQHandler
    bx    r0
    .size DMA_Error_IRQHandler, . - DMA_Error_IRQHandler

    .align 1
    .thumb_func
    .weak FLEXIO0_IRQHandler
    .type FLEXIO0_IRQHandler, %function
FLEXIO0_IRQHandler:
    ldr   r0,=FLEXIO0_DriverIRQHandler
    bx    r0
    .size FLEXIO0_IRQHandler, . - FLEXIO0_IRQHandler

    .align 1
    .thumb_func
    .weak SPI0_IRQHandler
    .type SPI0_IRQHandler, %function
SPI0_IRQHandler:
    ldr   r0,=SPI0_DriverIRQHandler
    bx    r0
    .size SPI0_IRQHandler, . - SPI0_IRQHandler

    .align 1
    .thumb_func
    .weak LPUART0_IRQHandler
    .type LPUART0_IRQHandler, %function
LPUART0_IRQHandler:
    ldr   r0,=LPUART0_DriverIRQHandler
    bx    r0
    .size LPUART0_IRQHandler, . - LPUART0_IRQHandler

    .align 1
    .thumb_func
    .weak LPUART1_IRQHandler
    .type LPUART1_IRQHandler, %function
LPUART1_IRQHandler:
    ldr   r0,=LPUART1_DriverIRQHandler
    bx    r0
    .size LPUART1_IRQHandler, . - LPUART1_IRQHandler

    .align 1
    .thumb_func
    .weak I2C0_IRQHandler
    .type I2C0_IRQHandler, %function
I2C0_IRQHandler:
    ldr   r0,=I2C0_DriverIRQHandler
    bx    r0
    .size I2C0_IRQHandler, . - I2C0_IRQHandler

    .align 1
    .thumb_func
    .weak QSPI0_IRQHandler
    .type QSPI0_IRQHandler, %function
QSPI0_IRQHandler:
    ldr   r0,=QSPI0_DriverIRQHandler
    bx    r0
    .size QSPI0_IRQHandler, . - QSPI0_IRQHandler


/*    Macro to define default handlers. Default handler
 *    will be weak symbol and just dead loops. They can be
 *    overwritten by other handlers */
    .macro def_irq_handler  handler_name
    .weak \handler_name
    .set  \handler_name, DefaultISR
    .endm

/* Exception Handlers */
    def_irq_handler    NMI_Handler
    def_irq_handler    HardFault_Handler
    def_irq_handler    SVC_Handler
    def_irq_handler    PendSV_Handler
    def_irq_handler    SysTick_Handler
    def_irq_handler    DMA0_DMA4_DriverIRQHandler
    def_irq_handler    DMA1_DMA5_DriverIRQHandler
    def_irq_handler    DMA2_DMA6_DriverIRQHandler
    def_irq_handler    DMA3_DMA7_DriverIRQHandler
    def_irq_handler    DMA_Error_DriverIRQHandler
    def_irq_handler    FLEXIO0_DriverIRQHandler
    def_irq_handler    TPM0_IRQHandler
    def_irq_handler    TPM1_IRQHandler
    def_irq_handler    TPM2_IRQHandler
    def_irq_handler    PIT0_IRQHandler
    def_irq_handler    SPI0_DriverIRQHandler
    def_irq_handler    EMVSIM0_IRQHandler
    def_irq_handler    LPUART0_DriverIRQHandler
    def_irq_handler    LPUART1_DriverIRQHandler
    def_irq_handler    I2C0_DriverIRQHandler
    def_irq_handler    QSPI0_DriverIRQHandler
    def_irq_handler    Reserved32_IRQHandler
    def_irq_handler    PORTA_IRQHandler
    def_irq_handler    PORTB_IRQHandler
    def_irq_handler    PORTC_IRQHandler
    def_irq_handler    PORTD_IRQHandler
    def_irq_handler    PORTE_IRQHandler
    def_irq_handler    LLWU_IRQHandler
    def_irq_handler    LTC0_IRQHandler
    def_irq_handler    USB0_IRQHandler
    def_irq_handler    ADC0_IRQHandler
    def_irq_handler    LPTMR0_IRQHandler
    def_irq_handler    RTC_Seconds_IRQHandler
    def_irq_handler    INTMUX0_0_IRQHandler
    def_irq_handler    INTMUX0_1_IRQHandler
    def_irq_handler    INTMUX0_2_IRQHandler
    def_irq_handler    INTMUX0_3_IRQHandler
    def_irq_handler    LPTMR1_IRQHandler
    def_irq_handler    Reserved49_IRQHandler
    def_irq_handler    Reserved50_IRQHandler
    def_irq_handler    Reserved51_IRQHandler
    def_irq_handler    SPI1_IRQHandler
    def_irq_handler    LPUART2_IRQHandler
    def_irq_handler    EMVSIM1_IRQHandler
    def_irq_handler    I2C1_IRQHandler
    def_irq_handler    TSI0_IRQHandler
    def_irq_handler    PMC_IRQHandler
    def_irq_handler    FTFA_IRQHandler
    def_irq_handler    MCG_IRQHandler
    def_irq_handler    WDOG_EWM_IRQHandler
    def_irq_handler    DAC0_IRQHandler
    def_irq_handler    TRNG0_IRQHandler
    def_irq_handler    Reserved63_IRQHandler
    def_irq_handler    CMP0_IRQHandler
    def_irq_handler    Reserved65_IRQHandler
    def_irq_handler    RTC_Alarm_IRQHandler
    def_irq_handler    Reserved67_IRQHandler
    def_irq_handler    Reserved68_IRQHandler
    def_irq_handler    Reserved69_IRQHandler
    def_irq_handler    Reserved70_IRQHandler
    def_irq_handler    Reserved71_IRQHandler
    def_irq_handler    DMA4_IRQHandler
    def_irq_handler    DMA5_IRQHandler
    def_irq_handler    DMA6_IRQHandler
    def_irq_handler    DMA7_IRQHandler
    def_irq_handler    Reserved76_IRQHandler
    def_irq_handler    Reserved77_IRQHandler
    def_irq_handler    Reserved78_IRQHandler
    def_irq_handler    Reserved79_IRQHandler

    .end
