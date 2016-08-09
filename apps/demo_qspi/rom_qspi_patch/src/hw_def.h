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
#ifndef __HW_DEF_H__
#define __HW_DEF_H__

// Note: the FAMILYID for K8x is 0x08 while it is 0x09 for KL8x.
// So use the least-significant bit to distiguish K8x from KL8x.
#define SIM_SDID_BASE (0x40048024ul)
#define SIM_SDID_KL81_MASK (0x10000000ul)
#define K8x_QuadSPI0_FLSHCR_BASE (0x400da00cul)
#define KL8x_QuadSPI0_FLSHCR_BASE (0x4005a00cul)
#define QuadSPI0_FLSHCR_TDH_MASK (0x00030000ul)
#define QuadSPI0_FLSHCR_TDH_SHIFT (16)

#define K8x_QuadSPI0_SOCCR_BASE (0x400DA024ul)
#define KL8x_QuadSPI0_SOCCR_BASE (0x4005A024ul)
#define QuadSPI0_SOCCR_DLYTAPSELA_SHIFT (16)
#define QuadSPI0_SOCCR_DLYTAPSELA_MASK (0x003F0000ul)
#define QuadSPI0_SOCCR_DLYTAPSELB_SHIFT (24)
#define QuadSPI0_SOCCR_DLYTAPSELB_MASK (0x3F000000ul)

#endif // #ifndef __HW_DEF_H__
