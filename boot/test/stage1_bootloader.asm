[BITS 16]
[ORG 0x7C00]
start:
    ; 1. Initialize segment registers to 0
    xor ax, ax
    mov ds, ax
    mov es, ax

    ; 2. Print initial message
    mov si, msg
    call print_string

    ; 3. Configure and call read_sector to load Sector 2 to 0x0500
    mov ax, 0x0000
    mov es, ax          ; Destination Segment ES=0x0000
    mov bx, 0x0500      ; Destination Offset BX=0x0500
    mov dl, 0x00        ; Drive 0 (Floppy)
    mov ch, 0x00        ; Cylinder 0
    mov cl, 0x02        ; Sector 2
    mov dh, 0x00        ; Head 0
    call read_sector

    ; 4. Print the loaded data (at 0x0500)
    mov si, 0x0500
    call print_string

    ; 5. Loop forever (halt)
    jmp $

msg db "Reading sector 2...", 0
%include "asm/print.asm"
%include "asm/disk_read.asm"

; Boot sector padding and signature
times 510 - ($ - $$) db 0
dw 0xAA55