CC = i586-elf-g++
LD = $(CC) -T

CXXFLAGS = -Wall -Wextra -nostdlib -fno-exceptions -fno-rtti -fno-stack-protector
LDFLAGS = -ffreestanding -nostdlib -fno-exceptions -fno-rtti -fno-stack-protector

SRCS = $(wildcard cpp/*.cpp)
OBJS = $(SRCS:.cpp=.o)

kernel: kmain.cpp loader.s objects
	mv *.o cpp/
	nasm -f elf -o loader.o loader.s
	nasm -f elf -o gdt_flush.o gdt_flush.s
	nasm -f elf -o isr.o isr.s
	$(CC) -c kmain.cpp $(CXXFLAGS)
	$(LD) linker.ld -o kernel.bin $(LDFLAGS) loader.o kmain.o $(OBJS) gdt_flush.o isr.o -Wl,-Map,prog.map

objects: $(SRCS)
	cd cpp
	$(CC) $^ -c $(CXXFLAGS) -l gdt_flush.o -l isr.o
	cd ..

clean:
	rm *.o
	rm cpp/*.o
	rm kernel.bin
