; Functions to check, enable, and disable the a20 line

[bits 32]
check_a20:
    pushad
    mov edi, 0x112345
    mov esi, 0x012345
    mov [esi], esi
    mov [edi], edi
    cmpsd ; Compare addresses
    popad
    jne enable_a20
    place_holder:
    
    ret
    
[bits 32]
enable_a20:
    ; Enable a20 line
    in al, 0x92
    or al, 2
    out 0x92, al
        
    jmp place_holder
