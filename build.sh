arm-none-eabi-as -o ./build/startup.o ./src/startup.s
arm-none-eabi-ld -o ./build/first-hang.elf ./build/startup.o
arm-none-eabi-objcopy -O binary ./build/first-hang.elf ./bin/first-hang.bin