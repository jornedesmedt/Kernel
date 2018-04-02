%macro idt_entry 3
    dw (%1 >> 16) ;offset 16:31
    db %2 ;Present, DPL (2 bits), Storage segment, - gate type (4 bits)
    db 0 ;Unused. always has to be zero
    dw %3 ;Selector
    dw %1 ;Offset 0-15
%endmacro

%macro isr_wrapper 1
    pushad
    cld
    call %1
    popad
    iret
%endmacro

section .idt_text
extern divide_by_zero
int_0:
isr_wrapper divide_by_zero


lidt [idt_descriptor]

IDT:
    ;idt entries
    idt_entry [int_0], 11101111b, 0xc001

idt_descriptor:
    dw idt_descriptor - IDT - 1; size
    dd IDT

sidt [idt_descriptor]