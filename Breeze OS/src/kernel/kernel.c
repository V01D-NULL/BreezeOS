// #include <kernel/kernel.h>
#include <kernel/util.h>
#include <drivers/ScreenIO/screen.h>
#include <drivers/PortIO/port.h>
#include <crypto/rand.h>
#include <crypto/ceaser.h>
#include <drivers/ScreenIO/vga.h>
#include <cpu/gdt/gdt.h>
#include <cpu/CPUID/cpuid.h>
#include <power/VM/shutdown.h>
#include <cpu/idt/idt.h>
// #include <drivers/Input/keyboard.h>
// #include <sys/time/clock.h>

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
    
    idt_init();
    
//    asm("int $1");
    
//     kprint("System has suffered critical damage", TRUE, FALSE, PANIC); //TODO: Make sure _x is NOT incremented if there is a kernel panic screen. _x MUST be equal to 0. Also, check if you can set the font to white while maintaining the blue borders - just make a new static kernel panic print function and call it in kprint
    
    

    //TODO:
//     Create a file called ascii.c or ascii.h and specify all the extended ascii chars, like a struct extended_ascii_chars { char sqrt[3] = "\xFB" } etc..

}
