#include <BreezeOS/crypto/rand.h>

#define RAND_MAX 32767
unsigned long next = 1;

int rand(){
    next = next * 1103515245 + 12345;
    return (_uint32)(next/65536) % RAND_MAX+1; 
}

static void srand(_uint32 seed) {
    next = seed;
}
