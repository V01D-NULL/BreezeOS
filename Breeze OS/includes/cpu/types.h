#ifndef _TYPES_H
#define _TYPES_H

#define NULL (void*)0
#define TRUE 1
#define FALSE 0

typedef unsigned long _ulong64;
typedef signed long _long64;
typedef unsigned int _uint32;
typedef signed int _int32;
typedef unsigned short _uint16;
typedef signed short _int16;
typedef unsigned char _uint8;
typedef signed char _int8;
typedef int bool;
// typedef const char* string; //Usage should be for higher ring levels. Perhaps I will use it in ring 2, for sure in ring 3.

#endif
