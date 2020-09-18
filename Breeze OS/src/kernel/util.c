/*
*
*   util.c by V01D. 
* 
*/

#include <BreezeOS/kernel/util.h>

//bootleg sleep function. This is the closest it get's without programming the PIT
void sleep(int time) {
     volatile int i, j;
     for (i=0; i<time; i++)
     {
         for (j=0; j < 250000; j++)
         {
            __asm__ __volatile__("nop");
         }
     }
}

//Integer to Hex
// Mathmatical reference: rapidtables.com
char* decToHexa(int n)
{
    // char array to store hexadecimal number 
    char hexaDeciNum[100];

    // counter for hexadecimal number array 
    int i = 0; 

    while(n != 0) 
    {    
        // temporary variable to store remainder 
        int temp  = 0;

        // storing remainder in temp variable. 
        temp = n % 16;

        // check if temp < 10 
        if(temp < 10)
        { 
            hexaDeciNum[i] = temp + 48; 
            i++; 
        } 

        else
        { 
            hexaDeciNum[i] = temp + 55; 
            i++; 
        } 
        n = n/16; 
    } 
    // printing hexadecimal number array in reverse order 
    char result[100];
    char* s = "0x";
    char* final;
    
    for(int j=i-1; j>=0; j--)
        result[j] = hexaDeciNum[j];
    
    final = strcat("0x", str_reverse(result));
    
    return final;
}

int str_to_int(char* str)
{
    int len;
    int result = 0;
    len = strlen(str);
    for (int i = 0; i < len; i++)
    {
        result = result * 10 + (str[i] - '0');
    }
    return result;
}

int strlen(const char* str)
{
    int len = 0;
    while (str[len] != '\0')
    {
        len++;
    }
    return len;
}

_uint32 digit_count(int num)
{
    int result = 0;
    while (num != 0)
    {
        num = num / 10;
        result++;
    }
    return result;
}

//From https://www.codeproject.com/Articles/1225196/Create-Your-Own-Kernel-In-C-2
int itoa(int num, char *number)
{
  int dgcount = digit_count(num);
  int index = dgcount - 1;
  char x;
  
  if(num == 0 && dgcount == 1){
    number[0] = '0';
    number[1] = '\0';
  }
  
  else
  {
      while(num != 0)
      {
        x = num % 10;
        number[index] = x + '0';
        index--;
        num = num / 10;
      }
      number[dgcount] = '\0';
  }
}

void memcpy(char* src, char* dst, int Abytes)
{
        for (int i = 0; i<Abytes; i++) {
            *(dst + i) = *(src + i);
        }
}

void memset(void* dst, char value, _uint32 length)
{
    char* tmp = (char*)dst;
    for (; length != 0; length--)
        *tmp++ = value;
}

char* str_reverse(char str[])
{
    char temp;
    int i, j = 0;
    i = 0;
    j = strlen(str) - 1; // counting the length
    while (i < j) // for reversing string
    {        
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++;
        j--;
    }
    return str;
}

char* strcat(char* a, char* b)
{
    char* ptr = a + strlen(a);
    
    while (*b != '\0')
		*ptr++ = *b++;

	// null terminate destination string
	*ptr = '\0';

	return a;
}

