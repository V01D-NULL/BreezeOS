#define cpuid(in, a, b, c, d) __asm__("cpuid": "=a" (a), "=b" (b), "=c" (c), "=d" (d) : "a" (in));

#include <cpu/CPUID/cpuid.h>

void detect_cpu()
{
    _ulong64 unused, ebx;
    cpuid(0, unused, ebx, unused, unused);
    switch (ebx)
    {
        case 0x756e6547:
            kprint("CPU VENDOR: Intel", TRUE, FALSE, LOG);
            break;
        case 0x68747541:
            kprint("CPU VENDOR: AMD", TRUE, FALSE, LOG);
            break;
        default:
            kprint("Unkown x86 CPU detected, you may or may not experience some problems", TRUE, FALSE, WARN);
            
            break;
    }
}
