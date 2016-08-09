/*
 * Copyright (c) 2013 - 2014, Freescale Semiconductor, Inc.
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
#include <ctype.h>

#include "bootloader_common.h"
#include "host_blsh_cmd.h"
#include "host_command.h"
#include "host_hardware.h"
#include "bllibc.h"
#include "bootloader/bootloader.h"
#include "sbloader/sbloader.h"

#if defined(BL_EMBEDDED_HOST)
#include "srecord_image.h"
#include "intelhex_image.h"
#include "binary_image.h"
#include "SB_image.h"
#include "board.h"
#endif

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define invalid_arg_echo(msg)                               \
    blsh_printf("\r\n Error: Invalid arguments '%s'", msg); \
    return

/*******************************************************************************
 * Variables
 ******************************************************************************/
static void process_response_status(uint32_t status);

/*! @brief get-property command definition */
static void get_property_func(uint8_t argc, uint8_t **argv);
static blsh_cmd_t get_property_cmd = {
    "get-property", "Query various properties and settings", "get-property <tag>", get_property_func, 0, 0
};
static void process_getProperty_response(uint32_t property_tag, uint32_t *response_param);

#if DEBUG && !DEBUG_PRINT_DISABLE
static const char *const kPeripheralNames[] = {
    "UART", /* kPeripheralType_UART */
    "I2C",  /* kPeripheralType_I2CSlave */
    "SPI",  /* kPeripheralType_SPISlave */
    "CAN",  /* kPeripheralType_CAN */
    "HID",  /* kPeripheralType_USB_HID */
    "CDC",  /* kPeripheralType_USB_CDC */
    "DFU",  /* kPeripheralType_USB_DFU */
    "MSD"   /* kPeripheralType_USB_MSC */
};

//! @brief Value of the terminator code in the g_statusCodes table.
enum
{
    kStatusMessageTableTerminatorValue = 0x7fffffff,
};
/*! @brief Status return code descriptions. */
struct StatusMessageTableEntry
{
    int32_t status;      /*!< Status code value. */
    const char *message; /*!< Description of the status. */
};
struct StatusMessageTableEntry g_statusCodes[] = {
    /* Generic statuses. */
    { kStatus_Success, "Success." },
    { kStatus_Fail, "Failure." },
    { kStatus_ReadOnly, "kStatus_ReadOnly" },
    { kStatus_OutOfRange, "kStatus_OutOfRange" },
    { kStatus_InvalidArgument, "kStatus_InvalidArgument" },

    /* Flash driver errors. */
    { 100 /*kStatus_FlashSizeError*/, "kStatus_FlashSizeError" },
    { 101 /*kStatus_FlashAlignmentError*/, "kStatus_FlashAlignmentError" },
    { 102 /*kStatus_FlashAddressError*/, "kStatus_FlashAddressError" },
    { 103 /*kStatus_FlashAccessError*/, "kStatus_FlashAccessError" },
    { 104 /*kStatus_FlashProtectionViolation*/, "kStatus_FlashProtectionViolation" },
    { 105 /*kStatus_FlashCommandFailure*/, "kStatus_FlashCommandFailure" },
    { 106 /*kStatus_FlashUnknownProperty*/, "kStatus_FlashUnknownProperty" },
    { 108 /*kStatus_FlashRegionExecuteOnly*/, "kStatus_FlashRegionExecuteOnly" },
    { 109 /*kStatus_FlashExecuteInRamFunctionNotReady*/, "kStatus_FlashExecuteInRamFunctionNotReady" },

    /* I2C driver errors. */
    { 200 /*kStatus_I2C_SlaveTxUnderrun*/, "I2C Slave TX Underrun error." },
    { 201 /*kStatus_I2C_SlaveRxOverrun*/, "I2C Slave RX Overrun error." },
    { 202 /*kStatus_I2C_AribtrationLost*/, "I2C Arbitration Lost error." },

    /* SPI driver errors. */
    { 300 /*kStatus_SPI_SlaveTxUnderrun*/, "SPI Slave TX Underrun error." },
    { 301 /*kStatus_SPI_SlaveRxOverrun*/, "SPI Slave RX Overrun error." },

    /* QSPI driver errors. */
    { 400 /*kStatus_QspiFlashSizeError*/, "QSPI Flash Size error." },
    { 401 /*kStatus_QspiFlashAlignmentError*/, "QSPI Flash Alignment error." },
    { 402 /*kStatus_QspiFlashAddressError*/, "QSPI Flash Address error." },
    { 403 /*kStatus_QspiFlashCommandFailure*/, "QSPI Flash Command Failure." },
    { 404 /*kStatus_QspiFlashUnknownProperty*/, "QSPI Flash Unknown Property." },
    { 405 /*kStatus_QspiNotConfigured*/, "QSPI Not Configured." },
    { 406 /*kStatus_QspiCommandNotSupported*/, "QSPI Command Not Supported." },
    { 407 /*kStatus_QspiCommandTimeout*/, "QSPI Command Timeout" },
    { 408 /*kStatus_QspiWriteFailure*/, "QSPI Write Failure." },

    /* OTFAD driver errors. */
    { 500 /*kStatus_OtfadSecurityViolation*/, "OTFAD Security Violation." },
    { 501 /*kStatus_OtfadLogicallyDisabled*/, "OTFAD Logically Disabled." },
    { 502 /*kStatus_OtfadInvalidKey*/, "OTFAD Invalid Key." },
    { 503 /*Kstatus_OtfadInvalidKeyBlob*/, "OTFAD Invalid KeyBlob." },

    /* Bootloader errors. */
    { kStatus_UnknownCommand, "kStatus_UnknownCommand" },
    { kStatus_SecurityViolation, "Command disallowed when security is enabled." },
    { kStatus_AbortDataPhase, "kStatus_AbortDataPhase" },
    { kStatus_Ping, "kStatus_Ping" },
    { kStatus_NoResponse, "No response packet from target device." },
    { kStatus_NoResponseExpected, "No response packet from target device was expected." },

    /* SB loader errors. */
    { kStatusRomLdrSectionOverrun, "kStatusRomLdrSectionOverrun" },
    { kStatusRomLdrSignature, "kStatusRomLdrSignature" },
    { kStatusRomLdrSectionLength, "kStatusRomLdrSectionLength" },
    { kStatusRomLdrUnencryptedOnly, "kStatusRomLdrUnencryptedOnly" },
    { kStatusRomLdrEOFReached, "kStatusRomLdrEOFReached" },
    { kStatusRomLdrChecksum, "kStatusRomLdrChecksum" },
    { kStatusRomLdrCrc32Error, "kStatusRomLdrCrc32Error" },
    { kStatusRomLdrUnknownCommand, "kStatusRomLdrUnknownCommand" },
    { kStatusRomLdrIdNotFound, "kStatusRomLdrIdNotFound" },
    { kStatusRomLdrDataUnderrun, "kStatusRomLdrDataUnderrun" },
    { kStatusRomLdrJumpReturned, "kStatusRomLdrJumpReturned" },
    { kStatusRomLdrCallFailed, "kStatusRomLdrCallFailed" },
    { kStatusRomLdrKeyNotFound, "kStatusRomLdrKeyNotFound" },
    { kStatusRomLdrSecureOnly, "kStatusRomLdrSecureOnly" },

    /* Memory interface errors. */
    { kStatusMemoryRangeInvalid, "kStatusMemoryRangeInvalid" },
    { kStatusMemoryReadFailed, "kStatusMemoryReadFailed" },
    { kStatusMemoryWriteFailed, "kStatusMemoryWriteFailed" },

    /* Property store errors. */
    { kStatus_UnknownProperty, "Unknown property." },
    { kStatus_ReadOnlyProperty, "Property is read-only." },
    { kStatus_InvalidPropertyValue, "Invalid property value." },

    /* Application crc check statuses. */
    { 10400, "kStatus_AppCrcCheckPassed" },
    { 10401, "kStatus_AppCrcCheckFailed" },
    { 10402, "kStatus_AppCrcCheckInactive" },
    { 10403, "kStatus_AppCrcCheckInvalid" },
    { 10404, "kStatus_AppCrcCheckOutOfRange" },

    /* Packetizer errors. */
    { kStatus_NoPingResponse, "No response received for ping command." },
    { kStatus_InvalidPacketType, "Invalid packet type." },
    { kStatus_InvalidCRC, "Invalid CRC value." },
    { kStatus_NoCommandResponse, "No response received for command." },

    /* Reliable Update statuses. */
    { 10600, "kStatus_ReliableUpdateSuccess" },
    { 10601, "kStatus_ReliableUpdateFail" },
    { 10602, "kStatus_ReliableUpdateImageInvalid" },
    { 10603, "kStatus_ReliableUpdateInactive" },

    /* Terminator */
    { kStatusMessageTableTerminatorValue, "" }
};

#endif /* DEBUG */

/*! @brief get-property command definition */
static void set_property_func(uint8_t argc, uint8_t **argv);
static blsh_cmd_t set_property_cmd = {
    "set-property", "Set various properties and settings", "set-property <tag> <value>", set_property_func, 0, 0
};

/*! @brief target-reset command definition */
static void target_reset_func(uint8_t argc, uint8_t **argv);
static blsh_cmd_t target_reset_cmd = { "reset", "Reset the target bootloader", "reset", target_reset_func, 0, 0 };

/*! @brief set-bus command definition */
static void set_bus_func(uint8_t argc, uint8_t **argv);
static blsh_cmd_t set_bus_cmd = {
    "set-bus", "Set bus and frequency/baud rate", "set-bus -b<bus> -f<frequency/baud rate>", set_bus_func, 0, 0
};

#if defined(BL_EMBEDDED_HOST)
/*! @brief flash_image command definition */
static void flash_image_func(uint8_t argc, uint8_t **argv);
blsh_cmd_t flash_image_cmd = {
    "flash-image", "Write a formated image to flash", "flash-image", flash_image_func, 0, 0
};

/*! @brief write_memory command definition */
static void write_memory_func(uint8_t argc, uint8_t **argv);
blsh_cmd_t write_memory_cmd = { "write-memory",
                                "Write memory from string of hex-values",
                                "write-memory <addr> [{{<hex-data>}}]",
                                write_memory_func,
                                0,
                                0 };

/*! @brief read memory command definition */
static void read_memory_func(uint8_t argc, uint8_t **argv);
blsh_cmd_t read_memory_cmd = {
    "read-memory", "Read memory and display", "read-memory <addr> <byte_count>", read_memory_func, 0, 0
};

/*! @brief read memory command definition */
static void fill_memory_func(uint8_t argc, uint8_t **argv);
blsh_cmd_t fill_memory_cmd = { "fill-memory",
                               "Fill memory with pattern",
                               "fill-memory <addr> <byte_count> <pattern> [word | short | byte]",
                               fill_memory_func,
                               0,
                               0 };

/*! @brief read memory command definition */
static void flash_security_disable_func(uint8_t argc, uint8_t **argv);
blsh_cmd_t flash_security_disable_cmd = { "flash-security-disable",
                                          "Flash security disable <8-byte-hex-key>",
                                          "flash-security-disable <key>",
                                          flash_security_disable_func,
                                          0,
                                          0 };

/*! @brief flash-erase-all command definition */
static void flash_erase_all_func(uint8_t argc, uint8_t **argv);
blsh_cmd_t flash_erase_all_cmd = {
    "flash-erase-all", "Erase all flash, excluding protected regions", "flash-erase-all", flash_erase_all_func, 0, 0
};

/*! @brief flash-erase-all-unsecure command definition */
static void flash_erase_all_unsecure_func(uint8_t argc, uint8_t **argv);
blsh_cmd_t flash_erase_all_unsecure_cmd = { "flash-erase-all-unsecure",
                                            "Erase all flash, including protected regions",
                                            "flash-erase-all-unsecure",
                                            flash_erase_all_unsecure_func,
                                            0,
                                            0 };

/*! @brief flash-erase-all-unsecure command definition */
static void flash_erase_region_func(uint8_t argc, uint8_t **argv);
blsh_cmd_t flash_erase_region_cmd = { "flash-erase-region",
                                      "Erase a region of flash",
                                      "flash-erase-region <addr> <byte_count>",
                                      flash_erase_region_func,
                                      0,
                                      0 };

/*! @brief call command definition */
static void execute_func(uint8_t argc, uint8_t **argv);
blsh_cmd_t execute_cmd = { "execute",
                           "Execute at address with arg and stack pointer",
                           "execute <address> <arg> <stackpointer>",
                           execute_func,
                           0,
                           0 };

/*! @brief call command definition */
static void call_func(uint8_t argc, uint8_t **argv);
blsh_cmd_t call_cmd = { "call", "Call address with arg", "call <address> <arg>", call_func, 0, 0 };

/*! @brief falsh program once command definition */
static void flash_program_once_func(uint8_t argc, uint8_t **argv);
blsh_cmd_t flash_program_once_cmd = { "flash-program-once",
                                      "Program flash program once field",
                                      "flash-program-once <index> <byteCount> <data>",
                                      flash_program_once_func,
                                      0,
                                      0 };

/*! @brief flash read once command definition */
static void flash_read_once_func(uint8_t argc, uint8_t **argv);
blsh_cmd_t flash_read_once_cmd = { "flash-read-once",
                                   "Read flash program once field",
                                   "flash-read-once <index> <byteCount>",
                                   flash_read_once_func,
                                   0,
                                   0 };

/*! @brief call command definition */
static void flash_read_resource_func(uint8_t argc, uint8_t **argv);
blsh_cmd_t flash_read_resource_cmd = { "flash-read-resource",
                                       "Reads the contents of Flash IFR or Flash Firmware ID",
                                       "flash-read-resource <addr> <byteCount> <option>",
                                       flash_read_resource_func,
                                       0,
                                       0 };

#endif

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*! @brief bus option parse */
static status_t bus_options_parse(uint8_t argc, uint8_t **argv, bus_option_t *bus_option);

/*******************************************************************************
 * Code
 ******************************************************************************/

void host_blsh_cmd_init(void)
{
    blsh_init();

    command_add(&get_property_cmd);
    command_add(&set_property_cmd);
    command_add(&target_reset_cmd);
    command_add(&set_bus_cmd);
}

/*!
 * @brief get property command function.
 *
 * @param argc the count of arguments inputed to shell.
 * @param argv the value of arguments inputed to shell.
 */
static void get_property_func(uint8_t argc, uint8_t **argv)
{
    uint8_t *index = 0;
    uint32_t property_tag = 0;
    uint32_t response_param[7] = { 0 }; /* response_param[0] is parameter count */
    uint32_t status = 0;

    /* This command has two argc */
    if (argc != 2)
    {
        invalid_arg_echo(get_property_cmd.usage);
    }

    /* Options parse */
    index = argv[1];
    if (!bl_atoi(&property_tag, index))
    {
        invalid_arg_echo(get_property_cmd.usage);
    }

    /* Get property */
    status = handle_getProperty_command(property_tag, response_param);
    process_response_status(status);

    /* Dispaly */
    if (status == kStatus_Success)
    {
        process_getProperty_response(property_tag, response_param);
    }
}

/*!
 * @brief process response status.
 *
 * @param status response status
 */
static void process_response_status(uint32_t status)
{
    uint32_t status_index = 0;
    while (status_index != kStatusMessageTableTerminatorValue)
    {
        if (status == g_statusCodes[status_index].status)
        {
            break;
        }
        status_index++;
    }
    blsh_printf("\r\n Response Status = %d (0x%X) %s", status, status, g_statusCodes[status_index].message);
}

/*!
 * @brief get status message frome status code.
 *
 * @param code status code
 */
static char const *get_status_message(status_t code)
{
    int i;
    for (i = 0; g_statusCodes[i].status != kStatusMessageTableTerminatorValue; ++i)
    {
        if (code == g_statusCodes[i].status)
        {
            return g_statusCodes[i].message;
        }
    }

    return "Unknown error code (%d)";
}

/*!
 * @brief process get-property response.
 *
 * @param property_tag the property tag inputed into blsh.
 * @param response_param the response parameter.
 */
static void process_getProperty_response(uint32_t property_tag, uint32_t *response_param)
{
    blsh_printf("\r\n ");
    switch (property_tag)
    {
        case kPropertyTag_BootloaderVersion:
            blsh_printf("Current Version = %c%d.%d.%d", (response_param[1] & 0xff000000) >> 24,
                        (response_param[1] & 0x00ff0000) >> 16, (response_param[1] & 0x0000ff00) >> 8,
                        response_param[1] & 0x000000ff);
            break;
        case kPropertyTag_TargetVersion:
            blsh_printf("Target Version = %c%d.%d.%d", (response_param[1] & 0xff000000) >> 24,
                        (response_param[1] & 0x00ff0000) >> 16, (response_param[1] & 0x0000ff00) >> 8,
                        response_param[1] & 0x000000ff);
            break;
        case kPropertyTag_AvailablePeripherals:
        {
            blsh_printf("Available Peripherals = ");
            uint32_t peripherals = response_param[1];
            uint32_t index = 0;
            while (peripherals)
            {
                if (peripherals & 0x00000001)
                {
                    blsh_printf("%s", kPeripheralNames[index]);
                    if (peripherals >> 1)
                    {
                        blsh_printf(", ");
                    }
                }
                peripherals >>= 1;
                index++;
            }
            break;
        }
        case kPropertyTag_FlashStartAddress:
            blsh_printf("Flash Start Address = 0x%X", response_param[1]);
            break;
        case kPropertyTag_FlashSizeInBytes:
            blsh_printf("Flash Size = %d bytes", response_param[1]);
            break;
        case kPropertyTag_FlashSectorSize:
            blsh_printf("Flash Sector Size = %d bytes", response_param[1]);
            break;
        case kPropertyTag_FlashBlockCount:
            blsh_printf("Flash Block Count = %d", response_param[1]);
            break;
        case kPropertyTag_AvailableCommands:
        {
            blsh_printf("Available Commands = ");
            uint32_t commands = response_param[1];
            uint32_t index = 0;
            while (commands)
            {
                if (commands & 0x00000001)
                {
                    blsh_printf("%s", kCommandNames[index]);
                    if (commands >> 1)
                    {
                        blsh_printf(", ");
                    }
                }
                commands >>= 1;
                index++;
            }
            break;
        }
        case kPropertyTag_CrcCheckStatus:
            blsh_printf("CRC Check Status = %s", get_status_message(response_param[1]));
            break;
        case kPropertyTag_VerifyWrites:
            blsh_printf("Verify Writes Flag = %s", response_param[1] ? "ON" : "OFF");
            break;
        case kPropertyTag_MaxPacketSize:
            blsh_printf("Max Packet Size = %d bytes", response_param[1]);
            break;
        case kPropertyTag_ReservedRegions:
        {
            uint32_t flashLength = response_param[2] - response_param[1] + 1;
            if (flashLength == 1)
            {
                flashLength = 0;
            }
            uint32_t ramLength = response_param[4] - response_param[3] + 1;
            if (ramLength == 1)
            {
                ramLength = 0;
            }
            blsh_printf("Reserved Regions = ");
            blsh_printf("Flash: 0x%X-0x%X (%d bytes), ", response_param[1], response_param[2], flashLength);
            blsh_printf("RAM: 0x%X-0x%X (%d bytes)", response_param[3], response_param[4], ramLength);
            break;
        }
        case kPropertyTag_RAMStartAddress:
            printf("RAM Start Address = 0x%X", response_param[1]);
            break;
        case kPropertyTag_RAMSizeInBytes:
            blsh_printf("RAM Size = %d bytes", response_param[1]);
            break;
        case kPropertyTag_SystemDeviceId:
            blsh_printf("System Device ID = 0x%X", response_param[1]);
            break;
        case kPropertyTag_FlashSecurityState:
            blsh_printf("Flash Security State = %s", response_param[1] ? "SECURE" : "UNSECURE");
            break;
        case kPropertyTag_UniqueDeviceId:
            blsh_printf("Unique Device ID =");
            for (uint32_t i = 1; i < response_param[0]; ++i)
            {
                blsh_printf(" %X %X", (response_param[i] & 0xffff0000) >> 16, (response_param[i] & 0x0000ffff));
            }
            break;
        case kPropertyTag_FacSupport:
            blsh_printf("Flash Access Controller (FAC) Support Flag = %s",
                        response_param[1] ? "SUPPORTED" : "UNSUPPORTED");
            break;
        case kPropertyTag_FlashAccessSegmentSize:
            blsh_printf("Flash Access Segment Size = %d bytes", response_param[1]);
            break;
        case kPropertyTag_FlashAccessSegmentCount:
            blsh_printf("Flash Access Segment Count = %d", response_param[1]);
            break;
        case kPropertyTag_FlashReadMargin:
            blsh_printf("Flash read margin level = ");
            if (response_param[1] == 0)
            {
                blsh_printf("NORMAL");
            }
            else if (response_param[1] == 1)
            {
                blsh_printf("USER");
            }
            else if (response_param[1] == 2)
            {
                blsh_printf("FACTORY");
            }
            else
            {
                blsh_printf("UNKNOWN (%d)", response_param[1]);
            }
            break;
        case kPropertyTag_QspiInitStatus:
            blsh_printf("QSPI Init Status = %s", get_status_message(response_param[1]));
            break;
        case kPropertyTag_ReliableUpdateStatus:
            blsh_printf("Reliable Update Status = %s", get_status_message(response_param[1]));
            break;
        default:
            blsh_printf("Unknow property");
            break;
    }
}

/*!
 * @brief read memory function.
 *
 * @param argc the count of arguments inputed to shell.
 * @param argv the value of arguments inputed to shell.
 */
static void set_property_func(uint8_t argc, uint8_t **argv)
{
    uint8_t *index = 0;
    uint32_t property_tag = 0;
    uint32_t property_value = 0;
    uint32_t status = 0;

    /* This command has three argc */
    if (argc != 3)
    {
        invalid_arg_echo(set_property_cmd.usage);
    }

    /* Options parse */
    index = argv[1];
    if (!bl_atoi(&property_tag, index))
    {
        invalid_arg_echo(set_property_cmd.usage);
    }

    index = argv[2];
    if (!bl_atoi(&property_value, index))
    {
        invalid_arg_echo(set_property_cmd.usage);
    }

    /* set-property renturn status */
    status = handle_setProperty_command(property_tag, property_value);
    process_response_status(status);
}

/*!
 * @brief target reset function.
 *
 * @param argc the count of arguments inputed to shell.
 * @param argv the value of arguments inputed to shell.
 */
static void target_reset_func(uint8_t argc, uint8_t **argv)
{
    uint32_t status = 0;

    status = handle_reset_command();
    process_response_status(status);
}

/*!
 * @brief set-bus function.
 *
 * @param argc the count of arguments inputed to shell.
 * @param argv the value of arguments inputed to shell.
 */
static void set_bus_func(uint8_t argc, uint8_t **argv)
{
    bus_option_t bus_option = { 0, 100 };

    /* Options parse */
    if ((argc > 1) && (bus_options_parse(argc, argv, &bus_option) != kStatus_Success))
    {
        return;
    }

    if (bus_option.bus == kSPI_mode)
    {
        blsh_printf("\r\n   Transfer bus:                 SPI ");
        blsh_printf("\r\n   Transfer frequency(Khz):      %d", bus_option.freq);
    }
    else if (bus_option.bus == kI2C_mode)
    {
        blsh_printf("\r\n   Transfer bus:                 I2C ");
        blsh_printf("\r\n   Transfer frequency(Khz):      %d", bus_option.freq);
    }
    else if (bus_option.bus == kUART_mode)
    {
        if (bus_option.freq < kUART_MIN_BAUD)
        {
            bus_option.freq = kUART_DEFAULT_BAUD;
        }
        blsh_printf("\r\n   Transfer bus:                 UART ");
        blsh_printf("\r\n   Transfer baud rate:           %d", bus_option.freq);
    }
    else if (bus_option.bus == kCAN_mode)
    {
        blsh_printf("\r\n   Transfer bus:                 CAN  ");
        blsh_printf("\r\n   Transfer frequency(Khz):      %d", bus_option.freq);
    }
    else
    {
        invalid_arg_echo(set_bus_cmd.usage);
    }

    /* Configure bus */
    check_transfer_bus(bus_option.bus, &bus_option.freq);
    configure_transfer_bus(bus_option.bus, bus_option.freq);
}

/*!
 * @brief parse memory command options.
 *
 * @param argc the count of arguments inputed to shell.
 * @param argv the value of arguments inputed to shell.
 * @param bus_option the bus options
 */
static status_t bus_options_parse(uint8_t argc, uint8_t **argv, bus_option_t *bus_option)
{
    uint8_t *index = 0;
    uint8_t i = 0;

    for (i = 1; i < argc; i++)
    {
        if ((argv[i][0] == '-') && (argv[i][1] == 'b'))
        {
            if (argv[i][2] != 0)
            {
                index = &argv[i][2];
                if (transfer_bus_parse(index, &bus_option->bus) != kStatus_Success)
                {
                    blsh_printf("\r\n Please input right transfer bus mode : -bspi/i2c/uart. ");
                    return kStatus_Fail;
                }
            }
            else
            {
                blsh_printf("\r\n Please input transfer bus after -b : -bspi/i2c/uart. ");
                return kStatus_Fail;
            }
        }
        else if ((argv[i][0] == '-') && (argv[i][1] == 'f'))
        {
            if (argv[i][2] != 0)
            {
                index = &argv[i][2];
                if (transfer_freq_parse(index, bus_option->bus, &bus_option->freq) != kStatus_Success)
                {
                    blsh_printf(
                        "\r\n Please input right transfer frequency : -f[100~1000] or baud rate : "
                        "-f[19200/38400/57600/115200/230400]. ");
                    return kStatus_Fail;
                }
            }
            else
            {
                blsh_printf(
                    "\r\n Please input transfer frequency after -f : -f[100~1000] or baud rate : "
                    "-f[19200/38400/57600/115200/230400]. ");
                return kStatus_Fail;
            }
        }
    }

    return kStatus_Success;
}

status_t transfer_bus_parse(uint8_t *src, uint8_t *option)
{
    if (bl_strstart("spi", src) == k_fullMatch)
    {
        *option = kSPI_mode;
        return kStatus_Success;
    }
    else if (bl_strstart("i2c", src) == k_fullMatch)
    {
        *option = kI2C_mode;
        return kStatus_Success;
    }
    else if (bl_strstart("uart", src) == k_fullMatch)
    {
        *option = kUART_mode;
        return kStatus_Success;
    }
    else if (bl_strstart("can", src) == k_fullMatch)
    {
        *option = kCAN_mode;
        return kStatus_Success;
    }

    return kStatus_Fail;
}

status_t transfer_freq_parse(uint8_t *src, uint8_t bus, uint32_t *option)
{
    uint32_t freq = 0;

    if (!bl_atoi(&freq, src))
    {
        return kStatus_Fail;
    }

    if ((freq >= 100) && (freq <= 1000) &&
        ((bus == kSPI_mode) || (bus == kI2C_mode) || (bus == kCAN_mode))) /* SPI or I2C frequency */
    {
        *option = freq;
        return kStatus_Success;
    }
    else if ((bus == kUART_mode) && ((freq == 19200) || (freq == 38400) || (freq == 57600) || (freq == 115200) ||
                                     (freq == 230400))) /* Uart baud rate */
    {
        *option = freq;
        return kStatus_Success;
    }
    return kStatus_Fail;
}

#if defined(BL_EMBEDDED_HOST)
/*!
 * @brief flash image function.
 *
 * @param handle UART handle pointer.
 */
static void flash_image_func(uint8_t argc, uint8_t **argv)
{
    uint32_t status = 0;

    status = flash_image(0);

    if (status == kRecordStatus_Success)
    {
        blsh_printf("\r\n Flash image success.");
    }
    else if (status == kRecordStatus_InvalidStart)
    {
        blsh_printf("\r\n No Flash image in host flash!");
    }
    else if (status == kRecordStatus_InvalidType)
    {
        blsh_printf("\r\n Invalid image type in host flash!");
    }
    else
    {
        blsh_printf("\r\n Flash image fail!");
    }
}

/*!
 * @brief write memory function.
 *
 * @param argc the count of arguments inputed to shell.
 * @param argv the value of arguments inputed to shell.
 */
static void write_memory_func(uint8_t argc, uint8_t **argv)
{
    uint8_t *index = 0;
    uint32_t address = 0;
    uint32_t length = 0;
    uint32_t write_bytes = 0;
    uint32_t status = 0;

    /* Options parse */
    if (argc != 3)
    {
        invalid_arg_echo(write_memory_cmd.usage);
    }

    index = argv[1];
    if (!bl_atoi(&address, index))
    {
        invalid_arg_echo(write_memory_cmd.usage);
    }

    index = argv[2];

    /*Check*/
    length = strlen((char *)index);
    for (uint32_t i = 0; i < length; i++)
    {
        if (!isxdigit(index[i]) && (index[i] != '{') && (index[i] != '}'))
        {
            invalid_arg_echo(write_memory_cmd.usage);
        }
    }

    if ((index[0] == '{') && (index[1] == '{'))
    {
        index += 2;
        length = strlen((char *)index);
        if ((index[--length] == '}') && (index[--length] == '}'))
        {
            /* Change to int */
            for (int32_t i = 0; i < length; i = i + 2)
            {
                index[write_bytes++] = read_hex_byte(index, i);
            }
            /* Write memory */
            status = handle_writeMemory_command(address, index, write_bytes);
        }
    }
    process_response_status(status);
}

/*!
 * @brief read memory function.
 *
 * @param argc the count of arguments inputed to shell.
 * @param argv the value of arguments inputed to shell.
 */
static void read_memory_func(uint8_t argc, uint8_t **argv)
{
    uint8_t *index = 0;
    uint32_t address = 0;
    uint8_t memory_data[32] = { 0 };
    uint32_t read_bytes = 0;
    uint32_t byte_count = 0;
    uint32_t status = 0;

    /* Options parse */
    if (argc != 3)
    {
        invalid_arg_echo(read_memory_cmd.usage);
    }

    index = argv[1];
    if (!bl_atoi(&address, index))
    {
        invalid_arg_echo(read_memory_cmd.usage);
    }

    index = argv[2];
    if (!bl_atoi(&byte_count, index))
    {
        invalid_arg_echo(read_memory_cmd.usage);
    }

    while (byte_count)
    {
        if (byte_count > sizeof(memory_data))
        {
            read_bytes = sizeof(memory_data);
        }
        else
        {
            read_bytes = byte_count;
        }

        status = handle_readMemory_command(address, memory_data, read_bytes);
        process_response_status(status);
        if (status != kStatus_Success)
        {
            return;
        }
        byte_count -= read_bytes;
        address += read_bytes;

        for (int32_t i = 0; i < read_bytes; i++)
        {
            if (i % 8 == 0)
            {
                blsh_printf("\r\n ");
            }
            blsh_printf("0x%X ", memory_data[i]);
        }
    }
}

/*!
 * @brief fill memory function.
 *
 * @param argc the count of arguments inputed to shell.
 * @param argv the value of arguments inputed to shell.
 */
static void fill_memory_func(uint8_t argc, uint8_t **argv)
{
    uint8_t *index = 0;
    uint32_t address = 0;
    uint32_t pattern_word = 0;
    uint32_t byte_count = 0;
    uint32_t status = 0;

    /* Options parse */
    if (argc != 5)
    {
        invalid_arg_echo(fill_memory_cmd.usage);
    }

    index = argv[1];
    if (!bl_atoi(&address, index))
    {
        invalid_arg_echo(fill_memory_cmd.usage);
    }

    index = argv[2];
    if (!bl_atoi(&byte_count, index))
    {
        invalid_arg_echo(fill_memory_cmd.usage);
    }

    index = argv[3];
    if (!bl_atoi(&pattern_word, index))
    {
        invalid_arg_echo(fill_memory_cmd.usage);
    }

    index = argv[4];
    if (bl_strstart("word", index) == k_fullMatch)
    {
        pattern_word = pattern_word;
    }
    else if (bl_strstart("short", index) == k_fullMatch)
    {
        pattern_word |= (pattern_word << 16);
    }
    else if (bl_strstart("byte", index) == k_fullMatch)
    {
        pattern_word |= (pattern_word << 8);
        pattern_word |= (pattern_word << 8);
        pattern_word |= (pattern_word << 8);
    }
    else
    {
        invalid_arg_echo(fill_memory_cmd.usage);
    }

    status = handle_fillMemory_command(address, pattern_word, byte_count);
    process_response_status(status);
}

/*!
 * @brief flash security disable region function.
 *
 * @param argc the count of arguments inputed to shell.
 * @param argv the value of arguments inputed to shell.
 */
static void flash_security_disable_func(uint8_t argc, uint8_t **argv)
{
    uint8_t *index = 0;
    uint32_t backdoorkey_low = 0;
    uint32_t backdoorkey_high = 0;
    uint32_t status = 0;
    uint32_t length = 0;

    /* Options parse */
    if (argc != 2)
    {
        invalid_arg_echo(flash_security_disable_cmd.usage);
    }

    index = argv[1];
    /*Check*/
    length = strlen((char *)index);
    if (length != 16)
    {
        invalid_arg_echo(flash_security_disable_cmd.usage);
    }
    for (uint32_t i = 0; i < length; i++)
    {
        if (!isxdigit(index[i]))
        {
            invalid_arg_echo(flash_security_disable_cmd.usage);
        }
    }

    backdoorkey_low = read_hex_byte(index, 0) << 24;
    backdoorkey_low |= read_hex_byte(index, 2) << 16;
    backdoorkey_low |= read_hex_byte(index, 4) << 8;
    backdoorkey_low |= read_hex_byte(index, 6);

    backdoorkey_high = read_hex_byte(index, 8) << 24;
    backdoorkey_high |= read_hex_byte(index, 10) << 16;
    backdoorkey_high |= read_hex_byte(index, 12) << 8;
    backdoorkey_high |= read_hex_byte(index, 14);

    status = handle_flashSecurityDisable_command(backdoorkey_low, backdoorkey_high);
    process_response_status(status);
}

/*!
 * @brief flash erase region function.
 *
 * @param argc the count of arguments inputed to shell.
 * @param argv the value of arguments inputed to shell.
 */
static void flash_erase_region_func(uint8_t argc, uint8_t **argv)
{
    uint8_t *index = 0;
    uint32_t address = 0;
    uint32_t byte_count = 0;
    uint32_t status = 0;

    /* Options parse */
    if (argc != 3)
    {
        invalid_arg_echo(flash_erase_region_cmd.usage);
    }

    index = argv[1];
    if (!bl_atoi(&address, index))
    {
        invalid_arg_echo(flash_erase_region_cmd.usage);
    }

    index = argv[2];
    if (!bl_atoi(&byte_count, index))
    {
        invalid_arg_echo(flash_erase_region_cmd.usage);
    }

    if (byte_count < 0)
    {
        invalid_arg_echo(flash_erase_region_cmd.usage);
    }

    status = handle_flashEraseRegion_command(address, byte_count);
    process_response_status(status);
}

/*!
 * @brief flash erase all function.
 *
 * @param argc the count of arguments inputed to shell.
 * @param argv the value of arguments inputed to shell.
 */
static void flash_erase_all_func(uint8_t argc, uint8_t **argv)
{
    uint32_t status = 0;

    status = handle_flashEraseAll_command();
    process_response_status(status);
}

/*!
 * @brief flash erase all unsecure function.
 *
 * @param argc the count of arguments inputed to shell.
 * @param argv the value of arguments inputed to shell.
 */
static void flash_erase_all_unsecure_func(uint8_t argc, uint8_t **argv)
{
    uint32_t status = 0;

    status = handle_flashEraseAllUnsecure_command();
    process_response_status(status);
}

/*!
 * @brief execute function.
 *
 * @param argc the count of arguments inputed to shell.
 * @param argv the value of arguments inputed to shell.
 */
static void execute_func(uint8_t argc, uint8_t **argv)
{
    uint8_t *index = 0;
    uint32_t address = 0;
    uint32_t arg = 0;
    uint32_t stack_pointer = 0;
    uint32_t status = 0;

    /* Options parse */
    if (argc != 4)
    {
        invalid_arg_echo(execute_cmd.usage);
    }

    index = argv[1];
    if (!bl_atoi(&address, index))
    {
        invalid_arg_echo(execute_cmd.usage);
    }

    index = argv[2];
    if (!bl_atoi(&arg, index))
    {
        invalid_arg_echo(execute_cmd.usage);
    }

    index = argv[3];
    if (!bl_atoi(&stack_pointer, index))
    {
        invalid_arg_echo(execute_cmd.usage);
    }

    status = handle_execute_command(address, arg, stack_pointer);
    process_response_status(status);
}

/*!
 * @brief call function.
 *
 * @param argc the count of arguments inputed to shell.
 * @param argv the value of arguments inputed to shell.
 */
static void call_func(uint8_t argc, uint8_t **argv)
{
    uint8_t *index = 0;
    uint32_t address = 0;
    uint32_t arg = 0;
    uint32_t status = 0;

    /* Options parse */
    if (argc != 3)
    {
        invalid_arg_echo(call_cmd.usage);
    }

    index = argv[1];
    if (!bl_atoi(&address, index))
    {
        invalid_arg_echo(call_cmd.usage);
    }

    index = argv[2];
    if (!bl_atoi(&arg, index))
    {
        invalid_arg_echo(call_cmd.usage);
    }

    status = handle_call_command(address, arg);
    process_response_status(status);
}

/*!
 * @brief flash program once function.
 *
 * @param argc the count of arguments inputed to shell.
 * @param argv the value of arguments inputed to shell.
 */
static void flash_program_once_func(uint8_t argc, uint8_t **argv)
{
    uint8_t *index = 0;
    uint32_t address_index = 0;
    uint32_t byte_count = 0;
    uint32_t status = 0;
    uint32_t data1 = 0;
    uint32_t data2 = 0;
    uint32_t length = 0;

    /* Options parse */
    if (argc != 4)
    {
        invalid_arg_echo(flash_program_once_cmd.usage);
    }

    index = argv[1];
    if (!bl_atoi(&address_index, index))
    {
        invalid_arg_echo(flash_program_once_cmd.usage);
    }

    index = argv[2];
    if (!bl_atoi(&byte_count, index))
    {
        invalid_arg_echo(flash_program_once_cmd.usage);
    }

    index = argv[3];
    if (byte_count == 4)
    {
        if (!bl_atoi(&data1, index))
        {
            invalid_arg_echo(flash_program_once_cmd.usage);
        }
        data2 = 0;
    }
    else if (byte_count == 8)
    {
        if (index[0] == '0' && index[1] == 'x')
        {
            index += 2;
        }

        for (uint32_t i = 0; i < 16; i++)
        {
            if (!isxdigit(index[i]))
            {
                invalid_arg_echo(flash_program_once_cmd.usage);
            }
        }
        data1 = read_hex_byte(index, 0) << 24;
        data1 |= read_hex_byte(index, 2) << 16;
        data1 |= read_hex_byte(index, 4) << 8;
        data1 |= read_hex_byte(index, 6);

        data2 = read_hex_byte(index, 8) << 24;
        data2 |= read_hex_byte(index, 10) << 16;
        data2 |= read_hex_byte(index, 12) << 8;
        data2 |= read_hex_byte(index, 14);
    }
    else
    {
        invalid_arg_echo(flash_program_once_cmd.usage);
    }

    status = handle_flashProgramOnce_command(address_index, byte_count, data1, data2);
    process_response_status(status);
}

/*!
 * @brief flash read once function.
 *
 * @param argc the count of arguments inputed to shell.
 * @param argv the value of arguments inputed to shell.
 */
static void flash_read_once_func(uint8_t argc, uint8_t **argv)
{
    uint8_t *index = 0;
    uint32_t address_index = 0;
    uint32_t byte_count = 0;
    uint32_t status = 0;
    uint32_t data1 = 0;
    uint32_t data2 = 0;

    /* Options parse */
    if (argc != 3)
    {
        invalid_arg_echo(flash_read_once_cmd.usage);
    }

    index = argv[1];
    if (!bl_atoi(&address_index, index))
    {
        invalid_arg_echo(flash_read_once_cmd.usage);
    }

    index = argv[2];
    if (!bl_atoi(&byte_count, index))
    {
        invalid_arg_echo(flash_read_once_cmd.usage);
    }

    if ((byte_count != 4) && (byte_count != 8))
    {
        invalid_arg_echo(flash_read_once_cmd.usage);
    }

    status = handle_flashReadOnce_command(address_index, byte_count, &data1, &data2);
    process_response_status(status);
    if (status == kStatus_Success)
    {
        blsh_printf("\r\n Response word 1 = %d (0x%X)", data1, data1);
        if (byte_count > 4)
        {
            blsh_printf("\r\n Response word 2 = %d (0x%X)", data2, data2);
        }
    }
}

static void flash_read_resource_func(uint8_t argc, uint8_t **argv)
{
    uint8_t *index = 0;
    uint32_t address = 0;
    uint8_t memory_data[32] = { 0 };
    uint32_t read_bytes = 0;
    uint32_t byte_count = 0;
    uint32_t option = 0;
    uint32_t status = 0;

    /* Options parse */
    if (argc != 4)
    {
        invalid_arg_echo(flash_read_resource_cmd.usage);
    }

    index = argv[1];
    if (!bl_atoi(&address, index))
    {
        invalid_arg_echo(flash_read_resource_cmd.usage);
    }

    index = argv[2];
    if (!bl_atoi(&byte_count, index))
    {
        invalid_arg_echo(flash_read_resource_cmd.usage);
    }

    index = argv[3];
    if (!bl_atoi(&option, index))
    {
        invalid_arg_echo(flash_read_resource_cmd.usage);
    }

    while (byte_count)
    {
        if (byte_count > sizeof(memory_data))
        {
            read_bytes = sizeof(memory_data);
        }
        else
        {
            read_bytes = byte_count;
        }

        status = handle_flashReadResource_command(address, memory_data, read_bytes, option);
        process_response_status(status);
        if (status != kStatus_Success)
        {
            return;
        }
        byte_count -= read_bytes;
        address += read_bytes;

        for (int32_t i = 0; i < read_bytes; i++)
        {
            if (i % 8 == 0)
            {
                blsh_printf("\r\n ");
            }
            blsh_printf("0x%X ", memory_data[i]);
        }
    }
}

#endif /* if defined(BL_EMBEDDED_HOST) */
