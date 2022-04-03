[org 0x7c00]

mov [BOOT_DISK], dl


;       - base: 0 (32 bit)
;       - limit: 0xfffff
;       - pres, priv, type  = 1001
;       - Type flags        = 1010       |          = 0010 for data_descriptor
;       - Other flags       = 1100

    cli                         ; disable all interrupts
    lgdt [GDT_Descriptor]       ; load the LGDT

; change last bit of cr0 to 1 :
    mov eax, cr0
    or eax, 1
    mov cr0, eax                ; entered in 32 bit mode !!

; far jump (jmp to other segment) :
    jmp CODE_SEG:start_protected_mode

GDT_Start:              ; must be at the end of the REAL CODE
    null_descriptor:
        dd 0            ; four times -> 00 00 00 00
        dd 0            ; four times -> 00 00 00 00
    code_descriptor:
        dw 0xffff       ; first 16 bits of the limit
        dw 0            ; 16 bits +
        db 0            ; 8 bits = first 24 bits of the base
        db 0b10011010     ; p,p,t, Type flags
        db 0b11001111     ; Other flags + limit (last four bits)
        db 0            ; Last 8 bits of base
    data_descriptor:
        dw 0xffff       ; first 16 bits of the limit
        dw 0            ; 16 bits +
        db 0            ; 8 bits = first 24 bits of the base
        db 0b10010010     ; p,p,t, Type flags -- CHANGES HERE
        db 0b11001111     ; Other flags + limit (last four bits)
        db 0            ; Last 8 bits of base
GDT_End:
GDT_Descriptor:
    dw GDT_End - GDT_Start - 1      ; size
    dd GDT_Start                    ; start

CODE_SEG equ code_descriptor - GDT_Start        ; equ is used to set constants
DATA_SEG equ data_descriptor - GDT_Start

; setup done...

[bits 32]
start_protected_mode:
    ; write protected mode code here...
    call f_clear

    mov bh, 0x0f
    mov bl, 254
    mov ch, 2
    mov cl, 1
    call f_write_char

    mov bh, 0x0f
    mov bl, 254
    mov ch, 3
    mov cl, 2
    call f_write_char

    mov bh, 0x0e
    mov bl, 254
    mov ch, 3
    mov cl, 3
    call f_write_char

    mov bh, 0x0e
    mov bl, 254
    mov ch, 2
    mov cl, 2
    call f_write_char

    mov bh, 0x0e
    mov bl, 254
    mov ch, 1
    mov cl, 1
    call f_write_char

    mov bh, 0x0e
    mov bl, 254
    mov ch, 0
    mov cl, 0
    call f_write_char

    jmp $                                            

f_write_char:                    ; ch: x | cl: y | bh: color | bl: 254
    xor eax, eax
    mov al, [WIDTH]
    mul cl
    xor edx, edx
    mov dl, ch
    add eax, edx
    add eax, edx
    mov edx, GRAPHIC_POS
    add eax, edx
    mov [eax], bx
    ret

f_clear:
    mov cx, 0xff
    mov eax, [TOTAL]
    mov ebx, GRAPHIC_POS
    add eax, ebx    
_clear_loop:
    mov [ebx], cx
    inc ebx
    inc ebx
    cmp ebx, eax
    jb _clear_loop
    ret




BOOT_DISK: db 0
WIDTH: db 160               ; 80 * (1 byte color + 1 byte char)
HEIGHT: db 50               ; 25 * (1 byte color + 1 byte char)
TOTAL: dd 3999
GRAPHIC_POS equ 0xb8000

    times 510-($-$$) db 0       ; Complete the rest of 00
    db 0x55, 0xaa               ; Finishes by "55aa"