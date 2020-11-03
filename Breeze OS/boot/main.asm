[org 0x7e00]

mov si, jump_success
call printf

call load_gdt

; This should NEVER run, but if for some reason it does, notify user and loop
mov si, protected_mode_fail
call printf

jmp $

%include "boot/screen/print.asm"
%include "boot/bits/32.asm"

[bits 32]
%include "boot/bits/cpuid.asm"
%include "boot/memory/paging.asm"
%include "boot/bits/64.asm"
%include "boot/bits/a20.asm"
%include "boot/screen/print32.asm"

protected_mode_main:    
;    mov bl, WHITE
;    mov esi, protected_mode_ok
;    call printf32

    ; Check a20 & enable it if it isn't enabled
    call check_a20

    call is_CPUID_supported
    call setupIdentityPaging
    call load_64_bit_gdt

    jmp CODE_SEGMENT:long_mode_main

[bits 64]
long_mode_main:
    
    jmp $

jump_success: db "(BOOT) [OK] Successfully expanded memory over 512 bytes", 0x0A, 0x0D, 0
protected_mode_fail: db "(BOOT) [FATAL] Could not enter protected mode (32 bits)", 0x0A, 0x0D, 0
protected_mode_ok: db "(BOOT) Landed in 32 bit protected mode", 0
test: db " ", 0

times 2048-($-$$) db 0
