[BITS 32]

GLOBAL drive_write

section .text
drive_write:
    mov eax, 0xe820
    xor ebx, ebx
    mov ecx, 24
    mov edx, 0x534d4150
    int 0x15
    ;int 0x13
    ret