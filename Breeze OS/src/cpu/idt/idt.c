#include <cpu/idt/idt.h>
#include <drivers/ScreenIO/screen.h>

extern void idt_flush();

idt_t idt[IDT_MAX];
idt_ptr_t idt_ptr;

void idt_init()
{
    kprint("Setting IDT pointer", TRUE, FALSE, LOG);
    //Set IDT pointer
    idt_ptr.limit = (sizeof(idt_t) * 256)-1;
    idt_ptr.base = (_uint32)&idt;
    kprint("Set IDT pointer", TRUE, TRUE, LOG);
    
    //Clear out IDT
    memset(&idt, 256 * sizeof(idt_t), 0);
    
    //Load the IDT
    kprint("Loading the IDT via lidt", TRUE, FALSE, LOG);
    idt_flush();
    kprint("Loaded the IDT via lidt", TRUE, TRUE, LOG);
}

void idt_gate(_uint32 offset, _uint16 cs, _uint8 flags, idt_t *idt_desc)
{
    idt_desc->low_offset = (offset & 0xFFFF);
    idt_desc->high_offset = (offset >> 16) & 0xFFFF;
    idt_desc->cs = cs;
    idt_desc->flags = flags;
    idt_desc->zero = 0;
}
