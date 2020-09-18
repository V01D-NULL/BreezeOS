;
;   Interrupt service routine (ISR) file by V01D
;

; C handler for CPU specific interrupts
extern fault_handler

; CPU specific interrupts
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

; C handler for PIC specific interrupts
extern irq_handler

; PIC specific interrupts
global irq0
global irq1
global irq2
global irq3
global irq4
global irq5
global irq6
global irq7
global irq8
global irq9
global irq10
global irq11
global irq12
global irq13
global irq14
global irq15

irq_common_stub:
    pusha
    push ds
    push es
    push fs
    push gs
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov eax, esp
    push eax
    mov eax, irq_handler
    call eax
    pop eax
    pop gs
    pop fs
    pop es
    pop ds
    popa
    add esp, 8
    iret
    
common_isr_stub:
    pusha
    push ds
    push es
    push fs
    push gs
    mov ax, 0x10 ; Kernel data segment
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov eax, esp
    push eax
    mov eax, fault_handler
    call eax
    pop eax
    pop gs
    pop fs
    pop es
    pop ds
    popa
    add esp, 8     ; Cleans up the pushed error code and pushed ISR number
    iret
    
; All isr's up to isr 7 have no error code

isr0: ; Division By Zero Exception
    cli
    push byte 0 ; Dummy error code
    push byte 0 ; ISR num
    jmp common_isr_stub

isr1: ; Debug Exception
    cli
    push byte 0
    push byte 1
    jmp common_isr_stub

isr2: ; Non Maskable Interrupt Exception
    cli
    push byte 0
    push byte 2
    jmp common_isr_stub
    
isr3: ; Breakpoint Exception
    cli
    push byte 0
    push byte 3
    jmp common_isr_stub
    
isr4: ; Into Detected Overflow Exception
    cli
    push byte 0
    push byte 4
    jmp common_isr_stub
    
isr5: ; Out of Bounds Exception
    cli
    push byte 0
    push byte 5
    jmp common_isr_stub
    
isr6: ; Invalid Opcode Exception
    cli
    push byte 0
    push byte 6
    jmp common_isr_stub
    
isr7: ; No Coprocessor Exception
    cli
    push byte 0
    push byte 7
    jmp common_isr_stub
    
isr8: ; Double Fault Exception
    cli
    push byte 0
    ; Has error code
    jmp common_isr_stub

isr9: ; Coprocessor Segment Overrun Exception
    cli
    push byte 0
    push byte 9
    jmp common_isr_stub
    
isr10: ; Bad TSS exception
    cli
    push byte 10
    jmp common_isr_stub
    
isr11: ; Segment Not Present Exception
    cli
    push byte 11
    jmp common_isr_stub
    
isr12: ; Stack Fault Exception
    cli
    push byte 12
    jmp common_isr_stub
    
isr13: ; General Protection Fault Exception
    cli
    push byte 13
    jmp common_isr_stub

isr14: ; Page Fault Exception
    cli
    push byte 14
    jmp common_isr_stub
    
isr15: ; Unknown Interrupt Exception
    cli
    push byte 0
    push byte 15
    call common_isr_stub
    
isr16: ; Coprocessor Fault Exception
    cli
    push byte 0
    push byte 16
    call common_isr_stub
    
isr17: ; Alignment Check Exception (486+)
    cli
    push byte 0
    push byte 17
    call common_isr_stub
    
isr18: ; Machine Check Exception (Pentium/586+)
    cli
    push byte 0
    push byte 18
    call common_isr_stub
    
; 19 -> 31 are reserved exceptions
isr19:
    cli
    push byte 0
    push byte 19
    call common_isr_stub
    
isr20:
    cli
    push byte 0
    push byte 20
    call common_isr_stub
    
isr21:
    cli
    push byte 0
    push byte 21
    call common_isr_stub
    
isr22:
    cli
    push byte 0
    push byte 22
    call common_isr_stub
    
isr23:
    cli
    push byte 0
    push byte 23
    call common_isr_stub

isr24:
    cli
    push byte 0
    push byte 24
    call common_isr_stub
    
isr25:
    cli
    push byte 0
    push byte 25
    call common_isr_stub
    
isr26:
    cli
    push byte 0
    push byte 26
    call common_isr_stub
    
isr27:
    cli
    push byte 0
    push byte 27
    call common_isr_stub
    
isr28:
    cli
    push byte 0
    push byte 28
    call common_isr_stub
    
isr29:
    cli
    push byte 0
    push byte 29
    call common_isr_stub
    
isr30:
    cli
    push byte 0
    push byte 30
    call common_isr_stub
    
isr31:
    cli
    push byte 0
    push byte 31
    call common_isr_stub
    

irq0:
    cli
    push byte 0
    push byte 32
    call irq_common_stub
    
irq1:
    cli
    push byte 0
    push byte 33
    call irq_common_stub    
    
irq2:
    cli
    push byte 0
    push byte 34
    call irq_common_stub
    
irq3:
    cli
    push byte 0
    push byte 35
    call irq_common_stub    
    
irq4:
    cli
    push byte 0
    push byte 36
    call irq_common_stub
    
irq5:
    cli
    push byte 0
    push byte 37
    call irq_common_stub    
    
irq6:
    cli
    push byte 0
    push byte 38
    call irq_common_stub    
    
irq7:
    cli
    push byte 0
    push byte 39
    call irq_common_stub    
    
irq8:
    cli
    push byte 0
    push byte 40
    call irq_common_stub
    
irq9:
    cli
    push byte 0
    push byte 41
    call irq_common_stub
    
irq10:
    cli
    push byte 0
    push byte 42
    call irq_common_stub
    
irq11:
    cli
    push byte 0
    push byte 43
    call irq_common_stub
    
irq12:
    cli
    push byte 0
    push byte 44
    call irq_common_stub
    
irq13:
    cli
    push byte 0
    push byte 45
    call irq_common_stub
    
irq14:
    cli
    push byte 0
    push byte 46
    call irq_common_stub
    
irq15:
    cli
    push byte 0
    push byte 47
    call irq_common_stub
    
