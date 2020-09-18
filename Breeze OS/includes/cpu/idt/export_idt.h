#ifndef _EXP_IDT_H
#define _EXP_IDT_H

#include "../types.h"

void installIDT();
void set_idt_gate(_uint8 num, _ulong64 base, _uint16 selector, _uint8 flags);

#endif
