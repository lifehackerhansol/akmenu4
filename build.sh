mkdir arm9/data
make -C nds-bootloader LOADBIN=$PWD/arm9/data/load.bin
make
