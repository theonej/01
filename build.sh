#arm-none-eabi-as -o ./build/startup.o ./src/startup.s

#arm-none-eabi-gcc -c -nostdlib -nostartfiles -lgcc -o ./build/kernel.o ./src/kernel.c
#arm-none-eabi-gcc -c -nostdlib -nostartfiles -lgcc -o ./build/text/string.o ./src/text/string.c
#arm-none-eabi-gcc -c -nostdlib -nostartfiles -lgcc -o ./build/text/console.o ./src/text/console.c

#arm-none-eabi-ld  -T linker.ld -o ./build/01.elf ./build/startup.o ./build/kernel.o ./build/text/string.o ./build/text/console.o
#arm-none-eabi-objcopy -O binary ./build/01.elf ./bin/01.bin

make all

echo -e 'creating image\n'

./create-img.sh
echo -e 'image created.  creating sd card\n'

./create-sd-img.sh ./bin/sdcard.img ./bin/bare-arm.uimg