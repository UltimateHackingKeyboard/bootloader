# Ultimate Hacking Keyboard bootloader

This repository contains the bootloader of the [Ultimate Hacking Keyboard](https://ultimatehackingkeyboard.com/) which is a fully functional port of [KBOOT](http://www.nxp.com/products/microcontrollers-and-processors/arm-processors/kinetis-cortex-m-mcus/kinetis-symbols-footprints-and-models/kinetis-bootloader:KBOOT) v2.0, including its full command set. 

## Build

The project actually resides in [targets/MK22F51212/freedom_bootloader](targets/MK22F51212/freedom_bootloader), and can be compiled and debugged using [Kinetis Design Studio](http://www.nxp.com/products/software-and-tools/run-time-software/kinetis-software-and-tools/ides-for-kinetis-mcus/kinetis-design-studio-integrated-development-environment-ide:KDS_IDE). 

To test the bootloader a binary properly configured has been added to the root folder of this repository. This binary is based on the UHK_Right Firmware project. 
To understand these modifications and apply them to the current version of the UHK Right firmware, follow the procedure in "Adapting UHK Project to KBOOT.docx" (Work in progress...)

The device can be controlled and erased/programmed easily using
the blhost.exe tool provided by NXP and included in this repository. A GUI with a reduced set of features has also been created for Windows (KinetisFlashTool.exe).

## Key features

 - Communication through HID with any PC without the need of an additional driver.
 - Automatic timeout and jump to user application without any action from the user.
 - If no valid application is present, the bootloader will keep waiting for communication through the HID USB port.
 - Every command sent to the bootloader includes a validation process inside the MCU to avoid any error in the communication.
 - The memory area of the bootloader is protected, so even if the update fails, user just needs to do a Power on Reset (Plug and Unplug the Keyboard) in order to launch the bootloader again.
 - Smart reset behavior: If the MCU has been reset by the user (SW reset or Reset-pin-to-GND short) a timeout will be enabled.
 If the reset is a Power on Reset (meaning that the user has just connected the keyboard to the power) it will jump to the
 application firmware if its present on the memory.
