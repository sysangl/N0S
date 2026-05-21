[bits 64]
section .text
global _start

extern kmain

_start:
    ; Write XYZ to confirm we got here
    mov rdi, 0xB8000
    mov byte [rdi],   'X'
    mov byte [rdi+1], 0x1F
    mov byte [rdi+2], 'Y'
    mov byte [rdi+3], 0x1F
    mov byte [rdi+4], 'Z'
    mov byte [rdi+5], 0x1F


    mov rsp, 0x200000
    mov rbp, rsp
    cld
    call kmain

kmain_debug:
    ; Show we're about to call kmain
    mov rdi, 0xB8000
    mov byte [rdi+6], 'C'  ; Call
    mov byte [rdi+7], 0x2F
    mov byte [rdi+8], 'A'  ; About to
    mov byte [rdi+9], 0x2F
    
    call kmain
    ; If we get here, kmain returned
    mov byte [rdi+10], 'R'  ; Returned
    mov byte [rdi+11], 0x2F
    ret

hang:
    cli
    hlt
    jmp hang
