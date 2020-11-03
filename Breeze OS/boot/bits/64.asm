; Edit GDT to fit the 64 bit env.

[bits 32]
load_64_bit_gdt:
    mov [CODE_SEGMENT+6], byte 10101111b
    mov [DATA_SEGMENT+6], byte 10101111b
    ret
