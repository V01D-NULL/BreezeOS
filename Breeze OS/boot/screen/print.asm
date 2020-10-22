printf:
    pusha
    print_loop:
        mov al, [si]
        cmp al, 0
        je done_print16
        mov ah, 0x0E
        int 0x10
        add si, 1
        jmp print_loop
        
done_print16:
    popa
    ret
