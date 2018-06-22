#include <kernel/page_frame_allocator.h>

page_directory_t* kernel_directory;
page_directory_t* current_directory; //Directory for whatever task is currently running

uint32_t number_of_frames; //Number of frames that can be loaded
uint32_t *frames; //Bitmap, 0 is free, 1 is taken.

#define FRAME_INDEX(physical_address) physical_address / 32; //Calculate the index of which uint32_t (in frames) the frame is in.
#define FRAME_BIT(physical_address) physical_address / 32; //Calculate the bit which represents the exact frame

#define KERNEL_HEAP_START 0x00800000;
#define KERNEL_HEAP_END 0x20000000; //512MB

extern void* placement_pointer = &KERNEL_END;
uintptr_t 

struct
{
    uint32_t index;
    uint32_t bit;
} frame_index_t;

void setup_paging(multiboot_memory_map *mmap, uint32_t address, uint32_t length, uint32_t memory_available_kb)
{
    number_of_frames = memory_available_kb / 4;
    do
    {       
            if(mmap[i].type == 1)
            {
                
            }
            ++i;
            
    }
    while((uint32_t)&mmap[i] < (uint32_t) address + length);
}

frame_index_t find_free_frame()
{
    for(int i=0; i<number_of_frames; i++)
    {
        frame_index_t result;
        if(frames[i] != 0xffffffff)
        {
            result.index = i;
            for(int j=0; j<32; j++)
            {
                if(!((frames[i] >> j) & 1)) //Check for first zero bit.
                {
                    result.bit = j;
                }
            }
        }
    }
}

void set_frame(uint32_t index, uint32_t bit)
{
    frames[i] |= (1 << bit);
}

void unset_frame(uint32_t index, uint32_t bit)
{
    frames[i] &= ~(1 << bit);
}

uintptr_t kmalloc(size_t size, uintptr_t align, uintptr_t * physical)
{
    
}