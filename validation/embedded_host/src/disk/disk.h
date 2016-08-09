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

#ifndef __USB_DISK_H__
#define __USB_DISK_H__ 1

#include "usb_device_config.h"
#include "usb.h"
#include "usb_device.h"
#include "usb_device_class.h"
#include "usb_device_msc.h"
#include "usb_device_ch9.h"
#include "usb_descriptor.h"
#include "flash/fsl_flash.h"
#include "executable_image.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#if defined(USB_DEVICE_CONFIG_EHCI) && (USB_DEVICE_CONFIG_EHCI > 0)
#define CONTROLLER_ID kUSB_ControllerEhci0
#endif
#if defined(USB_DEVICE_CONFIG_KHCI) && (USB_DEVICE_CONFIG_KHCI > 0)
#define CONTROLLER_ID kUSB_ControllerKhci0
#endif

#define USB_DEVICE_INTERRUPT_PRIORITY (4)

/* Length of Each Logical Address Block */
#define LENGTH_OF_EACH_LBA (512)
/* total number of logical blocks present */
#define TOTAL_LOGICAL_ADDRESS_BLOCKS_NORMAL (48)
/* Net Disk Size , default disk is 48*512, that is 24kByte, however , the disk reconnised by that PC only has 4k Byte,
 * This is caused by that the file system also need memory*/
#define DISK_SIZE_NORMAL (TOTAL_LOGICAL_ADDRESS_BLOCKS_NORMAL * LENGTH_OF_EACH_LBA)

#define LOGICAL_UNIT_SUPPORTED (1U)

#define USB_DEVICE_MSC_WRITE_BUFF_NUM 2
#define USB_DEVICE_MSC_WRITE_BUFF_SIZE 512
#define USB_DEVICE_MSC_READ_BUFF_SIZE 512
#define MSD_FLASH_BASE IMAGE_START_ADDRESS

// Program Flash block information
#define P_FLASH_BASE 0x00000000
#define P_FLASH_SIZE (FSL_FEATURE_FLASH_PFLASH_BLOCK_SIZE * FSL_FEATURE_FLASH_PFLASH_BLOCK_COUNT)
#define P_BLOCK_NUM FSL_FEATURE_FLASH_PFLASH_BLOCK_COUNT
#define P_SECTOR_SIZE FSL_FEATURE_FLASH_PFLASH_BLOCK_SECTOR_SIZE

typedef struct _usb_msc_struct
{
    usb_device_handle deviceHandle;
    class_handle_t mscHandle;
    uint8_t storageDisk[DISK_SIZE_NORMAL];
    uint8_t diskLock;
    uint8_t read_write_error;
    uint8_t currentConfiguration;
    uint8_t currentInterfaceAlternateSetting[USB_MSC_INTERFACE_COUNT];
    uint8_t speed;
    uint8_t attach;
} usb_msc_struct_t;

extern flash_config_t s_flashInstance;

/*******************************************************************************
 * API
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

void disk_init(void);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif
