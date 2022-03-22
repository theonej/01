FILES = ./build/kernel.o 		\
		./build/startup.o		\
		./build/string.o		\
		./build/console.o		\
		./build/dependency.o	\
		./build/PL011.o

INCLUDES = -I./src

LDFLAGS += -L /usr/bin

FLAGS = -c 				\
		-g				\
		-Wall			\
		-nostdlib 		\
		-nostartfiles 	\
		-lgcc			\
		-lm
		

all: ./build/01.elf
	arm-none-eabi-objcopy -O binary ./build/01.elf ./bin/01.bin

./build/01.elf: $(FILES)
	arm-none-eabi-ld --verbose -L /usr/lib/gcc/arm-none-eabi/9.2.1 -L /usr/lib/arm-none-eabi/lib -T linker.ld $(FILES) -nostdlib -lm -lgcc -o ./build/01.elf

./build/kernel.o: ./src/kernel.c
	arm-none-eabi-gcc $(INCLUDES) $(FLAGS) -o ./build/kernel.o ./src/kernel.c

./build/startup.o: ./src/startup.s
	arm-none-eabi-as -o ./build/startup.o ./src/startup.s

./build/string.o: ./src/text/string.c
	arm-none-eabi-gcc $(FLAGS) -o ./build/string.o ./src/text/string.c

./build/console.o: ./src/text/console.c
	arm-none-eabi-gcc $(INCLUDES) $(FLAGS) -o ./build/console.o ./src/text/console.c

./build/dependency.o: ./src/dependency.c
	arm-none-eabi-gcc $(INCLUDES) $(FLAGS) -o ./build/dependency.o ./src/dependency.c

./build/PL011.o: ./src/hardware/uart/PL011/PL011.c
	arm-none-eabi-gcc $(INCLUDES) $(FLAGS)  -o ./build/PL011.o ./src/hardware/uart/PL011/PL011.c

clean:
	rm -rf ./bin/**
	rm -rf ./build/**