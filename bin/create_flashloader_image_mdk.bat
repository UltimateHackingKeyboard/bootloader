rem Pass in full path and Release|Debug to iar project directory
cd /d %1

arm-none-eabi-objcopy -I elf32-littlearm -O binary output\release\flashloader.elf flashloader.bin
python ..\..\..\..\bin\create_fl_image_kds.py output\release\flashloader.elf flashloader.bin flashloader_image.c

arm-none-eabi-objcopy -I elf32-littlearm -O binary output\debug\flashloader.elf flashloader.bin
python ..\..\..\..\bin\create_fl_image_mdk.py output\debug\flashloader.elf flashloader.bin flashloader_image.c