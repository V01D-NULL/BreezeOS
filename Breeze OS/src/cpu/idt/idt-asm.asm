global idt_flush
extern idt_ptr

idt_flush:
    lidt[idt_ptr]
    ret
