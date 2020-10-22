; Migrating from grub to a custom bootloader + jumping to 64 bits/long mode
[org 0x7c00]

; Save bootdrive
mov [BOOT_DRIVE], dl

; Setup stack
mov bp, 0x7c00
mov sp, bp

; Clear screen
call cls

mov si, nl
call printf

mov si, bootloader_version
call printf

; Read sectors
call expand_memory

; Access extended memory
jmp PRG_SPACE

; Something went wrong, bootloader is stuck at 512 bytes.
; Add a better error handler in the future
mov si, jump_failure
call printf
jmp $

%include "boot/screen/mode.asm"
%include "boot/screen/print.asm"
%include "boot/disk/disk.asm"

bootloader_version: db "Kate bootloader V.0.0.1", 0x0A, 0x0D, 0
jump_failure: db "(BOOT) [FATAL] Could not access more memory! (Stuck at 512 bytes)", 0x0A, 0x0D
nl: db 0x0A, 0x0D, 0

times 510-($-$$) db 0
dw 0xaa55
