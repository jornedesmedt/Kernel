; Declare constants for the multiboot header.
MBALIGN  equ  1<<0              ; align loaded modules on page boundaries
MEMINFO  equ  1<<1              ; provide memory map
FLAGS    equ  MBALIGN | MEMINFO ; this is the Multiboot 'flag' field
MAGIC    equ  0x1BADB002        ; 'magic number' lets bootloader find the header
CHECKSUM equ -(MAGIC + FLAGS)   ; checksum of above, to prove we are multiboot

KERNEL_VIRTUAL_BASE equ 0xC0000000 ;3GB
KERNEL_PAGE_NUMBER equ (KERNEL_VIRTUAL_BASE >> 22) ;page directory index of kernel's 4MB PTE

section .data
align 0x1000
BootPageDirectory:
	;Set up a page directory entry to identity map the first 4MB of of the 32-bit address space
	; only the following bits are set: 7- Page size (4MB),  1-read/write, 0, present
	dd 0x00000083 ;flags
	times (KERNEL_PAGE_NUMBER - 1) dd 0 ;Number of pages before kernel space
	;This page directory entry defines a 4MB page containing the kernel
	dd 0x00000083
	times (1024 - KERNEL_PAGE_NUMBER - 1) dd 0 ;Pages after kernel image
 
;Declare the multiboot header (loaded in .text section by linker, before other.text sections)
section .multiboot
align 4
	dd MAGIC
	dd FLAGS
	dd CHECKSUM
 
;Reserve stack space
section .bss
align 4
stack_bottom:
resb 16384 ; 16 KiB
global stack_top:
stack_top:
 
 
 
; The linker script specifies _start as the entry point to the kernel and the
; bootloader will jump to this position once the kernel has been loaded. It
; doesn't make sense to return from this function as the bootloader is gone.
; Declare _start as a function symbol with the given symbol size.
section .text

global _start; :function (_start.end - _start)
_start:

	mov ecx, (BootPageDirectory - KERNEL_VIRTUAL_BASE);
	mov cr3, ecx ;Load page directory base register

	mov ecx, cr4;
	or ecx, 0x00000010 ;Set PSE bit to enable 4MB pages
	mov cr4, ecx

	mov ecx, cr0
	or ecx, 0x80000000
	mov cr0, ecx ;Set PG bit to enable paging.

	lea ecx, [StartInHigherHalf]
	jmp ecx

StartInHigherHalf:
	;Unmap identity mapped first 4MB of physical address space.
	;mov dword[BootPageDirectory], 0
	;invlpg [0]
	;From now on, paging should be enabled. The first 4MB of physical addres space is mapped to KERNEL_VIRTUAL_BASE (3GB)

	; The bootloader has loaded us into 32-bit protected mode on a x86
	; machine. Interrupts are disabled. Paging is disabled. The processor
	; state is as defined in the multiboot standard. The kernel has full
	; control of the CPU. The kernel can only make use of hardware features
	; and any code it provides as part of itself. There's no printf
	; function, unless the kernel provides its own <stdio.h> header and a
	; printf implementation. There are no security restrictions, no
	; safeguards, no debugging mechanisms, only what the kernel provides
	; itself. It has absolute and complete power over the
	; machine.
 
	; To set up a stack, we set the esp register to point to the top of our
	; stack (as it grows downwards on x86 systems). This is necessarily done
	; in assembly as languages such as C cannot function without a stack.
	mov esp, stack_top
 
	; This is a good place to initialize crucial processor state before the
	; high-level kernel is entered. It's best to minimize the early
	; environment where crucial features are offline. Note that the
	; processor is not fully initialized yet: Features such as floating
	; point instructions and instruction set extensions are not initialized
	; yet. The GDT should be loaded here. Paging should be enabled here.
	; C++ features such as global constructors and exceptions will require
	; runtime support to work as well.
 
	; Enter the high-level kernel. The ABI requires the stack is 16-byte
	; aligned at the time of the call instruction (which afterwards pushes
	; the return pointer of size 4 bytes). The stack was originally 16-byte
	; aligned above and we've since pushed a multiple of 16 bytes to the
	; stack since (pushed 0 bytes so far) and the alignment is thus
	; preserved and the call is well defined.
    ; note, that if you are building on Windows, C functions may have "_" prefix in assembly: _kernel_main
	extern kernel_main
	push eax ;pass multiboot magic number
	add ebx, KERNEL_VIRTUAL_BASE
	push ebx ;pass multiboot info structure. (physical address, may not be in the first 4MB)
	cli
	call kernel_main
 
	; If the system has nothing more to do, put the computer into an
	; infinite loop. To do that:
	; 1) Disable interrupts with cli (clear interrupt enable in eflags).
	;    They are already disabled by the bootloader, so this is not needed.
	;    Mind that you might later enable interrupts and return from
	;    kernel_main (which is sort of nonsensical to do).
	; 2) Wait for the next interrupt to arrive with hlt (halt instruction).
	;    Since they are disabled, this will lock up the computer.
	; 3) Jump to the hlt instruction if it ever wakes up due to a
	;    non-maskable interrupt occurring or due to system management mode.
	cli
.hang:	hlt
	jmp .hang
.end: