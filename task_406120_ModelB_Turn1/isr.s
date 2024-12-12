section .data
    msg db "Hello, Assemy ISR!", 0xA
    msg_len equ $ - msg

section .text
    global _isr_handler

_isr_handler:
    cli

    push eax
    push ebx
    push ecx
    push edx

    mov eax, 4      ; sys_write
    mov ebx, 1      ; stdout
    mov ecx, msg
    mov edx, msg_len
    int 0x80        ; Linux 32-bit syscall interrupt

    pop edx
    pop ecx
    pop ebx
    pop eax

    sti
    iret
