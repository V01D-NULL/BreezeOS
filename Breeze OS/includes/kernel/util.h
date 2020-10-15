#ifndef _UTIL_H
#define _UTIL_H

#include "../cpu/types.h"

void sleep(int time);
int str_to_int(char* str);
int strlen(const char* str);
int itoa(int num, char *number);
_uint32 digit_count(int num);
void memset(void* dst, char value, _uint32 length);
void memcpy(void* src, void* dst, int Abytes); //Abytes = Ammount of bytes
char* str_reverse(char str[]);
char* strcat(char* a, char* b);
char* decToHexa(int n);

#endif
