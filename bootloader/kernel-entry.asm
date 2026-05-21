[bits 32]
[extern kmain]
;[extern _enable_paging]


global _start
_start:
    mov esp, 0x200000    ; safe fixed stack, below BIOS at 0xA0000

    sub ecx, edi
    xor eax, eax
    rep stosb
    ;call _enable_paging
    call kmain
    jmp $
