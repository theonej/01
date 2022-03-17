#assumes that u-boot is installed at ../u-boot

../u-boot/tools/mkimage -A arm -C none -T kernel -a 0x60000000 -e 0x60000000 -d ./bin/01.bin ./bin/bare-arm.uimg