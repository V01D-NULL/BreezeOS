; TODO: CLEAN UP THIS FILE, GIVE IT A REAL NAME, RENAME BOOT.ASM (MBR OR SOMETHING (MAYBE 512)) AND PUT ALL FURTHER CODE IN HERE 
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
%include "boot/bits/a20.asm"
protected_mode_main:
    ; Check a20 & enable it if it isn't enabled
    call check_a20
    
    jmp $

jump_success: db "(BOOT) [OK] Successfully expanded memory over 512 bytes", 0x0A, 0x0D, 0
protected_mode_fail: db "(BOOT) [FATAL] Could not enter protected mode (32 bits)", 0x0A, 0x0D, 0
times 2048-($-$$) db 0
