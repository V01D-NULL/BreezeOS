; Migrating from grub to a custom bootloader + jumping to 64 bits/long mode
[org 0x7c00]

; Setup stack
mov bp, 0x7c00
mov sp, bp

; Clear screen
call cls

mov si, bootloader_version
call printf

; Read sectors


; Jump to 32 bits

jmp $

%include "boot/screen/mode.asm"
%include "boot/screen/print.asm"
%include "boot/disk/disk.asm"

bootloader_version: db "bootloader with no name V.0.0.1", 0x0A, 0x0D, 0

times 510-($-$$) db 0
dw 0xaa55
