#ifndef _IDT_H
#define _IDT_H

#include "../types.h"

#define IDT_MAX 256

typedef struct {
    
    _uint16 low_offset;
    _uint16 cs;
    _uint8  zero;
    _uint8  flags;
    _uint16 high_offset;
    
}__attribute__((packed)) idt_t;


typedef struct {
    
    _uint16 limit;
    _uint32 base;
    
}__attribute__((packed)) idt_ptr_t;

void idt_init();

#endif
