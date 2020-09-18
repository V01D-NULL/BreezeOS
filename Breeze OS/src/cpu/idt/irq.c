/* Heavily inspired by: http://www.osdever.net/bkerndev/Docs/irqs.htm */
#include <BreezeOS/cpu/idt/irq.h>
#include <BreezeOS/drivers/ScreenIO/screen.h>

void* irq_routines[16] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0  
};

void install_irq_handler(int irq, void (*handler)(struct regs* r))
{
    irq_routines[irq] = handler;
}

void uninstall_irq_handler(int irq)
{
    irq_routines[irq] = 0;
}

void remapIRQ(void)
{
    //ICW1
    outb(0x20, 0x11);
    outb(0xA0, 0x11);
    
    //ICW2 - Remap PIC offset
    outb(0x21, 0x20);
    outb(0xA1, 0x28);
    
    //ICW3 - Cascading
    outb(0x21, 0x0);
    outb(0xA1, 0x0);
    
    //ICW4 - Enviornment info
    outb(0x21, 0x01);
    outb(0xA1, 0x01);
    
    //Mask interrupts
    outb(0x21, 0xFF);
    outb(0xA1, 0xFF);
}

void installIRQS()
{
    kprint("Installing IRQ's...", TRUE, FALSE, LOG);
    kprint("Remapping PIC for IRQ's...", TRUE, FALSE, LOG);
    remapIRQ();
    kprint("Remapped PIC", TRUE, TRUE, LOG);
    kprint("Setting idt gates 32 -> 47...", TRUE, FALSE, LOG);
    set_idt_gate(32, (unsigned)irq0, 0x08, 0x8E);
    set_idt_gate(33, (unsigned)irq1, 0x08, 0x8E);
    set_idt_gate(34, (unsigned)irq2, 0x08, 0x8E);
    set_idt_gate(35, (unsigned)irq3, 0x08, 0x8E);
    set_idt_gate(36, (unsigned)irq4, 0x08, 0x8E);
    set_idt_gate(37, (unsigned)irq5, 0x08, 0x8E);
    set_idt_gate(38, (unsigned)irq6, 0x08, 0x8E);
    set_idt_gate(39, (unsigned)irq7, 0x08, 0x8E);
    set_idt_gate(40, (unsigned)irq8, 0x08, 0x8E);
    set_idt_gate(41, (unsigned)irq9, 0x08, 0x8E);
    set_idt_gate(42, (unsigned)irq10, 0x08, 0x8E);
    set_idt_gate(43, (unsigned)irq11, 0x08, 0x8E);
    set_idt_gate(44, (unsigned)irq12, 0x08, 0x8E);
    set_idt_gate(45, (unsigned)irq13, 0x08, 0x8E);
    set_idt_gate(46, (unsigned)irq14, 0x08, 0x8E);
    set_idt_gate(47, (unsigned)irq15, 0x08, 0x8E);
    kprint("Set idt gates", TRUE, TRUE, LOG);
    kprint("Installed IRQ's", TRUE, TRUE, LOG);
}

void irq_handler(struct regs* r)
{
    /* Blank function pointer */
    void (*handler)(struct regs* r);
    
    handler = irq_routines[r->int_num - 32];
    if (handler)
    {
        handler(r);
    }

    /* If the IDT entry that was invoked was greater than 40
    *  (meaning IRQ8 - 15), then we need to send an EOI to
    *  the slave controller */
    if (r->int_num >= 40)
    {
        outb(0xA0, 0x20);
    }

    /* In either case, we need to send an EOI to the master
    *  interrupt controller too */
    outb(0x20, 0x20);
}
