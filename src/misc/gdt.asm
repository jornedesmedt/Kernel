;Setup the Global Descriptor Table
section .gdt_text
lgdt [gdt_descriptor]

GDT:
    ;gdt entries
    .Null: equ $ - GDT
        dw 0 ;Base 0:15
        dw 0 ;Limit 0:15
        db 0 ;Base 24:31
        db 0 ;Flags - Limit 16:19
        db 0 ;Access byte
        db 0 ;Base 16:32

    .Code: equ $ - GDT
        dw 0
        dw 0xffff
        db 0
        db 11001111b ;flags(first 4 bits - limit 16:19)
        db 0x9a
        db 0

    .Data: equ $ - GDT
       dw 0
        dw 0xffff
        db 0
        db 11001111b ;flags(first 4 bits - limit 16:19)
        db 0x92
        db 0

gdt_descriptor:
    dw gdt_descriptor - GDT - 1 ;Size
    dd GDT ;offset. Use dq ub 64 bit

;section .gdt_text
reloadSegments:
;reload cs register containing code selector
jmp 0x08:.reload_CS ;0x08 points to the new code selector

.reload_CS:
;reload data segment register
    mov ax, 0x10 ;0x10 points to new data selector
    mov ds, ax ;data segement register
    mov es, ax ;extra data
    mov fs, ax ;more extra data
    mov gs, ax ;even more extra data
    mov ss, ax ;stack segment
    ret