#!/bin/sh

dir="/root/compile"
src="$dir/src"
obj="$dir/obj"
bin="$dir/bin"
linker="$dir/linker/linker.ld"
iso="$dir/iso"

cd $dir

#Create folders
echo Create folders...
mkdir -p $obj
mkdir -p $bin
mkdir -p $iso/boot/grub

compile_cpp()
{
    echo $1
    $TARGET-g++ -c $1 -o $2 -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti
}
#Compile sources
echo Compile sources
echo boot.asm
nasm -felf32 $src/boot.asm -o /root/compile/obj/boot.o
compile_cpp $src/kernel.cpp $obj/kernel.o
compile_cpp $src/terminal/terminal.cpp $obj/terminal.o
compile_cpp $src/misc/string.cpp $obj/string.o

#Link object files
echo Linking...
$TARGET-gcc -T $linker -o $bin/kernel.bin -ffreestanding -O2 -nostdlib $obj/boot.o $obj/string.o $obj/terminal.o $obj/kernel.o -lgcc

#Create iso
echo Create iso...
echo Copying grub.cfg
cp $dir/grub.cfg $iso/boot/grub
echo Copying grub.cfg
cp $bin/kernel.bin $iso/boot
echo grub-mkrescue
grub-mkrescue -o barebones.iso $iso