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

#include "usb_msd_disk.h"
#include "fat_directory_entry.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

//! @brief Date and time constants for directory entries.
enum _date_time_constants
{
    kFileDate = MAKE_FAT_DATE(12, 1, 2013), //!< 01-Dec-2013
    kFileTime = MAKE_FAT_TIME(12, 0, 0)     //!< 12:00:00 noon
};

/*******************************************************************************
 * Variables
 ******************************************************************************/

//! @brief Partition boot sector.
//!
//! Defines the FAT16 file system.
//!
//! The 0xaa55 signature at the end of the sector is not stored in this data. Instead, it is
//! filled in at runtime. This is done in order to save const data space.
static const uint8_t k_pbs[] = {
    0xEB,
    0x3C,
    0x90, // x86 JMP instruction
    'M',
    'S',
    'W',
    'I',
    'N',
    '4',
    '.',
    '1',                                 // 'MSWIN4.1'
    U16_LE(kDiskSectorSize),             // bytes per sector = 512
    0x01,                                // sectors per cluster = 1
    U16_LE(1),                           // number of reserved sectors = 1 (FAT12/16)
    0x02,                                // number of FATs = 2
    U16_LE(32),                          // maximum number of root directory entries = 32
    U16_LE(kDiskTotalLogicalBlocks - 1), // total volume sectors starting with PBS (16-bit count)
    0xF0,                                // media type, must match FAT[0] = 0xf0 (removable media)
    U16_LE(kDiskSectorsPerFat),          // sectors per FAT = 1
    U16_LE(1),                           // sectors per track = 1
    U16_LE(1),                           // number of heads = 1
    U32_LE(1),                           // sectors before start of PBS including MBR = 1
    U32_LE(kDiskTotalLogicalBlocks - 1), // total volume sectors starting with PBS
    0x00,                                // driver number (0x80 for hard disks) = 0
    0x00,                                // reserved
    0x29,                                // boot signature
    '1',
    '2',
    '3',
    '4', // volume ID = '1234'
    'K',
    'i',
    'n',
    'e',
    't',
    'i',
    's',
    ' ',
    'U',
    'S',
    'B', // volume label = 'Kinetis USB'
    // ..448 reserved bytes
    // 0x55,0xaa signature bytes - must be filled in at runtime
};

static const uint16_t k_fat1[] = {
    0xfff0, // unused cluster 0 (low byte must match media type in PBS)
    0xffff, // unused cluster 1
    0xffff, // '.fseventsd' directory
    0xffff, // 'System Volume Information' directory
    0xffff, // 'IndexerVolumeGuid' file
    0xffff, // 'info.txt' file
    0xffff, // 'status.txt' file
};

//! @brief Root directory.
//!
//! Volume label: FSL Loader
//!
//! Contents:
//! - .fseventsd (FSEVEN~1)
//! - .metadata_never_index (METADA~1)
//! - .Trashes (TRASHE~1)
//! - System Volume Information (SYSTEM~1)
//! - info.txt
//! - status.txt
static const fat_directory_entry_t k_rootDir[] = {
    // Volume label 'FSL Loader'
    MAKE_FAT_VOLUME_LABEL('F', 'S', 'L', ' ', 'L', 'o', 'a', 'd', 'e', 'r', ' ', kFileTime, kFileDate),

    // Mac OS X '.fseventsd' directory
    MAKE_FAT_LONG_NAME(
        1, L'.', L'f', L's', L'e', L'v', L'e', L'n', L't', L's', L'd', 0, 0xffff, 0xffff, 0xda, kLastLongNameEntry),
    MAKE_FAT_DIR_ENTRY('F',
                       'S',
                       'E',
                       'V',
                       'E',
                       'N',
                       '~',
                       '1',
                       ' ',
                       ' ',
                       ' ',
                       (kDirectoryAttribute | kHiddenAttribute),
                       kFileTime,
                       kFileDate,
                       CLUSTER_FROM_SECTOR(kMacFseventsdDirSector),
                       0),

    // Mac OS X '.metadata_never_index' file
    MAKE_FAT_LONG_NAME(
        2, L'e', L'r', L'_', L'i', L'n', L'd', L'e', L'x', 0, 0xffff, 0xffff, 0xffff, 0xffff, 0xa8, kLastLongNameEntry),
    MAKE_FAT_LONG_NAME(1, L'.', L'm', L'e', L't', L'a', L'd', L'a', L't', L'a', L'_', L'n', L'e', L'v', 0xa8, 0),
    MAKE_FAT_DIR_ENTRY('M',
                       'E',
                       'T',
                       'A',
                       'D',
                       'A',
                       '~',
                       '1',
                       ' ',
                       ' ',
                       ' ',
                       (kArchiveAttribute | kHiddenAttribute),
                       kFileTime,
                       kFileDate,
                       0,
                       0),

    // Mac OS X '.Trashes' file
    MAKE_FAT_LONG_NAME(
        1, L'.', L'T', L'r', L'a', L's', L'h', L'e', L's', 0, 0xffff, 0xffff, 0xffff, 0xffff, 0x25, kLastLongNameEntry),
    MAKE_FAT_DIR_ENTRY('T',
                       'R',
                       'A',
                       'S',
                       'H',
                       'E',
                       '~',
                       '1',
                       ' ',
                       ' ',
                       ' ',
                       (kArchiveAttribute | kHiddenAttribute),
                       kFileTime,
                       kFileDate,
                       0,
                       0),

    // Windows 'System Volume Information' directory
    MAKE_FAT_LONG_NAME(
        2, L' ', L'I', L'n', L'f', L'o', L'r', L'm', L'a', L't', L'i', L'o', L'n', 0, 0x72, kLastLongNameEntry),
    MAKE_FAT_LONG_NAME(1, L'S', L'y', L's', L't', L'e', L'm', L' ', L'V', L'o', L'l', L'u', L'm', L'e', 0x72, 0),
    MAKE_FAT_DIR_ENTRY('S',
                       'Y',
                       'S',
                       'T',
                       'E',
                       'M',
                       '~',
                       '1',
                       ' ',
                       ' ',
                       ' ',
                       (kDirectoryAttribute | kSystemAttribute | kHiddenAttribute),
                       kFileTime,
                       kFileDate,
                       CLUSTER_FROM_SECTOR(kWindowsSysVolInfoDirSector),
                       0),

    // Info and status files
    MAKE_FAT_DIR_ENTRY('I',
                       'N',
                       'F',
                       'O',
                       ' ',
                       ' ',
                       ' ',
                       ' ',
                       'T',
                       'X',
                       'T',
                       kReadOnlyAttribute,
                       kFileTime,
                       kFileDate,
                       CLUSTER_FROM_SECTOR(kInfoFileSector),
                       1), // File size is filled in at runtime
    MAKE_FAT_DIR_ENTRY('S',
                       'T',
                       'A',
                       'T',
                       'U',
                       'S',
                       ' ',
                       ' ',
                       'T',
                       'X',
                       'T',
                       kReadOnlyAttribute,
                       kFileTime,
                       kFileDate,
                       CLUSTER_FROM_SECTOR(kStatusFileSector),
                       1), // File size is filled in at runtime
};

//! @brief .fseventsd directory.
//!
//! Contents:
//! - .
//! - ..
//! - no_log
static const fat_directory_entry_t k_fseventsdDir[] = {
    // . and .. directories
    MAKE_FAT_DIR_ENTRY('.',
                       ' ',
                       ' ',
                       ' ',
                       ' ',
                       ' ',
                       ' ',
                       ' ',
                       ' ',
                       ' ',
                       ' ',
                       (kDirectoryAttribute | kArchiveAttribute | kHiddenAttribute),
                       kFileTime,
                       kFileDate,
                       CLUSTER_FROM_SECTOR(kMacFseventsdDirSector),
                       0),
    MAKE_FAT_DIR_ENTRY(
        '.', '.', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', kDirectoryAttribute, kFileTime, kFileDate, 0, 0),

    // Special 'no_log' file with reserved byte set to 0x08.
    {.entry = {.name = { 'N', 'O', '_', 'L', 'O', 'G', ' ', ' ', ' ', ' ', ' ' },
               .attributes = kArchiveAttribute,
               .ntReserved = 0x08,
               .creationTime = kFileTime,
               .creationDate = kFileDate,
               .lastAccessDate = kFileDate,
               .firstClusterHigh = 0,
               .writeTime = kFileTime,
               .writeDate = kFileDate,
               .firstClusterLow = 0,
               .fileSize = 0 } },
};

static const wchar_t k_indexerVolumeGuidFile[] = L"{37203BF8-FD83-4321-A4C4-9A9ABF8FBCFD}";

//! @brief System Volume Information directory.
//!
//! Contents:
//! - .
//! - ..
//! - IndexerVolumeGuid (INDEXE~1)
static const fat_directory_entry_t k_sysVolInfoDir[] = {
    // . and .. directories
    MAKE_FAT_DIR_ENTRY('.',
                       ' ',
                       ' ',
                       ' ',
                       ' ',
                       ' ',
                       ' ',
                       ' ',
                       ' ',
                       ' ',
                       ' ',
                       (kDirectoryAttribute | kArchiveAttribute | kHiddenAttribute),
                       kFileTime,
                       kFileDate,
                       CLUSTER_FROM_SECTOR(kWindowsSysVolInfoDirSector),
                       0),
    MAKE_FAT_DIR_ENTRY(
        '.', '.', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', kDirectoryAttribute, kFileTime, kFileDate, 0, 0),

    // 'IndexerVolumeGuid' file
    MAKE_FAT_LONG_NAME(
        2, L'G', L'u', L'i', L'd', 0, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0, 0, 0xff, kLastLongNameEntry),
    MAKE_FAT_LONG_NAME(1, L'I', L'n', L'd', L'e', L'x', L'e', L'r', L'V', L'o', L'l', L'u', L'm', L'e', 0xff, 0),
    MAKE_FAT_DIR_ENTRY('I',
                       'N',
                       'D',
                       'E',
                       'X',
                       'E',
                       '~',
                       '1',
                       ' ',
                       ' ',
                       ' ',
                       kArchiveAttribute,
                       kFileTime,
                       kFileDate,
                       CLUSTER_FROM_SECTOR(kWindowsIndexerVolumeGuidSector),
                       (sizeof(k_indexerVolumeGuidFile) - 1)), // subtract 1 to remove the trailing null byte
};

const sector_info_t g_msdDiskSectors[] = {
    { kPbsSector, k_pbs, sizeof(k_pbs) },
    { kFat1Sector, (const uint8_t *)k_fat1, sizeof(k_fat1) },
    { kRootDir1Sector, (const uint8_t *)k_rootDir, sizeof(k_rootDir) },

    // Support for Mac OS X: .fseventsd directory
    { kMacFseventsdDirSector, (const uint8_t *)k_fseventsdDir, sizeof(k_fseventsdDir) },

    // Support for Window 8.1: System Volume Information directory
    { kWindowsSysVolInfoDirSector, (const uint8_t *)k_sysVolInfoDir, sizeof(k_sysVolInfoDir) },
    { kWindowsIndexerVolumeGuidSector, (const uint8_t *)k_indexerVolumeGuidFile,
      sizeof(k_indexerVolumeGuidFile) - 1 }, // subtract 1 to remove the trailing null byte

    // contains info.txt
    //     { kInfoFileSector, (const uint8_t *)((const uint8_t *)BlockBuf + 512), 512 },
    //
    //     // contains status.txt
    //     { kStatusFileSector, (const uint8_t *)((const uint8_t *)BlockBuf + 1024), 512 },

    // Terminator
    { 0 }
};
