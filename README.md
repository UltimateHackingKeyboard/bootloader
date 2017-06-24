# Ultimate Hacking Keyboard bootloader

This repository contains the bootloader of the right keyboard half of the [Ultimate Hacking Keyboard](https://ultimatehackingkeyboard.com/), which is a fully functional port of [KBOOT](http://www.nxp.com/products/microcontrollers-and-processors/arm-processors/kinetis-cortex-m-mcus/kinetis-symbols-footprints-and-models/kinetis-bootloader:KBOOT) v2.0. 

The actual codebase of the bootloader resides in [targets/MK22F51212/src](targets/MK22F51212/src).

## Building the bootloader

Install [Kinetis Design Studio](http://www.nxp.com/products/software-and-tools/run-time-software/kinetis-software-and-tools/ides-for-kinetis-mcus/kinetis-design-studio-integrated-development-environment-ide:KDS_IDE) (KDS), import the project by invoking *File -> Import -> General -> Existing Projects into Workspace*, select the `targets/MK22F51212/kds/freedom_bootloader` directory, and click on the *Finish* button. At this point, you should be able to build the firmware in KDS.

*WARNING:* If you are going to debug the bootloader yourself, it is highly recommended to change the security configuration. See the section "Understanding the bootloader security below before flashing the project to your keyboard."

## Flashing the bootloader

First up, let's take care of the physical connections:

1. Make sure to power the UHK via USB.
2. Connect your [SEGGER J-Link debug probe](https://www.segger.com/jlink-debug-probes.html) to USB.
3. Connect SEGGER J-Link to one of the SWD ports of the right half of the UHK.

Next up, it's wise to erase the MCU because the application firmware might have already been uploaded via the bootloader, in which case the bootloader may treat the already existing CRC as valid, causing it not to timeout.

1. Visit the [J-Link / J-Trace Downloads](https://www.segger.com/downloads/jlink) page. In the *J-Link Software and Documentation Pack* section click on the *Click for downloads*, then download and install the package of your operating system.
2. Start up JLink.exe and type the following:

```
device MK22FN512xxx12
erase
```

When JLink.exe prompts for additional information, choose SWD, and the default speed.

Lastly, Use KDS to build and upload the bootloader firmware to the MCU.

## Uploading the application firmware via the bootloader

After the above steps, the UHK should enumerate as the bootloader over USB.

Ultimately, you will want to upload the actual [application firmware](https://github.com/UltimateHackingKeyboard/firmware), but in order to test the bootloader, you can use [uhk-right_binary_blink.srec](uhk-right_binary_blink.srec) which is a properly configured binary that blinks the test LED of the right half of the UHK.

You can use the [blhost utility](/bin/Tools/blhost) to upload the application firmware via the bootloader. Unfortunately, the Linux version of this tool does not seem to work due to a bug, but the Windows version does work. You may have to execute the following as root/administrator:

```
blhost --usb 0x1D50,0x6120 flash-erase-all 0
blhost --usb 0x1D50,0x6120 flash-image uhk-right_binary_blink.srec
blhost --usb 0x1D50,0x6120 reset
```

Alternatively, you can use the Windows-only [KinetisFlashTool](/bin/Tools/KinetisFlashTool/win) GUI application.

## Understanding the UHK bootloader security.

Kinetis MCU Flash protection has several levels of general security:
 - Unsecured
 - Protected
 - Protected + Mass Erase disabled
 
 For UHK we have selected Protected to allow the user to erase the MCU in case he wants to.
 This also allows to fix any potential issue in the FW without having to desolder/throw away the device.
 
 Nevertheless, we have also added extra security to prevent any possible failure. Kinetis has another feature called region protection.
 This is controlled by the 4 registers FPROTx (FPROT0 - FPROT3). Using the following registers you can protect any region of the flash
 so even the bootloader itself cannot erase it.
 Since the bootloader is the only way the user has to update the Keyboard configuration, we don't want that it gets accidentally erased, 
 so we have protected the first 3 sectors (16 KBytes each) of the flash.
 
 But the security goes beyond that. The bootloader itself checks the security status of the flash and refuses to update anything when
 the flash is protected. To un-protect the flash, a backdoor key is needed. 
 
 Since the bootloader will only be accessible when the user provides an application level customized key, the backdoor key is here just for standard
 Kinetis security procedures. 
 
 To check the values of all the parameters, you can refer to file "bootloader\target\MK22FN51212\src\startup\gcc\startup_MK22F51212.S" and to the following 
 chapters of the K22FN512 reference manual for further details:
 
 Chapter 29.1 - Flash configuration Field Description
 Chapter 29.3 - Flash registers
 Chapter 29.4.12 - Flash security (Functional description)
 
 Notes:
 
  - Be careful when testing security features of the chip. If you enable the security and disable the Mass Erase, you will lock your device forever.
  - If you are going to debug the bootloader, disable the security to make it easier for you to control the device.
  - If you are going to modify the backdoor access key, keep in mind the Little Endian nature of Cortex M memory. (See screenshot "littleEndian_keyStorage")

## Key features

 * Communication through HID with any PC without the need of an additional driver.
 * Automatic timeout and jump to user application without any action from the user.
 * If no valid application is present, the bootloader will keep waiting for communication through the HID USB port.
 * Every command sent to the bootloader includes a validation process inside the MCU to avoid any error in the communication.
 * The memory area of the bootloader is protected, so even if the update fails, user just needs to do a Power on Reset (Plug and Unplug the Keyboard) in order to launch the bootloader again.
 * Smart reset behavior: If the MCU has been reset by the user (SW reset or Reset-pin-to-GND short) a timeout will be enabled. If the reset is a Power on Reset (meaning that the user has just connected the keyboard to the power) it will jump to the application firmware if its present on the memory.
