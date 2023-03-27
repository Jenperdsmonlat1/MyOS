org 0x7c00

_start:

    mov ah, 0x00
    mov al, 0x13
    int 0x10

    xor cx, cx

    mov bl, 2
    call .new_line

.new_line:

    cmp cx, 320
    je .finish

    mov ah, 0x0c
    mov al, bl
    mov cx, cx
    mov dx, 66
    int 0x10
    inc cx

    jmp .new_line

.finish:

    ret

times 510 - ($-$$) db 0
dw 0xaa55
