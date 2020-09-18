#include <cpu/types.h>
#include <drivers/ScreenIO/screen.h>

#define IDT_MAX 256

struct idt_entry {
    _uint16 base_low;
    _uint16 kernel_code_segment_selector; //0x08
    _uint8  always_zero;
    _uint8  flags;
    _uint16 base_high;
}__attribute__((packed));

struct idt_ptr {
    _uint16 limit; //high offset
    _uint32 base;  //low offset
}__attribute__((packed));

struct idt_entry idt[IDT_MAX];
struct idt_ptr p_idt;

extern void load_idt(); //int.asm

void set_idt_gate(_uint8 num, _ulong64 base, _uint16 selector, _uint8 flags)
{
    /* We'll leave you to try and code this function: take the
    *  argument 'base' and split it up into a high and low 16-bits,
    *  storing them in idt[num].base_hi and base_lo. The rest of the
    *  fields that you must set in idt[num] are fairly self-
    *  explanatory when it comes to setup */
    idt[num].base_low = (base & 0xFFFF);
    idt[num].base_high = (base >> 16) & 0xFFFF;
    idt[num].kernel_code_segment_selector = selector;
    idt[num].always_zero = 0;
    idt[num].flags = flags;
}

void kbIDT() {
    int keyboard_addr = 10;//This is a function made in assembly (replace 10 with assembly label)
    set_idt_gate(0x21, keyboard_addr, 0x08, 0x8E);
}

// How to render extended ascii chars:
// crack open a list of the extended ibm character set and just find the hex of what you need to print
// then just put said hex in the string you want to print
//for example: "\x45" to print 45 hex

// GUI Basics:
// you'd usually switch to a graphics mode using vesa
// and then you get a framebuffer and just draw to it
//cough use limine

// no i mean print the char to screen by its hex value
// instead of ascii
// like print("some string \xab blah");
// where "ab" is the hex of the char you wanna print

void installIDT()
{
    kprint("IDT_LOG: Installing IDT...", TRUE, FALSE, LOG);
    
    //set idt limit (similar to setup in gdt (gdt_descriptor = dw gdt_end - gdt_start - 1)
    kprint("TASK: Setting IDT limit..", TRUE, FALSE, LOG);
    p_idt.limit = (sizeof(struct idt_entry) * IDT_MAX) - 1;
    kprint("TASK: Set the limit of the IDT", TRUE, TRUE, LOG);
    
    //set idt base
    kprint("TASK: Setting IDT base..", TRUE, FALSE, LOG);
    p_idt.base = (_uint32)&idt;
    kprint("TASK: Set the base of the IDT", TRUE, TRUE, LOG);
    
    //Set all 256 entries of the IDT to zero for now
    kprint("TASK: Setting IDT limit to 0 via memset..", TRUE, FALSE, LOG);
    memset(&idt, 0, sizeof(struct idt_entry) * IDT_MAX);
    kprint("TASK: Set IDT limit to 0", TRUE, TRUE, LOG);
    
    // Add new ISR's to IDT using set_idt_gate 
//     kbIDT();
    
    //load idt via assembly label
    kprint("TASK: Loading IDT into memory via lidt..", TRUE, FALSE, LOG);
   
    __asm__ __volatile__("lidt (%0)" : : "r" (&p_idt));
    
    kprint("TASK: Loaded IDT into memory", TRUE, TRUE, LOG);
    
    kprint("IDT_LOG: Installed IDT", TRUE, TRUE, LOG);
}
