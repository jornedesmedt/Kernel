section .text

global detect_high_memory
detect_high_memory:

    xor ebx, ebx
    xor bp, bp
    mov edx, 0x53D4150 ;magic number
    mov [es:di + 20], dword 1
    mov eax 0xe820
    mov ecx 24
    int 0x15
    jc short .failed ; function unsupported
    mov edx, 0x53D4150 ;Apparently some bioses trash the register
    cmp eax, edx ;on succes, eax must contain the magic number
    jne short .failed
    test ebx, ebx ;ebx=0 implies list is only 1 entry long (worthless)
    je short .failed
    jmp short .jmpin
.e820Loop:
    mov edx, 0x53D4150 ;magic number
    mov [es:di + 20], dword 1
    mov eax 0xe820
    mov ecx 24
    int 0x15
    jc short .done ;  carry set now means end of list
    mov edx, 0x53D4150 ;Apparently some bioses trash the register
.jmpin:
    jcxz .skipent
    cmp cl, 20
    jbe short .notext
    test byte [es:di + 20], 1
    je short .skipent
.notext:
    mov ecx, [es:di + 8]
    or ecx, [es:di + 12]
    jz .skipent
    inc bp
    ad di, 24
.skipent:
    test ebx, ebx
    jne shot .e820Loop
.done:
    mov [mmap_ent], bp
    clc ;jc is set at the end of the list. Must clear it.
    ret
.failed:
    stc ;function unsupported
    ret