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

#include "qspi.h"
#include "hw_def.h"

enum
{
    kStatus_Success = 0,
};

uint32_t rom_patch(qspi_config_t *base)
{
    volatile uint32_t *qspi_flshcr_reg = (volatile uint32_t *)K8x_QuadSPI0_FLSHCR_BASE;
    volatile uint32_t *qspi_soccr_reg = (volatile uint32_t *)K8x_QuadSPI0_SOCCR_BASE;

    // This means the device belongs to KL series, namely, KL8x
    uint32_t sim_sdid = *(volatile uint32_t *)SIM_SDID_BASE;
    if (sim_sdid & SIM_SDID_KL81_MASK)
    {
        qspi_flshcr_reg = (volatile uint32_t *)KL8x_QuadSPI0_FLSHCR_BASE;
        qspi_soccr_reg = (volatile uint32_t *)KL8x_QuadSPI0_SOCCR_BASE;
    }

    // Set QuadSPI_FLSHCR[TDH] to given value.
    *qspi_flshcr_reg &= (uint32_t)~QuadSPI0_FLSHCR_TDH_MASK;
    *qspi_flshcr_reg |= (base->data_hold_time) << QuadSPI0_FLSHCR_TDH_SHIFT;

    // Set QuadSPI_SOCCR[DLYTAPSELA] to given value
    *qspi_soccr_reg &= (uint32_t)~QuadSPI0_SOCCR_DLYTAPSELA_MASK;
    *qspi_soccr_reg |=
        (base->dqs_fa_delay_chain_sel << QuadSPI0_SOCCR_DLYTAPSELA_SHIFT) & QuadSPI0_SOCCR_DLYTAPSELA_MASK;
    // Set QuadSPI_SOCCR[DLYTAPSELB] to given value
    *qspi_soccr_reg &= (uint32_t)~QuadSPI0_SOCCR_DLYTAPSELB_MASK;
    *qspi_soccr_reg |=
        (base->dqs_fb_delay_chain_sel << QuadSPI0_SOCCR_DLYTAPSELB_SHIFT) & QuadSPI0_SOCCR_DLYTAPSELB_MASK;

    return kStatus_Success;
}
