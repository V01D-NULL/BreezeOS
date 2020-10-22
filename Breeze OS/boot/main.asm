; TODO: CLEAN UP THIS FILE, GIVE IT A REAL NAME, RENAME BOOT.ASM (MBR OR SOMETHING (MAYBE 512)) AND PUT ALL FURTHER CODE IN HERE 
[org 0x7e00]

mov si, jump_success
call printf

call load_gdt

jmp $

%include "boot/screen/print.asm"
%include "boot/bits/32.asm"

jump_success: db "(BOOT) [OK] Successfully expanded memory over 512 bytes", 0x0A, 0x0D, 0

times 2048-($-$$) db 0
