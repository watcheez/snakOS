[org 0x7c00]                ; To setup the origin of the pointer

    mov bx, buffer
    mov cx, 0

scan:
    mov ah, 0
    int 0x16
    cmp al, 0x0d
    je printa
    mov [bx], al
    inc cx
    inc bx
    cmp cx, 10
    je printa
    jmp scan

printa:
    mov ah, 0x0e
    mov bx, buffer
    jmp printString

printString:
    mov al, [bx]
    cmp al, 0
    je end
    int 0x10                
    inc bx
    jmp printString

end:
    jmp $

buffer:
    times 10 db 0

        ; The boot sector is 512 bytes long
    times 510-($-$$) db 0       ; Complete the rest of 00
    db 0x55, 0xaa               ; Finishes by "55aa"