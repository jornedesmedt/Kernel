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
echo paging.asm
nasm -felf32 $src/mmu/paging.asm -o /root/compile/obj/paging.o
compile_cpp $src/kernel.cpp $obj/kernel.o
compile_cpp $src/terminal/terminal.cpp $obj/terminal.o
compile_cpp $src/misc/string.cpp $obj/string.o
compile_cpp $src/vga/vga.cpp $obj/vga.o
compile_cpp $src/mmu/paging.cpp $obj/paging2.o
compile_cpp $src/test/testclass.cpp $obj/testclass.o
compile_cpp $src/misc/int_to_hex.cpp $obj/int_to_hex.o
compile_cpp $src/mmu/mm_explore.cpp $obj/mm_explore.o
compile_cpp $src/mmu/mm.cpp $obj/mm.o


#Link object files
echo Linking...
$TARGET-gcc -T $linker -o $bin/kernel.bin -ffreestanding -O2 -nostdlib $obj/boot.o $obj/mm.o $obj/int_to_hex.o $obj/mm_explore.o $obj/paging.o $obj/string.o $obj/paging2.o $obj/vga.o $obj/terminal.o $obj/testclass.o $obj/kernel.o -lgcc

#Create iso
echo Create iso...
echo Copying grub.cfg
cp $dir/grub.cfg $iso/boot/grub
echo Copying grub.cfg
cp $bin/kernel.bin $iso/boot
echo grub-mkrescue
grub-mkrescue -o barebones.iso $iso