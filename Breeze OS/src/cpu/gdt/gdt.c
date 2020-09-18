#include <cpu/gdt/gdt.h>

void gdt_load_wrapper()
{
    kprint("LOADING GDT...", TRUE, FALSE, LOG);
    __ASM_load_gdt();
    kprint("LOADED GDT", TRUE, TRUE, LOG);
#ifdef DEBUG
    kprintDBG("Kernel Code Segment: 0x08", TRUE, 0);
    kprintDBG("Kernel Data Segment: 0x10", TRUE, 0);
#endif
}
