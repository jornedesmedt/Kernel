#include "mm.h"

void init_mm()
{
    first_address = ((uint32_t)&KERNEL_END) + 1;
    next_address = first_address;
}

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
}