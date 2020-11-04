[bits 16]
mov si, jump_success
call printf

jmp load_gdt

; This should NEVER run, but if for some reason it does, notify user and loop
mov si, protected_mode_fail
call printf

;jmp $

%include "boot/screen/print.asm"

[bits 32]
%include "boot/bits/cpuid.asm"
%include "boot/memory/paging.asm"
%include "boot/bits/32.asm"
%include "boot/bits/64.asm"
%include "boot/bits/a20.asm"

protected_mode_main:
    mov [0xb8000], byte 'H'
	mov [0xb8002], byte 'e'
	mov [0xb8004], byte 'l'
	mov [0xb8006], byte 'l'
	mov [0xb8008], byte 'o'
	mov [0xb800a], byte ' '
	mov [0xb800c], byte 'W'
	mov [0xb800e], byte 'o'
	mov [0xb8010], byte 'r'
	mov [0xb8012], byte 'l'
	mov [0xb8014], byte 'd'

    call check_a20
    call is_CPUID_supported
    call setupIdentityPaging
    call load_64_bit_gdt
    
    jmp CODE_SEGMENT:long_mode_main
    jmp $

[bits 64]
[extern _start]
long_mode_main:
    
    
    call _start ; Reboots over and over. If this line is commented out everything works fine.
    jmp $

jump_success: db "(BOOT) [OK] Successfully expanded memory over 512 bytes", 0x0A, 0x0D, 0
protected_mode_fail: db "(BOOT) [FATAL] Could not enter protected mode (32 bits)", 0x0A, 0x0D, 0

times 2048-($-$$) db 0
