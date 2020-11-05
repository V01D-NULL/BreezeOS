
jmp protected_mode

%include "boot/bits/gdt.asm"
%include "boot/screen/print.asm"

protected_mode:
    call enable_a20

    cli
    lgdt [gdt_descriptor]
    mov eax, cr0
    or eax, 1
    mov cr0, eax

    jmp CODE_SEGMENT:protected_mode_main

enable_a20:
    in al, 0x92
    or al, 2
    out 0x92, al
    ret

[bits 32]

%include "boot/bits/cpuid.asm"
%include "boot/memory/paging.asm"

protected_mode_main:
    mov ax, DATA_SEGMENT
    mov ds, ax
    mov ss, ax 
    mov es, ax
    mov fs, ax
    mov gs, ax

    call is_CPUID_supported
    call is_long_mode_supported
    call setupIdentityPaging
    call load_64_bit_gdt

    jmp CODE_SEGMENT:long_mode_main

[bits 64]
[extern _start]

long_mode_main:
    ; Does not clear the screen with a blue color
    mov edi, 0xb8000
	mov rax, 0x1f201f201f201f20
	mov ecx, 500
	rep stosq

    call _start ; Reboots over and over

    hlt

times 2048-($-$$) db 0