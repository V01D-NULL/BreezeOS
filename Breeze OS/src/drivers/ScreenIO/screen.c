#include <drivers/ScreenIO/screen.h>


_int16* vidmem = (_uint16*) VIDMEM;
_uint32 _x;
_uint32 _y;
_uint8 color;
static bool flake_init = FALSE;

int vga_init(enum vga_color foreground, enum vga_color background)
{
    _x = 0;
    _y = 0;
    color = vga_entry_color(foreground, background);
    for (int y = 0; y < VGA_HEIGHT; y++)
    {
        for (int x = 0; x < VGA_WIDTH; x++)
        {
            const int index = y * VGA_WIDTH + x;
            vidmem[index] = vga_entry(' ', color);
        }
    }
    return color;
}

//Draw a banner at y (0 and 24). This can be used as some kind of message screen or something
void bannerDraw() {
    int temp_y = _y; //Save y
    
    _x = 0;
    _y = 0;
    char* banner = "\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB";
    
    kprint(banner, FALSE, FALSE, PANIC_SCREEN);
    _y = 24;
    kprint(banner, FALSE, FALSE, PANIC_SCREEN);
    _y = ++temp_y; //Restore y coordinate
}

void welcome_msg()
{
    _x = 0;
    _y = 0;

    #ifdef VERBOSE
    int info_bracket_color = vga_entry_color(VGA_LIGHT_GREY, VGA_BLACK);
    int text = vga_entry_color(VGA_WHITE, VGA_BLACK);
    int special = vga_entry_color(VGA_LIGHT_BLUE, VGA_BLACK);
    #else
    bannerDraw();
    int info_bracket_color = vga_entry_color(VGA_LIGHT_GREY, VGA_LIGHT_BLUE);
    int text = vga_entry_color(VGA_WHITE, VGA_LIGHT_BLUE);
    int special = vga_entry_color(VGA_BLUE, VGA_LIGHT_BLUE);
    #endif
    
    
    char msg_pt_1[] = " Welcome to ";
    char msg_pt_2[] = "Breeze OS! ";
    
    putc_at('[', info_bracket_color, _x++, _y);
    
    for (int i = 0; i < strlen(msg_pt_1); i++)
    {
        putc_at(msg_pt_1[i], text, _x++, _y);
    }
    
    for (int j = 0; j < strlen(msg_pt_2); j++)
    {
        putc_at(msg_pt_2[j], special, _x++, _y);
    }
    
    putc_at(']', info_bracket_color, _x++, _y);
    
    _y+=2;
    
    sleep(200);
}

//Prints [ok] if function worked correctly
char* kprint_op_ok()
{
#ifdef VERBOSE
    _x = 0;

    int info_bracket_color = vga_entry_color(VGA_LIGHT_GREY, VGA_BLACK);
    int msg_color = vga_entry_color(VGA_GREEN, VGA_BLACK);
    
    /* I'm too lazy to improve this. */
    if (_y < 24) {
        putc_at('[', info_bracket_color, _x++, _y);
        putc_at('O', msg_color, _x++, _y);
        putc_at('K', msg_color, _x++, _y);
        putc_at(']', info_bracket_color, _x++, _y);
    }
    
    _y++;
    
    if (_y > 24)
    {
        _x = 0;
        _y = 24;
        scroll();
        putc_at('[', info_bracket_color, _x++, _y);
        putc_at('O', msg_color, _x++, _y);
        putc_at('K', msg_color, _x++, _y);
        putc_at(']', info_bracket_color, _x++, _y);
    }
#endif
}

void kprint_op_failure(char error[100])
{
    _x = 5;
    
    #ifdef VERBOSE
    int info_bracket_color = vga_entry_color(VGA_LIGHT_GREY, VGA_BLACK);
    int msg_color = vga_entry_color(VGA_RED, VGA_BLACK);
    int err_msg_color = vga_entry_color(VGA_LIGHT_GREY, VGA_BLACK);
    #else
    
    int info_bracket_color = vga_entry_color(VGA_LIGHT_GREY, VGA_LIGHT_BLUE);
    int msg_color = vga_entry_color(VGA_BLACK, VGA_LIGHT_BLUE);
    int err_msg_color = vga_entry_color(VGA_LIGHT_GREY, VGA_LIGHT_BLUE);
    #endif
    
    char msg[100] = "Failure: ";
    
    putc_at('[', info_bracket_color, _x++, _y);
    
    for (int i = 0; i < strlen(msg); i++)
    {
        putc_at(msg[i], msg_color, _x++, _y);
    }
    
    for (int j = 0; j < strlen(error); j++)
    {
        if (error[j] == '\n')
        {
            _y++;
            _x = 0;
        }
        else if (error[j] == '\t')
            _x += 8;
        else
            putc_at(error[j], err_msg_color, _x++, _y);
    }
    
    putc_at(']', info_bracket_color, _x++, _y);
    _y++;
    sleep(300);
//     if (_y > 24)
//     {
//         _y = 24;
//         _x = 0;
//         scroll();
//     }
//     #ifdef aesthetic
//     sleep(40);
//     #endif
}

static void terminal_write_wrapper(const char* data, _uint32 size, bool use_y, bool op_response) {
    
    #ifdef VERBOSE
    int bracket_color =  vga_entry_color(VGA_LIGHT_GREY, VGA_BLACK);
    #else
    int bracket_color = vga_entry_color(VGA_LIGHT_GREY, VGA_LIGHT_BLUE);
    #endif
    
    int ok_color = vga_entry_color(VGA_GREEN, VGA_BLACK);
    
    if (use_y)
    {
        _x = 0;
        //clear x line
        for (int k = 0; k < 80; k++)
        {
            putc_at(' ', color, k, _y);
        }
        
        if (op_response==TRUE)
        {
            putc_at('[', bracket_color, _x++, _y);
            putc_at('O', ok_color, _x++, _y);
            putc_at('K', ok_color, _x++, _y);
            putc_at(']', bracket_color, _x++, _y);
            _x += 1;
        }
        else
            _x = 5;
        putc_at('[', bracket_color, _x++, _y);
        for (int i = 0; i < size; i++)
        {
            if (_y > 24)
            {
                _y = 24;
                _x = 0;
                
                scroll();
                if (op_response==TRUE)
                {
                    putc_at('[', bracket_color, _x++, _y);
                    putc_at('O', ok_color, _x++, _y);
                    putc_at('K', ok_color, _x++, _y);
                    putc_at(']', bracket_color, _x++, _y);
                    _x += 1;
                }
                else
                    _x = 5;
                
                putc_at('[', bracket_color, _x++, _y);
                _x++;
            }
            else
            {
                _x++;
            }
            if (data[i] == '\n')
            {
                _y++;
                _x = 0;
            }
            else if (data[i] == '\t')
                _x += 8;
            else
                putc(data[i]);
        }
        putc_at(']', bracket_color, _x+=2, _y++);

            
        #ifdef aesthetic
        sleep(20);
        #endif
    }
    
    else if (!use_y)
    {
        _x = 0;
        for (int i = 0; i < size; i++)
        {
            putc(data[i]);
            _x++;
        }
    }
}

void kprint(const char* str, bool use_y, bool op_response, unsigned int logLevel)
{
    #ifdef VERBOSE
    int temp_color = color; //Save the color
    switch (logLevel)
    {
        case LOG:
            color = vga_entry_color(VGA_WHITE, VGA_BLACK);
            terminal_write_wrapper(str, strlen(str), use_y, op_response);
            color = temp_color;
            break;
            
        case WARN:
            color = vga_entry_color(VGA_LIGHT_YELLOW, VGA_BLACK);
            terminal_write_wrapper(str, strlen(str), use_y, op_response);
            color = temp_color;
            break;
            
        case ERROR:
            color = vga_entry_color(VGA_RED, VGA_BLACK);
            terminal_write_wrapper(str, strlen(str), use_y, op_response);
            color = temp_color;
            break;
        
        case PANIC:
            kclear();
            bannerDraw();
            terminal_write_wrapper(str, strlen(str), use_y, op_response);
            _y = 1;
            break;
            
        case PANIC_SCREEN:
            color = vga_entry_color(VGA_LIGHT_BLUE, VGA_BLACK);
            terminal_write_wrapper(str, strlen(str), use_y, op_response);
            break;
            
        default:
            break;
    }
    
    #endif
}

void kprintDBG(char* str, bool use_y, _uint32 ammount) {
    
    #ifdef VERBOSE
    int DBG_NOTICE_COLOR = vga_entry_color(VGA_MAGENTA, VGA_BLACK);
    int color_default = vga_entry_color(VGA_WHITE, VGA_BLACK);
    int info_bracket_color = vga_entry_color(VGA_LIGHT_GREY, VGA_BLACK);
    
    const char* new_str = strcat("<BREEZE_DEBUG> ", str);
    const int new_str_len = strlen(new_str);
    
    _x = 5;
    
    int catch_y_overwrite = _y; //If kprintDBG had to wrap around to the next line, increment y accordingly to avoid overwriting the debug message
    
    if (_y > 24)
    {
        _y = 24;
        _x = 5;
                
        scroll();
    }
    
    putc_at('[', info_bracket_color, _x++, _y);
    //15 is the <BREEZE_DEBUG> message length, only that part should be magenta.
    for (int i = 0; i < 15; i++)
    {
        putc_at(new_str[i], DBG_NOTICE_COLOR, _x++, _y);
    }
    
    for (int i = 0; i < strlen(str); i++)
    {
        if (_x >= 80)
        {
            _y++;
            _x = 0;
        }
        
        if (str[i] == '\n')
            _y++;
        else
            putc_at(str[i], color_default, _x++, _y);
    }
    putc_at(']', info_bracket_color, _x++, _y);
    
    if (use_y)
    {
        if (ammount == 0)
            _y++;
        else
            _y+=ammount;
    }
    sleep(10);
    #endif
}

void clearX() {
    _x = 0;
    int nonVerboseColor = vga_entry_color(VGA_LIGHT_GREY, VGA_LIGHT_BLUE);
    for (int j = 0; j < 80; j++)
    {
        //Just changes colors
        #ifdef VERBOSE
        putc_at(' ', color, j, _y); //Clear the x line
        #else
        putc_at(' ', nonVerboseColor, j, _y); //Clear the x line
        #endif
    }
}

//Broken
// void kernelLoading(char msg[100], int progressAmmount, int delay) {
//     _x = 2;
//     int info_bracket_color = vga_entry_color(VGA_LIGHT_GREY, VGA_LIGHT_BLUE);
//     strcat(msg, " \xDB");
//     
//     for (int i = 0; i < 80; i++)
//     {
//         clearX();
//         kprint(msg, FALSE, FALSE);
//         strcat(msg, "\xDB");
//     }
//     _y++;
// }

/**********************************************************************************************************************/
//Special functions: These functions will print the interrupt that occured regardless of VERBOSE mode enabled, or disabled.
// void kprint_INTERRUPT(const char* str, bool use_y, bool op_response)
// {
//     terminal_write_wrapper(str, strlen(str), use_y, op_response);
// }
// 
// void kprint_INTERRUPT_int(_ulong64 value, bool use_y, bool op_response)
// {
//     char str_num[digit_count(value)+1];    
//     itoa(value, str_num);
//     kprint_INTERRUPT((_uint8*) str_num, use_y, op_response);
// }
/**********************************************************************************************************************/

void kprint_int(_ulong64 value, bool use_y, unsigned int logLevel)
{
    char str_num[digit_count(value)+1];    
    itoa(value, str_num);
    kprint((_uint8*) str_num, use_y, FALSE, logLevel);
}

//Create an enum with decimal & hexadecimal numbers. After getting the remainder of the division, find the corresponding decimal number, and set result = dec_to_hex[correct number (which should be temp)]
// static enum dec_to_hex
// {
//     0 = 0,
//     1 = 1,
//     2 = 2, 
//     3 = 3,
//     4 = 4,
//     5 = 5,
//     
// };

//Make use of ascii table. (Convert integer input into array. Loop through each item in the array. Get the integers corresponding ascii code. Change the integer ascii code to the integer hex code. So: int_array[i] = int_ascii_to_hex(int_array[i]);
void kprint_hex(_ulong64 n, bool use_y, bool op_response, unsigned int logLevel)
{
    char* n_2 = decToHexa(n);
    kprint(n_2, use_y, op_response, logLevel);
}

void putc_at(char ch, _uint32 color, _uint32 x, _uint32 y)
{
    int index = y * VGA_WIDTH + x;
    vidmem[index] = vga_entry(ch, color);
}

void putc(char c)
{
    if(_x == VGA_WIDTH || c == '\n')
    {
        _x = 0;
        if(_y == VGA_HEIGHT-1)
            scroll();
        else {
            _y++;
        }
    }
    
    if (c == '\n')
        return;
    putc_at(c, color, _x, _y);
}

void kclear()
{
    for (int i = 0; i < VGA_HEIGHT; i++)
    {
        for (int a = 0; a < 80; a++)
        {
            putc_at(' ', color, a, i);
        }
    }
    _x, _y = 0;
}

void scroll()
{    
    int i = 0;
    for(i = 0; i < (VGA_WIDTH*VGA_HEIGHT-80); i++)
        vidmem[i] = vidmem[i+80];
    for(i = 0; i < VGA_WIDTH; i++)
        vidmem[(VGA_HEIGHT - 1) * VGA_WIDTH + i] = vga_entry(' ', color);

}

static int offset_scroll(int data)
{
    return data / (2 * VGA_WIDTH);
}

static int get_offset(int x, int y)
{
    return 2 * (y * VGA_WIDTH + x);
}

static int ret_offset(int x, int y)
{
    return (y * VGA_WIDTH) + x;
}

// static void flake_init_message(char msg[])
// {
//     _x = 0;
//     _y = 0;
//     putc_at('[', vga_entry_color(VGA_LIGHT_GREY, VGA_BLACK), _x++, _y);
//     
//     for (int i = 0; i < strlen(msg); i++)
//     {
//         putc_at(msg[i], vga_entry_color(VGA_LIGHT_BLUE, VGA_BLACK), _x++, _y);
//     }
//     putc_at(']', vga_entry_color(VGA_LIGHT_GREY, VGA_BLACK), _x++, _y++);
// }

void init_flake_terminal()
{
    #ifndef FLAKE_VERSION
    #define FLAKE_VERSION "???"
    #endif
    
//     Reset VGA
    if (flake_init != TRUE)
    {
        kclear();
//         flake_init_message(strcat("Flake Shell V.", FLAKE_VERSION));
        _x = 0;
        _y = 0;
        flake_init = TRUE;
//         newline();
    }
    else
    {
        kclear();
        _x, _y = 0;
        kprint_op_failure("Flake Shell has already been initialized!");
//         newline();
    }
}
