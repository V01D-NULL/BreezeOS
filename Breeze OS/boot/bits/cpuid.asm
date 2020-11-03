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

    xor eax, ecx
    jz noCPUID_support

    mov bl, GREEN
    mov esi, cpuid_success
    call printf32
    
    mov bl, WHITE
    mov esi, division_symbol
    call printf32

    mov eax, 0x80000000
    cpuid
    cmp eax, 0x80000001
    jb noLongMode_support

    mov bl, GREEN
    mov esi, longmode_supported
    call printf32

    mov bl, WHITE
    mov esi, division_symbol
    call printf32

    ret

noCPUID_support:
    mov bl, RED
    mov esi, cpuid_not_supported_message
    call printf32
    hlt

noLongMode_support:
    mov bl, RED
    mov esi, longmode_not_supported
    call printf32
    hlt

cpuid_not_supported_message: db "(ERROR) [FATAL] CPUID is  not supported on this machine- cannot jump to 64 bit mode", 0
cpuid_success: db " [OK] CPUID is supported", 0

longmode_not_supported: db "(ERROR) [FATAL] Long mode is not supported.", 0
longmode_supported: db " [OK] Long mode is supported", 0