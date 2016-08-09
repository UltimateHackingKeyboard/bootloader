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
#include "lpspi/fsl_lpspi_slave_driver.h"
#include "lpspi/hal/fsl_lpspi_hal.h"
#include "bootloader_common.h"
#include "intmux/intmux_driver.h"
#include <assert.h>

////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////
static const IRQn_Type lpspi_irq_ids[LPSPI_INSTANCE_COUNT] = {
    LPSPI0_IRQn,
#if (LPSPI_INSTANCE_COUNT > 1)
    LPSPI1_IRQn,
#endif // #if (LPSPI_INSTANCE_COUNT > 1)
#if (LPSPI_INSTANCE_COUNT > 2)
    LPSPI2_IRQn,
#endif // #if (LPSPI_INSTANCE_COUNT > 2)
};

void lpspi_set_system_IRQ_gate(uint32_t instance, PeripheralSystemIRQSetting set)
{
    switch (instance)
    {
        case 0:
#if (LPI2C_INSTANCE_COUNT > 1)
        case 1:
#endif // #if (LPI2C_INSTANCE_COUNT > 1)
            if (set == kPeripheralEnableIRQ)
            {
                NVIC_EnableIRQ(lpspi_irq_ids[instance]);
            }
            else
            {
                NVIC_DisableIRQ(lpspi_irq_ids[instance]);
            }
            break;
#if (LPI2C_INSTANCE_COUNT > 2)
        case 2:
            uint32_t lpspi_intmux_offset = (uint32_t)lpspi_irq_ids[instance] - FSL_FEATURE_INTMUX_IRQ_START_INDEX;
            if (set == kPeripheralEnableIRQ)
            {
                NVIC_EnableIRQ(INTMUX0_2_IRQn);
                INTMUX_EnableInterrupt(INTMUX0_INSTANCE, kIntmuxChannel2, 1 << lpspi_intmux_offset);
            }
            else
            {
                NVIC_DisableIRQ(INTMUX0_2_IRQn);
                INTMUX_DisableInterrupt(INTMUX0_INSTANCE, kIntmuxChannel2, 1 << lpspi_intmux_offset);
            }
            break;

#endif // #if (LPI2C_INSTANCE_COUNT > 2)
    }
}

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
