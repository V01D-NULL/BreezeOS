; 32 bit mode printing routine

VIDEO_MEMORY: dd 0xb8000
BLUE equ 0x03
GREEN equ 0x0A
WHITE equ 0x0F
RED equ 0x4F
VGA_WIDTH equ 80
VGA_HEIGHT equ 25

; X & Y position (int index = y * VGA_WIDTH + x)
Y: db 0
X: db 0

[bits 32]
printf32:
    pusha
    mov edx, [VIDEO_MEMORY]
    print32_loop:
        ; Character & color
        mov al, [esi]
        mov ah, bl
        
        ; Check End of line
        cmp al, 0
        je done_print32
    
        cmp al, 13
        je nl
        dr:

        ; Print character
        mov [edx], ax
        add esi, 1
        add edx, 2
        
        ; Update memory address
        mov dword [VIDEO_MEMORY], edx

        jmp print32_loop

nl:
    inc byte [Y]
    jmp dr

done_print32:
    popa
    ret
