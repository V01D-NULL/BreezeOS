#include <cpu/idt/irq.h>
#include <drivers/ScreenIO/screen.h>
#include <drivers/PortIO/port.h>
#include <text/scancodes/EN-US/scancodes.h>
#include <drivers/Input/keyboard.h>
#include <cpu/idt/export_idt.h>

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
