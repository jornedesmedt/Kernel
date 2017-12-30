#ifndef __MM_H_INCLUDED__
#define __MM_H_INCLUDED__

#include <stdint.h>
#include <stddef.h>
//#include <stdlib.h>
#include "multiboot.h"

extern multiboot_memory_map_t* MEMORY_MAP; //The memory map, set from main
extern uint32_t MEMORY_MAP_COUNT; //The number of entries in the memory map, set from main after running through memory map the first time
extern uint32_t KERNEL_START; //Physical start of the kernel, set in linker
extern uint32_t KERNEL_END; //Physical end of the kernel, set in linker

extern uint32_t TOTAL_MEMORY;
extern uint32_t USABLE_MEMORY;

void init_mm(multiboot_uint32_t mmap_addr, multiboot_uint32_t mmap_length); //Initiate the memory manager.

#endif