# Ultimate Hacking Keyboard bootloader

This repository contains the bootloader of the [Ultimate Hacking Keyboard](https://ultimatehackingkeyboard.com/) which is a fully functional port of [KBOOT](http://www.nxp.com/products/microcontrollers-and-processors/arm-processors/kinetis-cortex-m-mcus/kinetis-symbols-footprints-and-models/kinetis-bootloader:KBOOT) v2.0. 

The codebase of the bootloader actually resides in [targets/MK22F51212/src](targets/MK22F51212/src).

## Building the bootloader

Install [Kinetis Design Studio](http://www.nxp.com/products/software-and-tools/run-time-software/kinetis-software-and-tools/ides-for-kinetis-mcus/kinetis-design-studio-integrated-development-environment-ide:KDS_IDE) (KDS) and import the project by invoking File -> Import -> General -> Existing Projects into Workspace, select the ` targets/MK22F51212/kds/freedom_bootloader` directory, and click on the Finish button. At this point, you should be able to build the firmware in KDS.

## Flashing the bootloader

First up, let's take care of the physical connections:

* make sure to power the UHK via USB,
* connect your [SEGGER J-Link debug probe](https://www.segger.com/jlink-debug-probes.html) to USB,
* connect SEGGER J-Link to one of the SWD ports of the right half of the UHK.

Next up, it's wise to explicitly erase the MCU because an application firmware might have already been uploaded via the bootloader, in which case the bootloader may treat the already existing CRC as valid, causing it not to timeout.

* Visit the [J-Link / J-Trace Downloads](https://www.segger.com/downloads/jlink) page. In the *J-Link Software and Documentation Pack* section click on the *Click for downloads*, then download and install the package of your operating system.
* Start up JLink.exe and type the following:

```
device MK22FN512xxx12
erase
```

Lastly, Use KDS to build and upload the firmware to the MCU.

## Uploading the application firmware via the bootloader

After the above steps, the UHK should enumerate as the bootloader over USB.

You can use the [blhost utility](/bin/Tools/blhost) to upload the [application firmware](https://github.com/UltimateHackingKeyboard/firmware) via the bootloader. Unfortunately, the Linux version of this tool does not seem to work due to the bug.

Alternatively, you can use the Windows-only [KinetisFlashTool](/master/bin/Tools/KinetisFlashTool/win) GUI application.

## Test firmwares

To test the bootloader a binary properly configured has been added to the root folder of this repository. This binary is based on the UHK_Right Firmware project. 
To understand these modifications and apply them to the current version of the UHK Right firmware, follow the procedure in "Adapting UHK Project to KBOOT.docx" (Work in progress...)

## Key features

 * Communication through HID with any PC without the need of an additional driver.
 * Automatic timeout and jump to user application without any action from the user.
 * If no valid application is present, the bootloader will keep waiting for communication through the HID USB port.
 * Every command sent to the bootloader includes a validation process inside the MCU to avoid any error in the communication.
 * The memory area of the bootloader is protected, so even if the update fails, user just needs to do a Power on Reset (Plug and Unplug the Keyboard) in order to launch the bootloader again.
 * Smart reset behavior: If the MCU has been reset by the user (SW reset or Reset-pin-to-GND short) a timeout will be enabled. If the reset is a Power on Reset (meaning that the user has just connected the keyboard to the power) it will jump to the application firmware if its present on the memory.
