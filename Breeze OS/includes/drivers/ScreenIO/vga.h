#ifndef _VGA_H
#define _VGA_H

#include "../PortIO/port.h"
#include "../../cpu/types.h"
#include "screen.h"

// void cursor_disable();
void cursor_update(_uint32 pos);
_uint32 ret_cursor_pos();
void specific_cursor_update(_uint32 x, _uint32 y);
int cursor_offset();
void disable_cursor();
void enable_cursor(_uint8 cursor_start, _uint8 cursor_end);
#endif
