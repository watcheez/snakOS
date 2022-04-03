    mov ah, 0x0e                ; To set in teletype
    mov al, 52                 ; To keep the letter to print

    push ax
    xor ax, ax

    pop ax

    int 0x10        

    jmp $


            ; The boot sector is 512 bytes long

    times 510-($-$$) db 0       ; Complete the rest of 00
    db 0x55, 0xaa               ; Finishes by "55aa"