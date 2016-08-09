/*
 * Copyright (c) 2013, Freescale Semiconductor, Inc.
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
#if !defined(_USB_MSD_DISK_H_)
#define _USB_MSD_DISK_H_

//#include "bootloader_common.h"
#include "fsl_common.h"

//! @addtogroup usb_msd_disk
//! @{

/*******************************************************************************
 * Definitions
 ******************************************************************************/

//! @name Data format macros
//@{
//! @brief Format a 32-bit little endian word as four bytes separated by commas.
#define U32_LE(n) ((n)&0xff), (((n) >> 8) & 0xff), (((n) >> 16) & 0xff), (((n) >> 24) & 0xff)

//! @brief Format a 16-bit little endian half-word as two bytes separated by commas.
#define U16_LE(n) ((n)&0xff), (((n) >> 8) & 0xff)
//@}

//! @brief Disk related constants.
enum _disk_constants
{
    kDiskSectorSize = 512,                                        //!< Size in bytes of each sector of the disk.
    kDiskTotalLogicalBlocks = 2048,                               //!< Total number of sectors in the disk.
    kDiskSizeInBytes = kDiskTotalLogicalBlocks * kDiskSectorSize, //!< Size in bytes of the total disk.
    kDiskLogicalUnits = 1,                                        //!< Number of SCSI LUNs.
    kDiskHeaderSectorCount = 1,                                   //!< PBS
    kDiskFat16EntrySize = 2,                                      //!< Two bytes per FAT16 entry.
    kDiskClusterSize = 1,                                         //!< Number of sectors per cluster.
    kDiskDataClusterCount = (kDiskTotalLogicalBlocks - kDiskHeaderSectorCount) / kDiskClusterSize,
    kDiskSectorsPerFat = (kDiskDataClusterCount * kDiskFat16EntrySize + kDiskSectorSize - 1) /
                         kDiskSectorSize, //!< Number of sectors occupied by each FAT, rounded up.
};

//! @brief Sector number constants.
enum _sector_numbers
{
    kPbsSector = 0,                                     //!< Partition Boot Sector
    kFat1Sector = kPbsSector + 1,                       //!< FAT1
    kFat2Sector = kFat1Sector + kDiskSectorsPerFat,     //!< FAT2 (unused)
    kRootDir1Sector = kFat2Sector + kDiskSectorsPerFat, //!< Root directory 1 (16 x 32-byte entries)
    kRootDir2Sector,                                    //!< Root directory 2 (16 x 32-byte entries)
    kMacFseventsdDirSector,                             //!< Mac OS X '.fseventsd' directory
    kWindowsSysVolInfoDirSector,                        //!< Windows 8.1 'System Volume Information' directory
    kWindowsIndexerVolumeGuidSector,                    //!< Windows 8.1 'IndexerVolumeGuid' file
    kInfoFileSector,                                    //!< Info .txt file
    kStatusFileSector,                                  //!< Status .txt file
    kFirstUnusedSector,                                 //!< First sector available for data.

    kFirstClusterSector = kRootDir1Sector, //!< Sector number of the first cluster.
};

//! @brief Convert a sector number to a cluster number.
#define CLUSTER_FROM_SECTOR(s) (((s)-kFirstClusterSector) / kDiskClusterSize)

//! @brief Root directory entry constants.
enum _root_dir_entry_numbers
{
    kInfoFileDirEntry = 11,
    kStatusFileDirEntry = 12,
    kFirstUnusedDirEntry = 13
};

//! @brief Sector information.
//!
//! Information about canned sectors. The sector data does not have to completely fill the
//! sector. Any remainder bytes will be cleared to zero in the sector read function.
typedef struct SectorInfo
{
    uint32_t sector;     //!< Sector number.
    const uint8_t *data; //!< Data for the sector.
    uint32_t length;     //!< Number of bytes of data.
} sector_info_t;

/*******************************************************************************
 * Variables
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

extern const sector_info_t g_msdDiskSectors[];

#if defined(__cplusplus)
}
#endif /* __cplusplus */

//! @}

#endif // _USB_MSD_DISK_H_
