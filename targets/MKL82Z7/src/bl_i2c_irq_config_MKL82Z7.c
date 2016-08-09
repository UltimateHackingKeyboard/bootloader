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

#include "bootloader/bl_context.h"
#include "bootloader_common.h"
#include "bootloader_config.h"
#include "target_config.h"
#include "bootloader/bl_irq_common.h"
#include "autobaud/autobaud.h"
#include "packet/serial_packet.h"
#include "fsl_device_registers.h"
#include "i2c/fsl_i2c.h"
#include "intmux/fsl_intmux.h"
#include "utilities/fsl_assert.h"

static const IRQn_Type i2c_irq_ids[FSL_FEATURE_SOC_I2C_COUNT] = {
    I2C0_IRQn, I2C1_IRQn,
};

void I2C_SetSystemIRQ(uint32_t instance, PeripheralSystemIRQSetting set)
{
    switch (instance)
    {
        case 1:
        {
            uint32_t intmux_offset = (uint32_t)i2c_irq_ids[1] - FSL_FEATURE_INTMUX_IRQ_START_INDEX;
            if (set == kPeripheralEnableIRQ)
            {
                NVIC_EnableIRQ(INTMUX0_1_IRQn);
                INTMUX0->CHANNEL[1].CHn_IER_31_0 |= 1 << (intmux_offset);
            }
            else
            {
                NVIC_DisableIRQ(INTMUX0_1_IRQn);
                INTMUX0->CHANNEL[1].CHn_IER_31_0 &= ~(1 << (intmux_offset));
            }
        }
        break;
// Note: I2C0 is not supported in KL80 ROM.
#if 0
    case 0:
        if (set == kPeripheralEnableIRQ)
        {
            NVIC_EnableIRQ(i2c_irq_ids[instance]);
        }
        else
        {
            NVIC_DisableIRQ(i2c_irq_ids[instance]);
        }
        break;
#endif //
    }
}

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
