[org 0x7e00]

mov si, jump_success
call printf

call load_gdt

; This should NEVER run, but if for some reason it does, notify user and loop
mov si, protected_mode_fail
call printf


jmp $

%include "boot/screen/print.asm"
%include "boot/screen/print32.asm"
%include "boot/bits/32.asm"
%include "boot/bits/a20.asm"
%include "boot/bits/cpuid.asm"

protected_mode_main:    
    ; Check a20 & enable it if it isn't enabled
    call check_a20

    mov bl, WHITE
    mov esi, protected_mode_ok
    call printf32

    mov bl, WHITE
    mov esi, division_symbol
    call printf32

    call is_CPUID_supported

    jmp $

jump_success: db "(BOOT) [OK] Successfully expanded memory over 512 bytes", 0x0A, 0x0D, 0
protected_mode_fail: db "(BOOT) [FATAL] Could not enter protected mode (32 bits)", 0x0A, 0x0D, 0
protected_mode_ok: db "(BOOT) Landed in 32 bit protected mode", 0
division_symbol: db " |", 0


times 2048-($-$$) db 0
