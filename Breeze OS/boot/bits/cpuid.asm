; Check if CPUID is supported

is_CPUID_supported:
    pushfd
    pop eax

    mov ecx, eax
    xor eax, 1 << 21

    push eax
    popfd

    pushfd
    pop eax

    push ecx
    popfd
    
    xor eax, ecx
    jz noCPUID_support
    ret

is_long_mode_supported:
    mov eax, 0x80000001
    cpuid
    test edx, 1 << 29
    jz noLongMode_support
    ret

noCPUID_support:
    mov [0xb8000], byte "C"
    mov [0xb8001], byte 0x0F
    
    mov [0xb8002], byte "P"
    mov [0xb8003], byte 0x0F
    
    mov [0xb8004], byte "U"
    mov [0xb8005], byte 0x0F
    
    mov [0xb8006], byte "I"
    mov [0xb8007], byte 0x0F
    
    mov [0xb8008], byte "D"
    mov [0xb8009], byte 0x0F
    
    mov [0xb800A], byte ":"
    mov [0xb800B], byte 0x0F
    
    mov [0xb800C], byte " "
    mov [0xb800D], byte 0x0F

    mov [0xb800E], byte "X"
    mov [0xb800F], byte 0x04

    hlt

noLongMode_support:
    mov [0xb8000], byte "L"
    mov [0xb8001], byte 0x0F

    mov [0xb8002], byte "o"
    mov [0xb8003], byte 0x0F
    
    mov [0xb8004], byte "n"
    mov [0xb8005], byte 0x0F

    mov [0xb8006], byte "g"
    mov [0xb8007], byte 0x0F

    mov [0xb8008], byte " "
    mov [0xb8009], byte 0x0F

    mov [0xb800A], byte "m"
    mov [0xb800B], byte 0x0F

    mov [0xb800C], byte "o"
    mov [0xb800D], byte 0x0F

    mov [0xb800E], byte "d"
    mov [0xb800F], byte 0x0F

    mov [0xb8010], byte "e"
    mov [0xb8011], byte 0x0F

    mov [0xb8012], byte ":"
    mov [0xb8013], byte 0x0F

    mov [0xb8014], byte " "
    mov [0xb8015], byte 0x0F

    mov [0xb8016], byte "X"
    mov [0xb8017], byte 0x04

    hlt
