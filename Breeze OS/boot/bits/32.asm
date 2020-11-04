; GDT
[bits 16]
gdt_start:

; Mandatory null descriptor to describe the base of the gdt, and invalid operations
gdt_null_descriptor:
    dd 0
    dd 0

gdt_code_entry:
    dw 0xFFFF     ; limit
    dw 0          ; base
    db 0          ; base
    db 10011010b  ; present, privilege, descriptor type, type (code, conforming, readable, accessed)
    db 11001111b  ; granularity, 32-bit default, 64-bit code segement, AVL, limit
    db 0          ; base
    

; Same as gdt_code_entry, aside from the type flags
gdt_data_entry:
    dw 0xFFFF     ; limit
    dw 0          ; base
    db 0          ; base
    db 10010010b  ; present, privilege, descriptor type, type (code, expand down, writeable, accessible)
    db 11001111b  ; granularity, 32-bit default, 64-bit code segement, AVL, limit
    db 0          ; base

; Label to mark the end of the GDT to calculate the size of the GDT table
gdt_end:
    
; Instead of giving the CPU the address of the GDT itself, the OS gives the CPU the GDT descriptor, which holds the GDT size (16 bits), and the GDT address (32 bits).
gdt_descriptor:
    dw gdt_end - gdt_start - 1 ; Size of gdt (16 bits total). Always minus 1 of the true size
    
    dd gdt_start               ; Address of GDT. (32 bits total)

    
load_gdt:
    cli
    xor ax, ax
    mov ds, ax
    
    mov si, doing_a20
    call printf
    
    call enable_a20
    mov si, ok_a20
    call printf
    
    lgdt [gdt_descriptor]
    
    mov eax, cr0
    or eax, 1
    mov cr0, eax
    
    jmp CODE_SEGMENT:flush_pipe
    
;[bits 32]
flush_pipe:
    mov ax, DATA_SEGMENT
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    
    jmp protected_mode_main ; main.asm

    
CODE_SEGMENT equ gdt_code_entry - gdt_null_descriptor ; 0x08
DATA_SEGMENT equ gdt_data_entry - gdt_null_descriptor ; 0x10

doing_a20: db "(BOOT) [Task] Enabling the a20 line",  0x0A, 0x0D, 0
ok_a20: db "(BOOT) [OK] Enabled a20 line", 0x0A, 0x0D, 0
