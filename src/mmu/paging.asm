section .text
global setup_paging
setup_paging:
    push ebp
    mov ebp, esp
    ;Put the address of the page directory in CR3
    mov eax, [ebp] ;Get the page_directory_address parameter from the memory address stored in ebp (whatever was on top of the stack before pushing ebp earlier)
    mov cr3, eax
    ;Enable paging
    mov eax, cr0 ;Copy CR0 to EAX
    or eax, 0x80000000 ; SET bit 31 for the value in EAX
    mov cr0, eax ; Copy the changed value back to CR0
    ;cleanup to exit function
    mov esp, ebp
    pop ebp
    ret