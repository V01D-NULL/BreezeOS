#ifndef _GDT_H
#define _GDT_H

#include "../../drivers/ScreenIO/screen.h"

// What's a descriptor?
// In real mode, there is little to know about the segments. Each is 64K bytes in size, and you can do with the segment what you wish: store data in it, put your stack there, or execute code stored in the segment. The base address of the segment is simply 16 times the value in one of the segment registers.

// In protected mode, besides the segment base address, we also need the segment size (limit) and some flags indicating what the segment is used for. This information goes into an 8-byte data structure called a descriptor: 


//So a global descriptor table tells the OS and the cpu which parts of memory it can access, thus enabling the OS to create different DPL's.

//The location of the gdt.c and gdt.h files are initialized after loading the corresponding descriptor table. (In this case the lgdt register)

//This gdt file manages all the memory flow in ring0. Access to this gdt must be denied (if caller is not supposed to access this gdt), and protected at all costs. (Wow, that sounds dramatic - That's because it is ;) )

// In simple terms, the gdt is used by a segmentation mechanism. The table in the gdt holds a descriptor entry that specify the location, size, and privilege attribute of a segment.

//32 bit mode software must create a gdt. The gdt contains code-segment, and data-segment (user segments) descriptor entries.

extern void __ASM_load_gdt();
#define KERNEL_CS 0x08
// extern const int KERNEL_CS; //0x08
#define KERNEL_DS 0x10
void gdt_load_wrapper(); // The gdt_load_wrapper function has some debugging text.

#endif
