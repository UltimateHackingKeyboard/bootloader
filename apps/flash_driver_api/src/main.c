/*
 * Copyright (c) 2014-2016, Freescale Semiconductor, Inc.
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

#include <stdint.h>
#include <stdio.h>
#include "application_common.h"
#include "fsl_flash.h"

////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////
#define TEST_ERASE_SECTOR_START_ADDRESSS 0x4000u
#define FLASH_ERASE_SIZE 0x400

#define BOOTLOADER_TREE_LOCATION (0x1c00001cul)

typedef union BootloaderVersion
{
    struct
    {
        uint32_t bugfix : 8; //!< bugfix version [7:0]
        uint32_t minor : 8;  //!< minor version [15:8]
        uint32_t major : 8;  //!< major version [23:16]
        uint32_t name : 8;   //!< name [31:24]
    } B;
    uint32_t version; //!< combined version numbers
} standard_version_t;

////////////////////////////////////////////////////////////////////////////////
// Prototypes
////////////////////////////////////////////////////////////////////////////////
static void flash_driver_api_tree_demo(void);
static void verify_status(status_t status);

////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////
const uint32_t test_program_buffer[2] = { 0x01234567, 0x89abcdef };

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////

int main()
{
    // Initialize hardware
    init_hardware();
    // Initialize terminal uart
    init_term_uart();

    // Run flash driver api tree demo.
    flash_driver_api_tree_demo();

    while (1)
    {
    }
}

void flash_driver_api_tree_demo(void)
{
    flash_config_t flashInstance;
    // Print basic information for Flash Driver API.
    printf("\r\nFlash driver API tree Demo Application...\r\n");
    printf("Getting bootloader tree location from address 0x%X\r\n", BOOTLOADER_TREE_LOCATION);
    standard_version_t flashDriverVersion;
    // Initialize flash driver
    printf("Initializing flash driver...\r\n");
    if (FLASH_Init(&flashInstance) == kStatus_Success)
    {
        uint32_t value;
        status_t status;
        uint32_t *failedAddress = 0;
        uint32_t *failedData = 0;

        printf("Done!\r\n");

        // Get flash properties
        printf("Flash Properties:\r\n");
        FLASH_GetProperty(&flashInstance, kFLASH_PropertyVersion, &flashDriverVersion.version);
        printf("\tkFLASH_PropertyVersion = %c%d.%d.%d\r\n", flashDriverVersion.B.name, flashDriverVersion.B.major,
               flashDriverVersion.B.minor, flashDriverVersion.B.bugfix);
        FLASH_GetProperty(&flashInstance, kFLASH_PropertyPflashSectorSize, &value);
        printf("\tkFLASH_PropertyPflashSectorSize = %d\r\n", value);
        FLASH_GetProperty(&flashInstance, kFLASH_PropertyPflashTotalSize, &value);
        printf("\tkFLASH_PropertyPflashTotalSize = %d\r\n", value);
        FLASH_GetProperty(&flashInstance, kFLASH_PropertyPflashBlockBaseAddr, &value);
        printf("\tkFLASH_PropertyPflashBlockBaseAddr = 0x%X\r\n", value);
        status = FLASH_GetProperty(&flashInstance, kFLASH_PropertyPflashFacSupport, &value);
        if (status == kStatus_Success)
        {
            printf("\tkFLASH_PropertyPflashFacSupport = 0x%x\r\n", value);
        }
        else
        {
            printf("\tProperty: kFLASH_PropertyPflashFacSupport is not supported.\r\n");
        }
        status = FLASH_GetProperty(&flashInstance, kFLASH_PropertyPflashAccessSegmentSize, &value);
        if (status == kStatus_Success)
        {
            printf("\tkFLASH_PropertyPflashAccessSegmentSize = 0x%x\r\n", value);
        }
        else
        {
            printf("\tProperty: kFLASH_PropertyPflashAccessSegmentSize is not supported.\r\n");
        }

        FLASH_GetProperty(&flashInstance, kFLASH_PropertyPflashAccessSegmentCount, &value);
        if (status == kStatus_Success)
        {
            printf("\tkFLASH_PropertyPflashAccessSegmentCount = 0x%x\r\n", value);
        }
        else
        {
            printf("\tProperty: kFLASH_PropertyPflashAccessSegmentCount is not supported.\r\n");
        }

        // Erase a given flash range
        printf("\r\nCalling FLASH_Erase() API...\r\n");
        status = FLASH_Erase(&flashInstance, TEST_ERASE_SECTOR_START_ADDRESSS, FLASH_ERASE_SIZE, kFLASH_ApiEraseKey);
        verify_status(status);

        // Verify if the given flash range is successfully erased.
        printf("Calling FLASH_VerifyErase() API...\r\n");
        status = FLASH_VerifyErase(&flashInstance, TEST_ERASE_SECTOR_START_ADDRESSS, FLASH_ERASE_SIZE,
                                   kFLASH_MarginValueUser);
        verify_status(status);

        // Start programming specified flash region
        printf("Calling FLASH_Program() API...\r\n");
        status = FLASH_Program(&flashInstance, TEST_ERASE_SECTOR_START_ADDRESSS, (uint32_t *)test_program_buffer, 8);
        verify_status(status);

        // Verify if the given flash region is successfully programmed with given data
        printf("Calling FLASH_VerifyProgram() API...\r\n");
        status = FLASH_VerifyProgram(&flashInstance, TEST_ERASE_SECTOR_START_ADDRESSS, 8, test_program_buffer,
                                     kFLASH_MarginValueUser, failedAddress, failedData);
        verify_status(status);

        // Start perform flash_register_callback API
        printf("Calling FLASH_SetCallback() API ...\r\n");
        status = FLASH_SetCallback(&flashInstance, NULL);
        verify_status(status);

        // Start Program specified Program Once Field
        /*
        Note: Because the Program Once Field is only support being programmed once,
        Please uncomment follow codes if you are aware of the result.
        */
        //        uint32_t temp = 0x12345678;
        //        printf("Calling FLASH_ProgramOnce() API ...\r\n");
        //        status = FLASH_ProgramOnce(&flashInstance, 0, &temp, sizeof(temp));
        //        verify_status(status);

        // Start Read specified Program Once Field

        uint32_t readData[2];
        printf("Calling FLASH_ReadOnce() API ...\r\n");
        status = FLASH_ReadOnce(&flashInstance, 0, &readData[0], sizeof(uint32_t));
        verify_status(status);

        // Start running flash_read_resource API
        printf("Calling FLASH_ReadResource() API ...\r\n");
        status = FLASH_ReadResource(&flashInstance, 0, &readData[0], 8, kFLASH_ResourceOptionVersionId);
        verify_status(status);
        if (status == kStatus_Success)
        {
            printf("Data read from Flash IFR Field: 0x%08x, 0x%08x\r\n", readData[0], readData[1]);
        }
    }
    else
    {
        printf("Flash init failure. Halting...\r\n");
    }

    printf("Done!\r\n");
}

void verify_status(status_t status)
{
    char *tipString = "Unknown status";
    switch (status)
    {
        case kStatus_Success:
            tipString = "Done.";
            break;
        case kStatus_InvalidArgument:
            tipString = "Invalid argument.";
            break;
        case kStatus_FLASH_AlignmentError:
            tipString = "Alignment Error.";
            break;
        case kStatus_FLASH_AccessError:
            tipString = "Flash Access Error.";
            break;
        case kStatus_FLASH_CommandNotSupported:
            tipString = "This API is not supported in current target.";
            break;
        default:
            break;
    }
    printf("%s\r\n\r\n", tipString);
}

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
