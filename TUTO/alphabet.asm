mov ah, 0x0e                ; To set in teletype
mov al, 'A'                 ; To keep the letter to print
int 0x10                    ; interrupt to ask the print

loop:
    test al, 1
    jz maj
    jnz min

min:
    add al, 0x21
    cmp al, 'z'
    int 0x10            
    je end
    jmp loop

maj:
    sub al, 0x1F
    cmp al, 'Z'
    int 0x10
    je end
    jmp loop

end:
    jmp $


        ; The boot sector is 512 bytes long

times 510-($-$$) db 0       ; Complete the rest of 00
db 0x55, 0xaa               ; Finishes by "55aa"