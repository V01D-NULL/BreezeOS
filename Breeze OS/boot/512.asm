; Migrating from grub to a custom bootloader + jumping to 64 bits/long mode
[org 0x7c00]

; Save bootdrive
mov [BOOT_DRIVE], dl

; Setup stack
mov bp, 0x7c00
mov sp, bp

call cls

mov si, nl
call printf

mov si, bootloader_version
call printf

; Read sectors
call expand_memory

; Access extended memory
jmp PRG_SPACE

%include "boot/screen/mode.asm"
%include "boot/screen/print.asm"
%include "boot/disk/disk.asm"

bootloader_version: db "Kate bootloader V.0.0.1", 0x0A, 0x0D, 0
nl: db 0x0A, 0x0D, 0

times 510-($-$$) db 0
dw 0xaa55
