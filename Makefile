FILES = ./build/kernel.o 		\
		./build/startup.o		\
		./build/text/string.o	\
		./build/text/console.o	\

INCLUDES = -I./src

FLAGS = -c 				\
		-nostdlib 		\
		-nostartfiles 	\
		-lgcc

all: ./build/01.elf
	arm-none-eabi-objcopy -O binary ./build/01.elf ./bin/01.bin

./build/01.elf: $(FILES)
	arm-none-eabi-ld  -T linker.ld -o ./build/01.elf $(FILES)

./build/kernel.o: ./src/kernel.c
	arm-none-eabi-gcc $(FLAGS) -o ./build/kernel.o ./src/kernel.c

./build/startup.o: ./src/startup.s
	arm-none-eabi-as -o ./build/startup.o ./src/startup.s

./build/text/string.o: ./src/text/string.c
	arm-none-eabi-gcc $(FLAGS) -o ./build/text/string.o ./src/text/string.c

./build/text/console.o: ./src/text/console.c
	arm-none-eabi-gcc $(FLAGS) -o ./build/text/console.o ./src/text/console.c

clean:
	rm -r ./bin/*.bin
	rm -r ./bin/*.uimg
	rm -r ./bin/*.img
	rm -r ./build/*.o
	rm -r ./build/*.elf
	rm -r ./build/**/*.o