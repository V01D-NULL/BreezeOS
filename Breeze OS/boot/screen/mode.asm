cls:
    mov ax, 0x03
    int 0x10
    ret

video_mode:
    mov ax, 0x13
    int 0x10
    ret