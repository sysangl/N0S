[bits 32]
[extern k_main]


global _start
_start:
    mov esp, 0x90000    ; safe fixed stack, below BIOS at 0xA0000


    sub ecx, edi
    xor eax, eax
    rep stosb

    call k_main
    jmp $