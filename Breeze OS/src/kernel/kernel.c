// #include <BreezeOS/kernel/kernel.h>
#include <BreezeOS/kernel/util.h>
#include <BreezeOS/drivers/ScreenIO/screen.h>
#include <BreezeOS/drivers/PortIO/port.h>
#include <BreezeOS/crypto/rand.h>
#include <BreezeOS/crypto/ceaser.h>
#include <BreezeOS/drivers/ScreenIO/vga.h>
#include <BreezeOS/cpu/gdt/gdt.h>
#include <BreezeOS/cpu/CPUID/cpuid.h>
#include <BreezeOS/power/VM/shutdown.h>
#include <BreezeOS/cpu/idt/export_idt.h>
#include <BreezeOS/cpu/idt/isr.h>
#include <BreezeOS/cpu/idt/irq.h>
#include <BreezeOS/drivers/Input/keyboard.h>
#include <BreezeOS/sys/time/clock.h>

void main() {
    disable_cursor();

    #ifdef VERBOSE
    int color = vga_init(VGA_WHITE, VGA_BLACK);
    #else
    int color = vga_init(VGA_WHITE, VGA_LIGHT_BLUE);
    #endif
    
    welcome_msg();
    sleep(200);
    
    detect_cpu();
    gdt_load_wrapper();
    
    installIDT();

    install_CPU_ISR();
//     installIRQS();
//     
//     installKB();
    
    asm volatile("int $1");
    
//     timer_install();
    
//     kprint("System has suffered critical damage", TRUE, FALSE, PANIC); //TODO: Make sure _x is NOT incremented if there is a kernel panic screen. _x MUST be equal to 0. Also, check if you can set the font to white while maintaining the blue borders - just make a new static kernel panic print function and call it in kprint
    
    

    //TODO:
//     Create a file called ascii.c or ascii.h and specify all the extended ascii chars, like a struct extended_ascii_chars { char sqrt[3] = "\xFB" } etc..
    
//     Division by 0 example
//     __asm__ __volatile__("push %eax");
//     __asm__ __volatile__("mov $0, %eax");
//     __asm__ __volatile__("div %eax");
//     __asm__ __volatile__("pop %eax");
}
