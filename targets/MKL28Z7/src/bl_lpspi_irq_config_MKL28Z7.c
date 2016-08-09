/*
 * Copyright (c) 2014, Freescale Semiconductor, Inc.
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

#include "bootloader_config.h"
#include "bootloader/bl_peripheral_interface.h"
#include "fsl_device_registers.h"
#include "intmux/fsl_intmux.h"
#include "lpspi/fsl_lpspi.h"
#include "bootloader_common.h"
#include <assert.h>

////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////
static const IRQn_Type lpspi_irq_ids[FSL_FEATURE_SOC_LPSPI_COUNT] = {
    LPSPI0_IRQn, LPSPI1_IRQn, LPSPI2_IRQn,
};

void LPSPI_SetSystemIRQ(uint32_t instance, PeripheralSystemIRQSetting set)
{
    switch (instance)
    {
        case 2:
            if (set == kPeripheralEnableIRQ)
            {
                NVIC_EnableIRQ(INTMUX0_2_IRQn);
                // LPSPI2_IRQ is assigned to INTMUX, LPTMR1_IRQ is the first irq assigned to INTMUX.
                // So LPSPI2_IRQ id - LPTMR1_IRQ id is the index of LPSPI2_IRQ in INTMUX.
                INTMUX0->CHANNEL[2].CHn_IER_31_0 |= 1 << (lpspi_irq_ids[instance] - LPTMR1_IRQn);
            }
            else
            {
                NVIC_DisableIRQ(INTMUX0_2_IRQn);
                INTMUX0->CHANNEL[2].CHn_IER_31_0 &= ~(1 << (lpspi_irq_ids[instance] - LPTMR1_IRQn));
            }
            break;
        case 0:
        case 1:
            if (set == kPeripheralEnableIRQ)
            {
                NVIC_EnableIRQ(lpspi_irq_ids[instance]);
            }
            else
            {
                NVIC_DisableIRQ(lpspi_irq_ids[instance]);
            }
            break;
    }
}

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
