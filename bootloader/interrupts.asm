[bits 32]
extern irq0_handler

global irq0_stub
irq0_stub:
    pusha
    mov ax, 0x10      ; reload data segment
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    call irq0_handler
    popa
    iret