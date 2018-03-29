#include "mm.h"

//Set intial values for globals
multiboot_memory_map_t* MEMORY_MAP;
uint32_t MEMORY_MAP_COUNT = 0;
uint32_t TOTAL_MEMORY = 0;
uint32_t USABLE_MEMORY = 0;

void init_mm(multiboot_uint32_t mmap_addr, multiboot_uint32_t mmap_length)
{
    //Get the memory map
    MEMORY_MAP = (multiboot_memory_map_t*)mmap_addr;
    MEMORY_MAP_COUNT = 0;
    TOTAL_MEMORY = 0;
    USABLE_MEMORY = 0;
    
    do
    {
        TOTAL_MEMORY += MEMORY_MAP[MEMORY_MAP_COUNT].len;

        //If high memory and available, clear memory, except for the bit where the kernel is loaded, don't remove the kernel, that would probably be bad
        if(MEMORY_MAP[MEMORY_MAP_COUNT].addr >= 0x100000 && MEMORY_MAP[MEMORY_MAP_COUNT].type == MULTIBOOT_MEMORY_AVAILABLE)
        {
            USABLE_MEMORY += MEMORY_MAP[MEMORY_MAP_COUNT].len;
            uint32_t start_addr = (uint32_t)MEMORY_MAP[MEMORY_MAP_COUNT].addr; //((uint32_t)MEMORY_MAP[MEMORY_MAP_COUNT].addr >= (uint32_t)&KERNEL_END)?(uint32_t)MEMORY_MAP[MEMORY_MAP_COUNT].addr:(uint32_t)&KERNEL_END;
            uint32_t end_addr = (uint32_t)MEMORY_MAP[MEMORY_MAP_COUNT].addr + MEMORY_MAP[MEMORY_MAP_COUNT].len;
            if(end_addr > start_addr)
            {
                //Clear memory between start_addr and end_addr
                uint32_t i=0;
                uint32_t* memory = (uint32_t*) start_addr;
                while((uint32_t)&memory[i] < end_addr)
                {            
                    if(/*(uint32_t)&memory[i] < 0xC0000000 - 4||*/ (uint32_t)&memory[i] > (uint32_t)&KERNEL_END)
                    {
                        //memory[i] = 0;
                    }
                    ++i;
                }
            }
        }
        
        ++MEMORY_MAP_COUNT;
    }
    while((uint32_t)&MEMORY_MAP[MEMORY_MAP_COUNT] < (uint32_t)mmap_addr + mmap_length);
}
/*
extern "C"
{
//malloc() shall allocate unused space for an object whose size in bytes is specified by size and whose value is unspecified.
    void *malloc(size_t size)
    {
        if(size != 0)
        {
            //Find space to allocate object of size
            //On failure, return NULL and set errno to ENOMEM (insufficient memory) (errno.h)
        }
        else
        {
            //Return NULL and set errno (errno.h)
            return NULL;
        }
    }
}

extern "C"
{
    void free(void *ptr)
    {
        
    }
}*/