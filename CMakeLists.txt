cmake_minimum_required(VERSION 3.13)

# https://github.com/cortexm/baremetal
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
set(CMAKE_C_COMPILER_ID GNU)
set(CMAKE_CXX_COMPILER_ID GNU)
set(CMAKE_C_COMPILER_FORCED TRUE)
set(CMAKE_CXX_COMPILER_FORCED TRUE)

set(device MK22F51212)
project(bootloader-${device} C ASM)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)

add_executable(${PROJECT_NAME})

set(LINKER_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/targets/common/linker/kds/MK22F51212/MK22FN512xxx12_application_0x0000.ld)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/autobaud
    ${CMAKE_CURRENT_SOURCE_DIR}/src/bootloader
    ${CMAKE_CURRENT_SOURCE_DIR}/src/crc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/drivers
    ${CMAKE_CURRENT_SOURCE_DIR}/src/memory
    ${CMAKE_CURRENT_SOURCE_DIR}/src/packet
    ${CMAKE_CURRENT_SOURCE_DIR}/src/property
    ${CMAKE_CURRENT_SOURCE_DIR}/src/sbloader
    ${CMAKE_CURRENT_SOURCE_DIR}/src/startup
    ${CMAKE_CURRENT_SOURCE_DIR}/src/utilities
    ${CMAKE_CURRENT_SOURCE_DIR}/targets/common/include
    ${CMAKE_CURRENT_SOURCE_DIR}/targets/${device}/include
)
target_sources(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/targets/common/src/bl_dspi_irq_config_common.c
    ${CMAKE_CURRENT_SOURCE_DIR}/targets/common/src/bl_i2c_irq_config_common.c
    ${CMAKE_CURRENT_SOURCE_DIR}/targets/common/src/bl_uart_irq_config_common.c
    ${CMAKE_CURRENT_SOURCE_DIR}/targets/${device}/src/bootloader_config.h
    ${CMAKE_CURRENT_SOURCE_DIR}/targets/${device}/src/clock_config_K22F512.c
    ${CMAKE_CURRENT_SOURCE_DIR}/targets/${device}/src/hardware_init_K22F512.c
    ${CMAKE_CURRENT_SOURCE_DIR}/targets/${device}/src/memory_map_K22F512.c
    ${CMAKE_CURRENT_SOURCE_DIR}/targets/${device}/src/peripherals_K22F512.c
    ${CMAKE_CURRENT_SOURCE_DIR}/targets/${device}/src/peripherals_pinmux.h
    ${CMAKE_CURRENT_SOURCE_DIR}/targets/common/src/pinmux_utility_common.c
    ${CMAKE_CURRENT_SOURCE_DIR}/targets/${device}/src/target_config.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/bm_usb
    ${CMAKE_CURRENT_SOURCE_DIR}/src/autobaud/autobaud.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/bootloader/bl_app_crc_check.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/bootloader/bl_command.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/bootloader/bl_context.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/bootloader/bl_peripheral.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/bootloader/bl_peripheral_interface.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/bootloader/bl_shutdown_cleanup.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/bootloader/bl_user_entry.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/bootloader/bl_version.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/bootloader/bootloader.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/bootloader/wormhole.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/crc/crc16.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/crc/crc32.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/include/bootloader_common.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/memory/memory.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/packet/command_packet.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/packet/serial_packet.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/property/property.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/sbloader/sbloader.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/startup/crt0_gcc.S
    ${CMAKE_CURRENT_SOURCE_DIR}/src/startup/startup.c
    ${CMAKE_CURRENT_SOURCE_DIR}/targets/${device}/src/startup/gcc/startup_MK22F51212.S
    ${CMAKE_CURRENT_SOURCE_DIR}/targets/${device}/src/startup/system_MK22F51212.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/utilities/fsl_rtos_abstraction.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/autobaud/src/autobaud_irq.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/bootloader/src/bl_app_crc_check.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/bootloader/src/bl_command.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/bootloader/src/bl_context.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/bootloader/src/bl_exception_handler.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/bootloader/src/bl_main.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/bootloader/src/bl_misc.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/bootloader/src/bl_reliable_update.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/bootloader/src/bl_shutdown_cleanup.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/bootloader/src/bl_tree_root.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/bootloader/src/bl_user_entry.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/bootloader/src/dspi_peripheral_interface.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/bootloader/src/i2c_peripheral_interface.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/bootloader/src/scuart_peripheral_interface.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/bootloader/src/usb_hid_msc_peripheral_interface.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/bootloader/src/wormhole.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/crc/src/crc16.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/crc/src/crc32.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/drivers/crc/fsl_crc.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/drivers/dspi/fsl_dspi.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/drivers/flash/fsl_flash.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/drivers/flash/fsl_flash.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/drivers/gpio/fsl_gpio.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/drivers/microseconds/microseconds.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/drivers/port/fsl_port.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/drivers/smc/smc.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/drivers/smc/smc.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/drivers/uart/fsl_uart.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/memory/src/device_memory.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/memory/src/device_memory.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/memory/src/flash_memory.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/memory/src/flash_memory.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/memory/src/memory.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/memory/src/normal_memory.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/memory/src/normal_memory.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/memory/src/pattern_fill.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/memory/src/pattern_fill.s
    ${CMAKE_CURRENT_SOURCE_DIR}/src/memory/src/pattern_fill_gcc.S
    ${CMAKE_CURRENT_SOURCE_DIR}/src/memory/src/sram_init_cm4.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/packet/src/serial_packet.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/property/src/property.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/sbloader/src/sbloader.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/bm_usb/bootloader_hid_report_ids.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/bm_usb/composite.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/bm_usb/composite.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/bm_usb/fat_directory_entry.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/bm_usb/hid_bootloader.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/bm_usb/hid_bootloader.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/bm_usb/msc_disk.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/bm_usb/msc_disk.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/bm_usb/usb_descriptor.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/bm_usb/usb_descriptor.h
    ${CMAKE_CURRENT_SOURCE_DIR}/targets/${device}/src/usb_device_config.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/usb/device/usb_device.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/usb/device/usb_device_ch9.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/usb/device/usb_device_ch9.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/usb/device/usb_device_dci.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/usb/device/usb_device_dci.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/usb/device/usb_device_khci.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/usb/device/usb_device_khci.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/usb/include/usb.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/usb/osa/usb_osa.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/usb/osa/usb_osa_bm.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/usb/osa/usb_osa_bm.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/utilities/src/fsl_assert.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/utilities/src/fsl_rtos_abstraction.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/drivers/i2c/fsl_i2c.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/drivers/microseconds/src/microseconds_sysclk.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/usb/device/class/usb_device_class.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/usb/device/class/usb_device_class.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/usb/device/class/usb_device_hid.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/usb/device/class/usb_device_hid.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/usb/device/class/usb_device_msc.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/usb/device/class/usb_device_msc.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/usb/device/class/usb_device_msc_ufi.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/usb/device/class/usb_device_msc_ufi.h
)

set(CPU_OPTIONS -mthumb -mcpu=cortex-m4 -mfloat-abi=hard)

target_compile_options(${PROJECT_NAME} PUBLIC
    ${CPU_OPTIONS}
    $<$<CONFIG:Release>:-Os>
    $<$<CONFIG:Debug>:-g3>
    -fno-common
    -ffreestanding
    -fno-builtin
    -fshort-wchar
    -mapcs
    -flto
    -fno-inline-small-functions
    -Wall
    -ffunction-sections
    -fdata-sections
    -fsigned-char
    -fmessage-length=0
    -std=gnu99
)

target_compile_definitions(${PROJECT_NAME} PRIVATE
    $<$<CONFIG:Release>:NDEBUG>
    $<$<CONFIG:Debug>:DEBUG>
    USB_STACK_BM
    CPU_MK22FN512VDC12
    CPU_IS_ARM_CORTEX_M4=1
    FREEDOM
    BL_TARGET_FLASH
)

# Linker script
set_target_properties(${PROJECT_NAME} PROPERTIES LINK_DEPENDS ${LINKER_SCRIPT})
target_link_libraries(${PROJECT_NAME} PRIVATE
    m
    g
    gcc
    nosys
)
target_link_options(${PROJECT_NAME} PRIVATE
    ${CPU_OPTIONS}
    -T${LINKER_SCRIPT}
    -Xlinker -z
    -Xlinker muldefs
    -Os
    --specs=nano.specs
    -Wall
    -fno-common
    -ffunction-sections
    -fdata-sections
    -ffreestanding
    -fno-builtin
    -fshort-wchar
    -Wl,--no-wchar-size-warning
    -mapcs
    -Xlinker -static
    -flto
    -Xlinker --defsym=__ram_vector_table__=1
)

add_custom_command(OUTPUT ${PROJECT_NAME}.srec
    DEPENDS ${PROJECT_NAME}
    COMMAND ${CMAKE_OBJCOPY} -Osrec ${PROJECT_NAME} ${PROJECT_NAME}.srec
)
add_custom_command(OUTPUT ${PROJECT_NAME}.hex
    DEPENDS ${PROJECT_NAME}
    COMMAND ${CMAKE_OBJCOPY} -Oihex ${PROJECT_NAME} ${PROJECT_NAME}.hex
)
add_custom_command(OUTPUT ${PROJECT_NAME}.bin
    DEPENDS ${PROJECT_NAME}
    COMMAND ${CMAKE_OBJCOPY} -Obinary ${PROJECT_NAME} ${PROJECT_NAME}.bin
)
add_custom_target(srec
    DEPENDS ${PROJECT_NAME}.srec
)
add_custom_target(hex
    DEPENDS ${PROJECT_NAME}.hex
)
add_custom_target(bin
    DEPENDS ${PROJECT_NAME}.bin
)
