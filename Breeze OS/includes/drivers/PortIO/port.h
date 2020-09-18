#ifndef _PORT_H
#define _PORT_H

#include "../../cpu/types.h"

#define PORT_DATA_READ 0x3D4
#define PORT_DATA_WRITE 0x3D5

extern void outb(_uint32 port, _uint32 data);
extern unsigned char inb(short port);

extern void outw(_uint32 port, _uint32 data);

#endif
