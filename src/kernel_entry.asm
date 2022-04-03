[bits 32]
[extern main]

    call main
    jmp $

global idt_load
extern idtp
idt_load:
    lidt [idtp]
    ret


; ============
;  INTERRUPTS
; ============
    global isr0
    global isr1
    global isr2
    global isr3
    global isr4
    global isr5
    global isr6
    global isr7
    global isr8
    global isr9
    global isr10
    global isr11
    global isr12
    global isr13
    global isr14
    global isr15
    global isr16
    global isr17
    global isr18
    global isr19
    global isr20
    global isr21
    global isr22
    global isr23
    global isr24
    global isr25
    global isr26
    global isr27
    global isr28
    global isr29
    global isr30
    global isr31

; Divide By Zero Exception
isr0:                  ; ERROR CODE: NO
    cli
    push byte 0         ; A normal ISR stud pops a dumyy code to keep an uniform stack frame
    push byte 0
    jmp isr_common_stub

; Debug Exception
isr1:                  ; ERROR CODE: NO
    cli
    push byte 0         
    push byte 1
    jmp isr_common_stub

; Non Maskable Interrupt Exception
isr2:                  ; ERROR CODE: NO
    cli
    push byte 0         
    push byte 2
    jmp isr_common_stub

; Breakpoint Exception
isr3:                  ; ERROR CODE: NO
    cli
    push byte 0         
    push byte 3
    jmp isr_common_stub

; Into Detected Overflow Exception
isr4:                  ; ERROR CODE: NO
    cli
    push byte 0         
    push byte 4
    jmp isr_common_stub

; Out of Bounds Exception
isr5:                  ; ERROR CODE: NO
    cli
    push byte 0         
    push byte 5
    jmp isr_common_stub

; Invalid Opcode Exception
isr6:                  ; ERROR CODE: NO
    cli
    push byte 0         
    push byte 6
    jmp isr_common_stub

; No Coprocessor Exception
isr7:                  ; ERROR CODE: NO
    cli
    push byte 0         
    push byte 7
    jmp isr_common_stub

; Double Fault Exception
isr8:                  ; ERROR CODE: YES -> no dummy push
    cli
    push byte 2
    jmp isr_common_stub

; Coprocessor Segment Overrun Exception
isr9:                  ; ERROR CODE: NO
    cli
    push byte 0         
    push byte 9
    jmp isr_common_stub

; Bad TSS Exception
isr10:                  ; ERROR CODE: YES
    cli
    push byte 10
    jmp isr_common_stub

; Segment Not Present Exception
isr11:                  ; ERROR CODE: YES
    cli
    push byte 11
    jmp isr_common_stub

; Stack Fault Exception
isr12:                  ; ERROR CODE: YES
    cli
    push byte 12
    jmp isr_common_stub

; General Protection Fault Exception
isr13:                  ; ERROR CODE: YES
    cli
    push byte 13
    jmp isr_common_stub

; Page Fault Exception
isr14:                  ; ERROR CODE: YES
    cli
    push byte 14
    jmp isr_common_stub

; Unknown Interrupt Exception
isr15:                  ; ERROR CODE: NO
    cli
    push byte 0
    push byte 15
    jmp isr_common_stub

; Coprocessor Fault Exception
isr16:                  ; ERROR CODE: NO
    cli
    push byte 0
    push byte 16
    jmp isr_common_stub

; Alignement Check Exception (486+)
isr17:                  ; ERROR CODE: NO
    cli
    push byte 0
    push byte 17
    jmp isr_common_stub

; Machine Check Exception (Pentium/586+)
isr18:                  ; ERROR CODE: NO
    cli
    push byte 0
    push byte 18
    jmp isr_common_stub

; Reserved Exception
isr19:                  ; ERROR CODE: NO
	cli
	push byte 0
	push byte 19 
	jmp isr_common_stub

; Reserved Exception
isr20:                  ; ERROR CODE: NO
	cli
	push byte 0
	push byte 20 
	jmp isr_common_stub

; Reserved Exception
isr21:                  ; ERROR CODE: NO
	cli
	push byte 0
	push byte 21 
	jmp isr_common_stub

; Reserved Exception
isr22:                  ; ERROR CODE: NO
	cli
	push byte 0
	push byte 22 
	jmp isr_common_stub

; Reserved Exception
isr23:                  ; ERROR CODE: NO
	cli
	push byte 0
	push byte 23 
	jmp isr_common_stub

; Reserved Exception
isr24:                  ; ERROR CODE: NO
	cli
	push byte 0
	push byte 24 
	jmp isr_common_stub

; Reserved Exception
isr25:                  ; ERROR CODE: NO
    cli
	push byte 0
	push byte 25 
	jmp isr_common_stub

; Reserved Exception
isr26:                  ; ERROR CODE: NO
	cli
	push byte 0
	push byte 26 
	jmp isr_common_stub

; Reserved Exception
isr27:                  ; ERROR CODE: NO
	cli
	push byte 0
	push byte 27 
	jmp isr_common_stub

; Reserved Exception
isr28:                  ; ERROR CODE: NO
	cli
	push byte 0
	push byte 28 
	jmp isr_common_stub

; Reserved Exception
isr29:                  ; ERROR CODE: NO
	cli
	push byte 0
	push byte 29 
	jmp isr_common_stub

; Reserved Exception
isr30:                  ; ERROR CODE: NO
	cli
	push byte 0
	push byte 30 
	jmp isr_common_stub

; Reserved Exception
isr31:                  ; ERROR CODE: NO
	cli
	push byte 0
	push byte 31 
	jmp isr_common_stub


; We call a C function here
extern fault_handler

; This is the common ISR stub. It saves the processor state, sets up for kernel mode segments, 
;calls the C-level fault handler, and finnally restores the stack frame
isr_common_stub:
    pusha
    push ds
    push es
    push fs
    push gs
    mov ax, 0x10       ; Load the Kernel Data Segment
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov eax, esp            ; Push us the stack
    push eax
    mov eax, fault_handler
    call eax                ; A special call, preserves the eip register
    pop eax
    pop gs
    pop fs
    pop es
    pop ds
    popa
    add esp, 8              ; Cleans up the pushed error code and pushed  ISR number
    iret                    ; pops 5 things at once: CS, EIP, EFLAGS, SS, and ESP