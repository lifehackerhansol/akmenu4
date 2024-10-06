set -e

mkdir -p data
make -C nds-bootloader LOADBIN=$PWD/data/load.bin
make
