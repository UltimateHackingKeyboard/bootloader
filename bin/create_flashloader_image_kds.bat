rem Pass in full path and Release|Debug to iar project directory
cd /d %1
arm-none-eabi-objcopy -I elf32-littlearm -O binary flashloader.elf flashloader.bin
python ..\..\..\..\..\bin\create_fl_image_kds.py flashloader.elf flashloader.bin flashloader_image.c

