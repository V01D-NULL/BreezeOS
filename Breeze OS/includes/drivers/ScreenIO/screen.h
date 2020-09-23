#ifndef _SCREEN_H
#define _SCREEN_H

#include "../../cpu/types.h"
#include "../../kernel/util.h"
#include "vga.h"
#include "../../libc/math.h"

//Macro constants
#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VIDMEM 0xb8000
#define VIDMEM_MONOCHROME 0xb0000

//These macro constants specify the log level of the text (i.e. color and behaviour
#define LOG 0 
#define WARN 1
#define ERROR 2
#define PANIC 3
#define PANIC_SCREEN 4

// @param Screen printing API calls.
/* Public kernel API function */
void clearX();
int vga_init();
void putc(char c);
void kprint(const char* str, bool use_y, bool op_response, unsigned int logLevel); //op_response = print [ok] "msg" if TRUE
// void kernelLoading(char msg[100], int progressAmmount, int delay);
void putc_at(char ch, _uint32 color, _uint32 x, _uint32 y);
void kprint_at(char str[], _uint8 color, int x, int y);
void kprint_int(_ulong64 value, bool use_y, unsigned int logLevel);
void kclear();
int cursor_offset();
void welcome_msg();
char* kprint_op_ok();
void kprint_op_failure(char error[100]);
void init_flake_terminal();
void scroll();
void kprint_hex(_ulong64 n, bool use_y, bool op_response, unsigned int logLevel);
void kprintDBG(char* str, bool use_y, _uint32 ammount);

/* Public kernel API for the shell */
// void newline();
// void putc_s(char c);



/* Private kernel API functions */
static void reset_index();
static int get_offset(int x, int y);
static int offset(int x, int y);
static int ret_offset(int x, int y);
static int offset_scroll(int data);
static int calc_cur_offset_x();
static int calc_cur_offset_y();

enum vga_color {
    VGA_BLACK,
    VGA_BLUE,
    VGA_GREEN,
    VGA_CYAN,
    VGA_RED,
    VGA_MAGENTA,
    VGA_BROWN,
    VGA_LIGHT_GREY,
    VGA_DARK_GREY,
    VGA_LIGHT_BLUE,
    VGA_LIGHT_GREEN,
    VGA_LIGHT_CYAN,
    VGA_LIGHT_RED,
    VGA_LIGHT_MAGENTA,
    VGA_LIGHT_YELLOW,
    VGA_WHITE,
};

static inline _uint8 vga_entry_color(enum vga_color foreground, enum vga_color background){
    return foreground | (background << 4);
}

static inline _uint16 vga_entry(unsigned char c, _uint8 color){
    return (_uint16) c | ((_uint16) color << 8);
}

#endif
