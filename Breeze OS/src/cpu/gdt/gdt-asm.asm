;
;   GDT by V01D. (Setting up the GDT really isn't that hard... Don't let people scare you, and alter your state of mind.)
;
;       NOTE: interrupts have already been cleared in kernel_asm.

global __ASM_load_gdt
global KERNEL_CS

KERNEL_CS:
    db 0x08
  
; Label to mark the start of the GDT to calculate the size of the GDT table
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

    
; Actually load gdt
__ASM_load_gdt:
    lgdt [gdt_descriptor]
    jmp 0x08:flush_gdt
    ret

; Setup data, stack, etc registers for the gdt.
flush_gdt:
    mov ax, 0x10
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    ret
