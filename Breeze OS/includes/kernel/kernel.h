#ifndef _KERNEL_H
#define _KERNEL_H

//Includes
#include "util.h"
#include "../drivers/ScreenIO/screen.h"
#include "../drivers/PortIO/port.h"
#include "../crypto/rand.h"
#include "../crypto/ceaser.h"
#include "../drivers/ScreenIO/vga.h"
#include "../cpu/gdt/gdt.h"
#include "../cpu/CPUID/cpuid.h"
#include "../power/VM/shutdown.h"
#include "../cpu/idt/export_idt.h"
#include "../cpu/idt/isr.h"
#include "../cpu/idt/irq.h"
#include "../sys/time/clock.h"

void kBootMsg(char* msg, int color);

#endif
