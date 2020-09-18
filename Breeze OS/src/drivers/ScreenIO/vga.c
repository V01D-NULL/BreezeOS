#include <BreezeOS/drivers/ScreenIO/vga.h>

// Broken. Cursor get's really big.
// void cursor_disable()
// {
//     outb(PORT_DATA_READ, 0x0A);
//     outb(PORT_DATA_WRITE, 0x20);
// }

void cursor_update(_uint32 pos)
{
//     _uint32 pos = y * 80 + x;
    
    outb(PORT_DATA_WRITE, (_uint8) (pos & 0xFF));
    outb(PORT_DATA_READ, 0x0E);
    outb(PORT_DATA_WRITE, (_uint8) ((pos >> 8) & 0xFF));
}

void specific_cursor_update(_uint32 x, _uint32 y)
{
    _uint16 pos = y * VGA_WIDTH + x + 1;
    outb(0x3D4, 0x0F);
    outb(0x3D5, (_uint8) (pos & 0xFF));
    outb(0x3D4, 0x0E);
    outb(0x3D5, (_uint8) ((pos >> 8) & 0xFF));
}

_uint32 ret_cursor_pos()
{
    _uint16 pos = 0;
    outb(PORT_DATA_READ, 0x0F);
    pos |= inb(PORT_DATA_WRITE);
    outb(PORT_DATA_READ, 0x0E);
    pos |= ( (_uint16) inb(PORT_DATA_WRITE) ) << 8;
    return pos;
}

int cursor_offset()
{
    outb(PORT_DATA_READ, 14);
    int offset = inb(PORT_DATA_WRITE) << 8;
    outb(PORT_DATA_READ, 15);
    offset += inb(PORT_DATA_WRITE);
    return offset * 2;
}

void disable_cursor()
{
	outb(0x3D4, 0x0A);
	outb(0x3D5, 0x20);
}

void enable_cursor(_uint8 cursor_start, _uint8 cursor_end)
{
	outb(0x3D4, 0x0A);
	outb(0x3D5, (inb(0x3D5) & 0xC0) | cursor_start);
 
	outb(0x3D4, 0x0B);
	outb(0x3D5, (inb(0x3D5) & 0xE0) | cursor_end);
}
