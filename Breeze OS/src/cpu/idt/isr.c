#include <cpu/idt/isr.h>
#include <cpu/idt/export_idt.h>
#include <drivers/ScreenIO/screen.h>
#include <power/VM/shutdown.h>

/* Install CPU specific ISR's */
void install_CPU_ISR()
{
    /* Set / Map all CPU required ISR's to the IDT */
    // 0x08 -> kernel code segment, 0x8E = 10001110 ( 1     00     01110)
    //                                            Present  Ring  Always 01110
    kprint("Installing CPU ISR's 0 -> 31", TRUE, FALSE, LOG);
    set_idt_gate(0, (unsigned)isr0, 0x08, 0x8E);
    set_idt_gate(1, (unsigned)isr1, 0x08, 0x8E);
    set_idt_gate(2, (unsigned)isr2, 0x08, 0x8E);
    set_idt_gate(3, (unsigned)isr3, 0x08, 0x8E);
    set_idt_gate(4, (unsigned)isr4, 0x08, 0x8E);
    set_idt_gate(5, (unsigned)isr5, 0x08, 0x8E);
    set_idt_gate(6, (unsigned)isr6, 0x08, 0x8E);
    set_idt_gate(7, (unsigned)isr7, 0x08, 0x8E);
    set_idt_gate(8, (unsigned)isr8, 0x08, 0x8E);
    set_idt_gate(9, (unsigned)isr9, 0x08, 0x8E);
    set_idt_gate(10, (unsigned)isr10, 0x08, 0x8E);
    set_idt_gate(11, (unsigned)isr11, 0x08, 0x8E);
    set_idt_gate(12, (unsigned)isr12, 0x08, 0x8E);
    set_idt_gate(13, (unsigned)isr13, 0x08, 0x8E);
    set_idt_gate(14, (unsigned)isr14, 0x08, 0x8E);
    set_idt_gate(15, (unsigned)isr15, 0x08, 0x8E);
    set_idt_gate(16, (unsigned)isr16, 0x08, 0x8E);
    set_idt_gate(17, (unsigned)isr17, 0x08, 0x8E);
    set_idt_gate(18, (unsigned)isr18, 0x08, 0x8E);
    set_idt_gate(19, (unsigned)isr19, 0x08, 0x8E);
    set_idt_gate(20, (unsigned)isr20, 0x08, 0x8E);
    set_idt_gate(21, (unsigned)isr21, 0x08, 0x8E);
    set_idt_gate(22, (unsigned)isr22, 0x08, 0x8E);
    set_idt_gate(23, (unsigned)isr23, 0x08, 0x8E);
    set_idt_gate(24, (unsigned)isr24, 0x08, 0x8E);
    set_idt_gate(25, (unsigned)isr25, 0x08, 0x8E);
    set_idt_gate(26, (unsigned)isr26, 0x08, 0x8E);
    set_idt_gate(27, (unsigned)isr27, 0x08, 0x8E);
    set_idt_gate(28, (unsigned)isr28, 0x08, 0x8E);
    set_idt_gate(29, (unsigned)isr29, 0x08, 0x8E);
    set_idt_gate(30, (unsigned)isr30, 0x08, 0x8E);
    set_idt_gate(31, (unsigned)isr31, 0x08, 0x8E);
    kprint("Installed CPU ISR's 0 -> 31", TRUE, TRUE, LOG);
}

/* Error messges */
static const char* cpu_exception_messages[] = {
    "Division by zero",
    "Debug Exception",
    "Non maskable interrupt",
    "Breakpoint exception",
    "Into detected overflow",
    "Out of bounds",
    "Invalid opcode",
    "No coprocessor",
    "Double fault",
    "Coprocessor segment overrun",
    "Bad TSS",
    "Segment not present",
    "Stack fault",
    "General protection fault",
    "Page fault",
    "Unkown interrupt",
    "Coprocessor fault",
    "Alignment check",
    "Machine check",
    "reserved",
    "reserved",
    "reserved",
    "reserved",
    "reserved",
    "reserved",
    "reserved",
    "reserved",
    "reserved",
    "reserved",
    "reserved",
    "reserved",
    "reserved"
};

void fault_handler(struct regs r)
{
    if (r.int_num < 32)
    {
        kprint_op_failure("Exception has occured! Error details: ");
        kprint_int(r.int_num, TRUE, WARN);
        kprint(cpu_exception_messages[r.int_num], TRUE, FALSE, WARN);
#ifdef VM_QEMU
        kprint("Host needs to shutdown in order to prevent further damage", TRUE, FALSE, LOG);
        sleep(500);
        VM_shutdown(__QEMU__);
        for(;;);
#elif VM_BOCHS
        kprint("Host needs to shutdown in order to prevent further damage", TRUE, FALSE, LOG);
        sleep(500);
        VM_shutdown(__BOCHS__);
        for(;;);
#elif VM_VBOX
        kprint("Host needs to shutdown in order to prevent further damage", TRUE, FALSE, LOG);
        sleep(500);
        VM_shutdown(__VBOX__);
        for(;;);
#else
        kprint("Halting CPU.", TRUE, FALSE, LOG);
        kprint("CPU Halted - Please restart computer.", TRUE, TRUE, LOG); //TODO: Automatically restart computer once reboot is implemented.
        for(;;);
#endif
    }
}
