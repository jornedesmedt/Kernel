#!/bin/sh

dir="/root/compile"
src="$dir/src"
obj="$dir/obj"
bin="$dir/bin"
linker="$dir/linker/linker.ld"
iso="$dir/iso"

cd $dir

#Create folders
mkdir -p $obj
mkdir -p $bin
mkdir -p $iso/boot/grub

#Compile sources
nasm -felf32 $src/boot.asm -o /root/compile/obj/boot.o
$TARGET-g++ -c $src/kernel.cpp -o $obj/kernel.o -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti

#Link object files
$TARGET-gcc -T $linker -o $bin/kernel.bin -ffreestanding -O2 -nostdlib $obj/boot.o $obj/kernel.o -lgcc

#Create iso
cp $dir/grub.cfg $iso/boot/grub
cp $bin/kernel.bin $iso/boot
grub-mkrescue -o barebones.iso $iso