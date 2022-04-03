[org 0x7c00]
    mov [_diskNum], dl

    xor ax, ax 
    mov es, ax                  ; here extra-segment is 0 since 0x7e00 fits in bx
    mov ds, ax
    mov bp, 0x8000
    mov sp, bp

    ; 1.    Disk: diskNum
    ; 2.    C = 0, H = 0, S = 2
    ; 3.    Sectors: 1
    ; 4.    Address: 0x7e00 -> right below boot code

    mov bx, 0x7e00              ; pointer of the disk 
    mov ah, 2                   ; must be
    mov al, 1                   ; number of sectors we want to read
    mov ch, 0                   ; cylinder number
    mov cl, 2                   ; sector number
    mov dh, 0                   ; head number
    mov dl, [_diskNum]           ; drive number we saved in a variable                  
    int 0x13


    call __handleDiskError
    jc end

;    mov ah, 0x0e
 ;   mov al, [0x7e00]
  ;  int 0x10                     ; prints 'A'

end:
    jmp $


; =============
;   CALLS
; =============


__handleDiskError:
    jnc carryDone
    mov bx, _carryMessage 
    call __printString
carryDone:
    mov bx, _alMessage
    mov ch, 1
    call __printString
    xor ah, ah
    call __printInt
    mov cl, 43
    call __printEndl
    int 0x10
    ret


__printInt:                   ; Parameter in ax
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

__printString:
    mov ah, 0x0e
    xor cl, cl
printingLoop:
    mov al, [bx]
    cmp al, 0
    je pend
    int 0x10
    inc bx
    inc cl
    jmp printingLoop
pend:
    cmp ch, 1
    je  retEnd
    call __printEndl
retEnd:
    ret

__printEndl:
    mov ah, 0x0e
    mov al, 0x0a
    int 0x10
backLoop:
    cmp cl, 0
    je end_printEndl
    dec cl
    mov al, 0x08
    int 0x10
    jmp backLoop
end_printEndl:
    ret


_diskNum:
    db 0

_carryMessage:
    db "A problem happend while creating the disk", 0x00 

_alMessage:
    db "Number of sectors read by the procedure : ", 0x00
   
    times 510-($-$$) db 0       ; Complete the rest of 00
    db 0x55, 0xaa               ; Finishes by "55aa"

    times 512 db 'A' ; filling one sector with 'A's