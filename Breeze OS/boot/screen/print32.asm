; 32 bit mode printing routine

VIDEO_MEMORY equ 0xb8000
COLOR equ 0x0F

[bits 32]
printf32:
    pusha
    mov edx, VIDEO_MEMORY
    print32_loop:
        mov al, [esi]
        mov ah, COLOR
        
        cmp al, 0
        je done_print32
        
        mov [edx], ax
        add esi, 1
        add edx, 2
        
        jmp print32_loop
        
done_print32:
    popa
    ret
