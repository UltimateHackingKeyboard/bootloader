rem Pass in full path and Release|Debug to iar project directory
cd /d %1
ielftool --bin output\%2\flashloader.elf flashloader.bin
python ..\..\..\..\bin\create_fl_image.py output\%2\flashloader.elf flashloader.bin output\%2\flashloader_image.c
