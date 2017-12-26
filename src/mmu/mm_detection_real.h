#ifndef __MM_DETECTION_REAL_H_INCLUDED__
#define __MM_DETECTION_REAL_H_INCLUDED__
//May be required for running in real mode
//__asm__(".code16gcc\n");

#include <stdint.h>
typedef struct SMAP_entry
{
    uint64_t baseAddress;
    uint64_t length;
    uint32_t type;
    uint32_t ACPI;
}__attribute__((packed)) SMAP_entry_t;

//Load memory map to buffer, regparm(3) avoids stack issues with gcc in real mode
int __attribute__((noinline)) __attribute__((regparm(3))) detectMemory(SMAP_entry_t* buffer, int maxentries);

#endif