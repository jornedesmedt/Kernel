;Setup the Global Descriptor Table
section .text

global gdt_flush
gdt_flush:
    mov eax, [esp+4]
    lgdt [eax]
;reload data segment register
    mov ax, 0x10 ;0x10 points to new data selector
    mov ds, ax ;data segement register
    mov es, ax ;extra data
    mov fs, ax ;more extra data
    mov gs, ax ;even more extra data
    mov ss, ax ;stack segment
    jmp 0x08:.flush
.flush:
    ret