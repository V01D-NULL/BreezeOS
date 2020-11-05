PRG_SPACE equ 0x7e00 ; Program space

expand_memory:
    mov bx, PRG_SPACE
    mov ah, 0x02
    mov al, 4   ; 4 Sectors
    mov ch, 0   ; Track/cylinder number
    mov cl, 2   ; Sector number
    mov dh, 0   ; Head number
    mov dl, [BOOT_DRIVE]
    int 0x13
    jc disk_read_error
    mov si, read_success
    call printf
    ret
    
disk_read_error:
    mov si, read_error
    call printf
    jmp $
    
BOOT_DRIVE:
    db 0
    
read_error: db "(BOOT) [FATAL] Could not read from disk!", 0x0a, 0x0d, 0
read_success: db "(BOOT) [OK] Disk read", 0x0a, 0x0d, 0
