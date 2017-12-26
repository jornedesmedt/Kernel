#include "mm_detection_real.h"
int __attribute__((noinline)) __attribute__((regparm(3))) detectMemory(SMAP_entry_t* buffer, int maxEntries)
{
    uint32_t cont_ID = 0;
    int entries = 0, signature, bytes;
    do
    {
        __asm__ __volatile__ ("int $0x15"
            : "=a" (signature), "=c" (bytes), "=b" (cont_ID)
            : "a" (0xE820), "b" (cont_ID), "c" (24), "d" (0x534D4150), "D" (buffer));
        if(signature != 0x534D4150)
            return -1; //error
        if(bytes > 20 && (buffer->ACPI & 0x0001) == 0)
        {
            //ignore this entry
        }
        else
        {
            buffer++;
            entries++;
        }
    }
    while(cont_ID != 0 && entries < maxEntries);
    return entries;
}