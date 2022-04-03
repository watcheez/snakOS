[org 0x7c00]
KERNEL_LOCATION equ 0x1000

    
    mov [BOOT_DISK], dl

    xor ax, ax 
    mov es, ax                  ; here extra-segment is 0 since 0x7e00 fits in bx
    mov ds, ax
    mov bp, 0x8000
    mov sp, bp

    ; 1.    Disk: diskNum
    ; 2.    C = 0, H = 0, S = 2
    ; 3.    Sectors: 1
    ; 4.    Address: 0x7e00 -> right below boot code

    mov bx, KERNEL_LOCATION     ; pointer of the disk 

    mov ah, 0x02                    ; must be
    mov al, 0x30                    ; number of sectors we want to read  // may be changed
    mov ch, 0x00                    ; cylinder number
    mov dh, 0x00                    ; head number
    mov cl, 0x02                    ; sector number
    mov dl, [BOOT_DISK]             ; drive number we saved in a variable                  
    int 0x13

    mov ah, 0x0e
    mov al, 'E'
    int 0x10
    jc end                          ; handle error

    mov ah, 0x00
    mov al, 0x03                    ; set text mod (0x03) / set vga mod (0x0d)
    int 0x10                        ; text mode => clear 

; =================
;  SETTING GDT UP:
; =================

CODE_SEG equ GDT_code - GDT_Start           ; equ is used to set constants
DATA_SEG equ GDT_data - GDT_Start           ; equals 0x20


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

end:
    jmp $

BOOT_DISK: db 0


GDT_Start:              ; must be at the end of the REAL CODE
    GDT_null:
        dd 0            ; four times -> 00 00 00 00
        dd 0            ; four times -> 00 00 00 00
    GDT_code:
        dw 0xffff       ; first 16 bits of the limit
        dw 0            ; 16 bits +
        db 0            ; 8 bits = first 24 bits of the base
        db 0b10011010     ; p,p,t, Type flags
        db 0b11001111     ; Other flags + limit (last four bits)
        db 0            ; Last 8 bits of base
    GDT_data:
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

[bits 32]
start_protected_mode:
    mov ax, DATA_SEG        ; set up segment registers and stack

    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov ebp, 0x90000        ;  32 bit stack base pointer 
    mov esp, ebp

    jmp KERNEL_LOCATION

    times 510-($-$$) db 0
    dw 0xaa55