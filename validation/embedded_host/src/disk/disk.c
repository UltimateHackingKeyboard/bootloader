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

#include "disk.h"

#include "fsl_device_registers.h"
#include "board.h"
#include "usb_msd_disk.h"
#include "fat_directory_entry.h"
#include "utilities/fsl_rtos_abstraction.h"
#include "blsh/blsh.h"

#include <stdio.h>
#include <stdlib.h>

#if defined(USB_DEVICE_CONFIG_EHCI) && (USB_DEVICE_CONFIG_EHCI > 0)
#include "usb_phy.h"
#endif

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
  * Prototypes
  ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
/* Data structure of msc device, store the information ,such as class handle */
usb_msc_struct_t g_msc;

//! @brief Messages corresponding to the various transfer statuses.
static const char *const kStatusMessages[] = {
    "Ready\r\n",        // kReadyStatus
    "Transferring\r\n", // kTransferringStatus
    "Success\r\n",      // kSuccessStatus
    "Failure\r\n"       // kFailureStatus
};
//! @brief Status values for SB tranfsers.
typedef enum _sb_transfer_status
{
    kReadyStatus = 0,
    kTransferringStatus,
    kSuccessStatus,
    kFailureStatus
} sb_transfer_status_t;
//! @brief Various constants for the MSD peripheral.
enum _usb_msd_constants
{
    //! Number of sector buffers we use.
    kNumberOfSectorBuffers = 2,

    //! Value used to indicate that the #usb_msd_state_t::lastBufferReadIndex is unset.
    kInvalidBufferReadIndex = ~0
};

//! @brief The various states that a sector buffer can be in.
typedef enum _sector_buffer_status
{
    kBufferFree = 0, //!< Buffer contains no data.
    kBufferPending,  //!< A write is pending for this buffer.
    kBufferFilled,   //!< Buffer has data that is waited to be processed.
    kBufferInUse     //!< The buffer's data is being processed by the sbloader.
} sector_buffer_status_t;
//! @brief State information for the USB MSD peripheral.
//!
//! The sector buffers come first so they will be word aligned.
typedef struct _usb_msd_state
{
    uint32_t start_app;
    uint8_t buffer[kDiskSectorSize];   //!< Generic buffer.
    uint8_t sbBuffer[kDiskSectorSize]; //!< Buffer to hold SB file sectors
    uint8_t isDiskLocked;
    uint8_t read_write_error;
    uint8_t isActive;         //!< Set to true when the first SB file is transferred.
    uint8_t isTransferring;   //!< Whether an SB file transfer has been started.
    uint8_t isLoaderInited;   //!< Flag to indicate that the SB loader has been initialized.
    uint8_t isProcessing;     //!< Set to true while the SB file is being processed.
    uint8_t isReceivePending; //!< Whether a sector write is being held off until a buffer is free.
    uint32_t infoFileLength;  //!< Size in bytes of the info.txt file.
    uint32_t nextSector;      //!< The next expected sector write for the SB file transfer.
    //    uint32_t nextBufferWriteIndex;       //!< The next sector buffer index to write into. Toggles between 0 and 1.
    //    uint32_t lastBufferReadIndex;        //!< The last sector buffer index that was read from. Toggles between 0
    //    and 1.
    uint32_t remainingFileLength;        //!< Total length in bytes of the SB file being transferred.
    uint32_t dataBytesAvailable;         //!< Number of bytes available in sectorBuffer.
    sb_transfer_status_t transferStatus; //!< Status to present in the status.txt file.
} usb_msd_state_t;

//! @brief Format for contents of the info.txt file.
static const char kInfoFileFormat[] =
    "Embedded Host %c%d.%d.%d\r\n"
    "\r\n"
    "Host Board: %s\r\n"
    "CPU clock: %u MHz\r\n"
    "Flash size: %u bytes\r\n"
    "Flash range: %s-%s\r\n"
    "RAM size: %u bytes\r\n"
    "RAM range: %s-%s\r\n"
    "Peripheral supported: %s\r\n";

static uint8_t msc_bulk_out_buff[USB_DEVICE_MSC_WRITE_BUFF_SIZE];
static uint8_t msc_bulk_in_buff[USB_DEVICE_MSC_READ_BUFF_SIZE];
static uint32_t s_sector_address = MSD_FLASH_BASE;

flash_config_t s_flashInstance = { P_FLASH_BASE, /*! Base address of PFlash block */
                                   P_FLASH_SIZE, /*! Size of PFlash block */
                                   0x4,          P_SECTOR_SIZE, 0, 0x8000, 0x40, 0, 0x14000000, 0x1000, 0, 0, 0 };

//! @brief Current state of the USB MSD disk.
static usb_msd_state_t s_diskState;
static usb_status_t usb_msd_write_sector(uint32_t sector, const usb_device_lba_app_struct_t *lbaData);
static usb_status_t usb_msd_read_sector(uint32_t sector, usb_device_lba_app_struct_t *lbaData);
static void error_trap(void);
static void usb_msd_update_info_file(uint8_t *buffer);
/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * @brief device msc callback function.
 *
 * This function handle the disk class specified event.
 * @param handle          The USB class  handle.
 * @param event           The USB device event type.
 * @param param           The parameter of the class specific event.
 * @return kStatus_USB_Success or error.
 */
usb_status_t USB_DeviceMscCallback(class_handle_t handle, uint32_t event, void *param)
{
    usb_status_t error = kStatus_USB_Error;
    usb_device_lba_information_struct_t *lbaInformationStructure;
    usb_device_lba_app_struct_t *lbaData;
    uint32_t sector = 0;
    uint32_t result;

    switch (event)
    {
        case kUSB_DeviceMscEventReadResponse:
            lbaData = (usb_device_lba_app_struct_t *)param;

            if (lbaData != NULL)
            {
                sector = lbaData->offset / kDiskSectorSize;
                error = usb_msd_read_sector(sector, lbaData);
            }

            break;
        case kUSB_DeviceMscEventWriteResponse:
            lbaData = (usb_device_lba_app_struct_t *)param;

            /* Write flash */
            if (lbaData != NULL)
            {
                sector = lbaData->offset / kDiskSectorSize;
                error = usb_msd_write_sector(sector, lbaData);
            }
            break;
        case kUSB_DeviceMscEventWriteRequest:
            lbaData = (usb_device_lba_app_struct_t *)param;
            /*offset is the write start address get from write command, refer to class driver*/
            lbaData->buffer = g_msc.storageDisk + lbaData->offset;
            if (lbaData != NULL)
            {
                lbaData->buffer = (uint8_t *)msc_bulk_out_buff;
            }
            break;
        case kUSB_DeviceMscEventReadRequest:
            lbaData = (usb_device_lba_app_struct_t *)param;
            /*offset is the read start address get from read command, refer to class driver*/
            // lbaData->buffer = g_msc.storageDisk + lbaData->offset;
            if (lbaData != NULL)
            {
                lbaData->buffer = (uint8_t *)msc_bulk_in_buff;
            }
            sector = lbaData->offset / kDiskSectorSize;
            error = usb_msd_read_sector(sector, lbaData);
            break;
        case kUSB_DeviceMscEventGetLbaInformation:
            lbaInformationStructure = (usb_device_lba_information_struct_t *)param;
            lbaInformationStructure->totalLbaNumberSupports = kDiskTotalLogicalBlocks;
            lbaInformationStructure->lengthOfEachLba = kDiskSectorSize;
            lbaInformationStructure->logicalUnitNumberSupported = kDiskLogicalUnits;
            lbaInformationStructure->bulkInBufferSize = USB_DEVICE_MSC_WRITE_BUFF_SIZE;
            lbaInformationStructure->bulkOutBufferSize = USB_DEVICE_MSC_READ_BUFF_SIZE;
            break;
        case kUSB_DeviceMscEventFormatComplete:
            break;
        case kUSB_DeviceMscEventRemovalRequest:

            break;
    }
    return error;
}

/*!
 * @brief device callback function.
 *
 * This function handle the usb standard event. more information, please refer to usb spec chapter 9.
 * @param handle          The USB device handle.
 * @param event           The USB device event type.
 * @param param           The parameter of the device specific request.
 * @return kStatus_USB_Success or error.
 */
usb_status_t USB_DeviceCallback(usb_device_handle handle, uint32_t event, void *param)
{
    usb_status_t error = kStatus_USB_Success;
    uint16_t *temp16 = (uint16_t *)param;
    uint8_t *temp8 = (uint8_t *)param;
    switch (event)
    {
        case kUSB_DeviceEventBusReset:
        {
            g_msc.attach = 0;
            error = kStatus_USB_Success;
#if defined(USB_DEVICE_CONFIG_EHCI) && (USB_DEVICE_CONFIG_EHCI > 0)
            if (kStatus_USB_Success == USB_DeviceClassGetSpeed(CONTROLLER_ID, &g_msc.speed))
            {
                USB_DeviceSetSpeed(handle, g_msc.speed);
            }
#endif
        }
        break;
        case kUSB_DeviceEventSetConfiguration:
            if (param)
            {
                g_msc.attach = 1;
                g_msc.currentConfiguration = *temp8;
            }
            break;
        case kUSB_DeviceEventSetInterface:
            if (g_msc.attach)
            {
                uint8_t interface = (uint8_t)((*temp16 & 0xFF00U) >> 0x08U);
                uint8_t alternateSetting = (uint8_t)(*temp16 & 0x00FFU);
                if (interface < USB_MSC_INTERFACE_COUNT)
                {
                    g_msc.currentInterfaceAlternateSetting[interface] = alternateSetting;
                }
            }
            break;
        case kUSB_DeviceEventGetConfiguration:
            if (param)
            {
                *temp8 = g_msc.currentConfiguration;
                error = kStatus_USB_Success;
            }
            break;
        case kUSB_DeviceEventGetInterface:
            if (param)
            {
                uint8_t interface = (uint8_t)((*temp16 & 0xFF00U) >> 0x08U);
                if (interface < USB_INTERFACE_COUNT)
                {
                    *temp16 = (*temp16 & 0xFF00U) | g_msc.currentInterfaceAlternateSetting[interface];
                    error = kStatus_USB_Success;
                }
                else
                {
                    error = kStatus_USB_InvalidRequest;
                }
            }
            break;
        case kUSB_DeviceEventGetDeviceDescriptor:
            if (param)
            {
                error = USB_DeviceGetDeviceDescriptor(handle, (usb_device_get_device_descriptor_struct_t *)param);
            }
            break;
        case kUSB_DeviceEventGetConfigurationDescriptor:
            if (param)
            {
                error = USB_DeviceGetConfigurationDescriptor(handle,
                                                             (usb_device_get_configuration_descriptor_struct_t *)param);
            }
            break;
        case kUSB_DeviceEventGetStringDescriptor:
            if (param)
            {
                error = USB_DeviceGetStringDescriptor(handle, (usb_device_get_string_descriptor_struct_t *)param);
            }
            break;
        default:
            break;
    }
    return error;
}
/* USB device class information */
usb_device_class_config_struct_t msc_config[1] = { {
    USB_DeviceMscCallback, 0, &g_UsbDeviceMscConfig,
} };
/* USB device class configuraion information */
usb_device_class_config_list_struct_t msc_config_list = {
    msc_config, USB_DeviceCallback, 1,
};
/*!
 * @brief USB Interrupt service routine.
 *
 * This function serves as the USB interrupt service routine.
 *
 * @return None.
 */
#if defined(USB_DEVICE_CONFIG_EHCI) && (USB_DEVICE_CONFIG_EHCI > 0)
void USBHS_IRQHandler(void)
{
    USB_DeviceEhciIsrFunction(g_msc.deviceHandle);
}
#endif
#if defined(USB_DEVICE_CONFIG_KHCI) && (USB_DEVICE_CONFIG_KHCI > 0)
void USB0_IRQHandler(void)
{
    USB_DeviceKhciIsrFunction(g_msc.deviceHandle);
}
#endif

/*!
 * @brief device callback function.
 *
 * This function init the usb stack and sdhc driver.
 *
 * @return None.
 */
void disk_init(void)
{
    uint8_t irq_no;
#if defined(USB_DEVICE_CONFIG_EHCI) && (USB_DEVICE_CONFIG_EHCI > 0)
    uint8_t ehci_irq[] = USBHS_IRQS;
    irq_no = ehci_irq[CONTROLLER_ID - kUSB_ControllerEhci0];

    USB_EhciPhyInit(CONTROLLER_ID, BOARD_XTAL0_CLK_HZ);
#endif
#if defined(USB_DEVICE_CONFIG_KHCI) && (USB_DEVICE_CONFIG_KHCI > 0)
    uint8_t khci_irq[] = USB_IRQS;
    irq_no = khci_irq[CONTROLLER_ID - kUSB_ControllerKhci0];

    SystemCoreClockUpdate();
    usb_clock_init();
#endif

/*
 * If the SOC has USB KHCI dedicated RAM, the RAM memory needs to be clear after
 * the KHCI clock is enabled. When the demo uses USB EHCI IP, the USB KHCI dedicated
 * RAM can not be used and the memory can't be accessed.
 */
#if (defined(FSL_FEATURE_USB_KHCI_USB_RAM) && (FSL_FEATURE_USB_KHCI_USB_RAM > 0U))
#if (defined(FSL_FEATURE_USB_KHCI_USB_RAM_BASE_ADDRESS) && (FSL_FEATURE_USB_KHCI_USB_RAM_BASE_ADDRESS > 0U))
    for (uint32_t i = 0; i < FSL_FEATURE_USB_KHCI_USB_RAM; i++)
    {
        ((uint8_t *)FSL_FEATURE_USB_KHCI_USB_RAM_BASE_ADDRESS)[i] = 0x00U;
    }
#endif /* FSL_FEATURE_USB_KHCI_USB_RAM_BASE_ADDRESS */
#endif /* FSL_FEATURE_USB_KHCI_USB_RAM */

    g_msc.speed = USB_SPEED_FULL;
    g_msc.attach = 0;
    g_msc.mscHandle = (class_handle_t)NULL;
    g_msc.deviceHandle = NULL;

    // Get info file length
    usb_msd_update_info_file(s_diskState.buffer);
    s_diskState.infoFileLength = strlen((char *)s_diskState.buffer);

    if (kStatus_USB_Success != USB_DeviceClassInit(CONTROLLER_ID, &msc_config_list, &g_msc.deviceHandle))
    {
        // usb_echo("USB device init failed\r\n");
    }
    else
    {
        // usb_echo("USB device mass storage demo\r\n");
        g_msc.mscHandle = msc_config_list.config->classHandle;
    }

    NVIC_SetPriority((IRQn_Type)irq_no, USB_DEVICE_INTERRUPT_PRIORITY);
    NVIC_EnableIRQ((IRQn_Type)irq_no);

    USB_DeviceRun(g_msc.deviceHandle);
}

usb_status_t usb_msd_read_sector(uint32_t sector, usb_device_lba_app_struct_t *lbaData)
{
    // Clear the sector contents (all zeroes).
    memset(lbaData->buffer, 0, lbaData->size);

    // Search for a sector entry in our table.
    const sector_info_t *sectorInfo = g_msdDiskSectors;
    for (; sectorInfo->data; ++sectorInfo)
    {
        if (sectorInfo->sector == sector)
        {
            // Copy sector data into output buffer.
            memcpy(lbaData->buffer, sectorInfo->data, sectorInfo->length);
            break;
        }
    }

    // Special handling for certain sectors.
    switch (sector)
    {
        case kPbsSector:
            // Fill in signature bytes for PBS, so we don't have to have the full 512 bytes as const data.
            lbaData->buffer[510] = 0x55;
            lbaData->buffer[511] = 0xaa;
            break;

        case kRootDir1Sector:
        {
            // Update info.txt and status.txt file sizes in root directory.
            fat_directory_entry_t *rootDir = (fat_directory_entry_t *)lbaData->buffer;

            rootDir[kInfoFileDirEntry].entry.fileSize = s_diskState.infoFileLength;

            const char *statusMessage = kStatusMessages[s_diskState.transferStatus];
            rootDir[kStatusFileDirEntry].entry.fileSize = strlen(statusMessage);

            break;
        }

        case kInfoFileSector:
            usb_msd_update_info_file(lbaData->buffer);
            break;

        case kStatusFileSector:
        {
            const char *statusMessage = kStatusMessages[s_diskState.transferStatus];
            uint32_t statusLength = strlen(statusMessage);
            memcpy(lbaData->buffer, statusMessage, statusLength);
            break;
        }
    }

    return kStatus_USB_Success;
}

usb_status_t usb_msd_write_sector(uint32_t sector, const usb_device_lba_app_struct_t *lbaData)
{
    uint32_t regPrimask = 0U;
    // The 27th sector is image data start address
    uint32_t image_start_sector = kFirstUnusedSector + 3;

    if (sector >= image_start_sector)
    {
        /* Disable IRQ, protect ring buffer. */
        regPrimask = __get_PRIMASK();
        __disable_irq();

        if (kStatus_FLASH_Success != FLASH_Program(&s_flashInstance,
                                                   s_sector_address + (sector - image_start_sector) * kDiskSectorSize,
                                                   (void *)msc_bulk_out_buff, USB_DEVICE_MSC_WRITE_BUFF_SIZE))
        {
            error_trap();
        }

        /* Recover PRIMASK, enable IRQ if previously enabled. */
        __set_PRIMASK(regPrimask);
    }

    return kStatus_USB_Success;
}

static void usb_msd_update_info_file(uint8_t *buffer)
{
    /* Format embedded host info for TWR-K65 */
    sprintf((char *)buffer, kInfoFileFormat, 'E', 1, 0, 0, "TWR-K65F180M", 120, 2097152, "0x00000000", "0x00200000",
            262144, "0x1fff0000", "0x2002ffff", "SPI, I2C, UART, CAN");
}

/*
* @brief Gets called when an error occurs.
* Print error message and trap forever.
*/
static void error_trap(void)
{
    blsh_printf("\r\nFlash program error!");
}
