#include <BreezeOS/cpu/idt/irq.h>
#include <BreezeOS/drivers/ScreenIO/screen.h>
#include <BreezeOS/drivers/PortIO/port.h>
#include <BreezeOS/text/scancodes/EN-US/scancodes.h>
#include <BreezeOS/drivers/Input/keyboard.h>
#include <BreezeOS/cpu/idt/export_idt.h>

//Maybe the -> in set_idt_gate is causing IRQ not to fire.

void keyboard_callback(struct regs* r)
{
    while (1) {
        unsigned char scancode;
        
        scancode = inb(DATA_REG);
        
        if (scancode & 0x80)
        {
            
        }
        else
        {
            kprint("a", TRUE, FALSE, LOG);
        }
    }
}

void installKB() {
    kprint("Installing keyboard...", TRUE, FALSE, LOG);
    install_irq_handler(1, keyboard_callback);
//     outb(0x21, 0xFD);
    kprint("Installed keyboard", TRUE, TRUE, LOG);
}
