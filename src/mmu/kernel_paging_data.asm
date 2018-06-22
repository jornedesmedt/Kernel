KERNEL_VIRTUAL_BASE equ 0xC0000000 ;3GB
KERNEL_PAGE_DIRECTORY_NUMBER equ (KERNEL_VIRTUAL_BASE >> 22) ;page directory index of kernel's 4MB PTE
KERNEL_PAGE_TABLE_NUMBER equi (256*1024)

section .data

align 0x1000
global KERNEL_PAGE_DIRECTORY
KERNEL_PAGE_DIRECTORY:
    dd 0 ;Entry for page table for identity mapped pages, unmap later
    times (KERNEL_PAGE_DIRECTORY_NUMBER - 1) dd 0 ;Empty page table entries, before kernel space
    dd 0 ;Same value as identity mapped pages, keep after unmapping the other
    times (1024 - KERNEL_PAGE_DIRECTORY_NUMBER - 1) dd 0 ;Pages after kernel image, also empty, for now

align 0x1000
global KERNEL_PAGE_TABLES
KERNEL_PAGE_TABLES:
    times (256*1024) dd 0; reserve space for 256 page table entries covering 1 GB worth of memory

section .text

setup_paging:
    mov ecx, (KERNEL_PAGE_DIRECTORY - KERNEL_VIRTUAL_BASE);
    mov cr3, ecx ;Load page directory base register

    mov ecx, cr4;
    or ecx, 0x00000000 ;4KB pages
    mov cr4, ecx

    mov ecx, cr0
    or ecx, 0x80000000
    mov cr0, ecx ;Set PG bit to enable paging.

    lea ecx, [StartInHigherHalf]
    jmp ecx

StartInHigherHalf:
	;Unmap identity mapped first 4MB of physical address space.
	mov dword [KERNEL_PAGE_DIRECTORY], 0
	invlpg [0]
	;From now on, paging should be enabled. The first 4MB of physical addres space is mapped to KERNEL_VIRTUAL_BASE (3GB)