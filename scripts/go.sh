#!/bin/bash

#nasm -f elf -o loader.o loader.s
#i586-elf-g++ -o kmain.o -c kmain.cpp -Wall -Wextra -nostdlib -fno-exceptions -fno-rtti -fno-stack-protector
#i586-elf-g++ -T linker.ld -o kernel.bin -ffreestanding -nostdlib -fno-exceptions -fno-rtti -fno-stack-protector loader.o kmain.o

#cd src
#make kernel
#cd ..

cat bochs/stage1 bochs/stage2 >tmp.img
wc -c tmp.img >tmp.num
n=$(cut -d " " -f 1 tmp.num)

dd if=/dev/zero of=tmp.pad bs=1 count=$((102400-n))
cat tmp.pad >>floppy.img

mv tmp.img bochs/floppy.img

cd src
make clean
cd ..

rm tmp.*

