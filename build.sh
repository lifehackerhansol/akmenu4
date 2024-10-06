mkdir arm9/data
make -C nds-bootloader LOADBIN=$PWD/arm9/data/load.bin

if [ $1 == "DSI" ]; then
    make DSI=1
else
    make
fi
