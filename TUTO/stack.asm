[org 0x7c00]        

    mov bp, sp
inputCharRead:
    mov ah, 0
    int 0x16
    cmp al, 0x0d
    je printInputs
    push ax
    jmp inputCharRead

printInputs:
    mov bx, bp
    stepInput:
        dec bx
        dec bx
        mov ax, [bx]
        mov ah, 0x0e
        int 0x10
        cmp bx, sp
        jne stepInput

empty:
    pop ax
    cmp bp, sp
    jne empty

    mov ax, 123
    call printInt

    jmp $

printInt:                   ; Parameter in ax
    mov bp, sp
divide:
    mov ch, 0x0a
    div ch
    mov cx, ax
    add ah, 48
    mov al, ah
    mov ah, 0x0e
    push ax
    cmp cl, 0
    je printing
    xor ax, ax
    mov al, cl
    jmp divide
printing:
    pop ax
    int 0x10
    cmp sp, bp
    jne printing
    ret

        ; The boot sector is 512 bytes long

times 510-($-$$) db 0       ; Complete the rest of 00
db 0x55, 0xaa               ; Finishes by "55aa"