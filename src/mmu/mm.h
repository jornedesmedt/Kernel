#ifndef __MM_H_INCLUDED__
#define __MM_H_INCLUDED__

#include <stdint.h>
//Returns a pointer to the payload of a memory block (minimum length size bytes)
void *malloc(size_t size);
void free(void *ptr);
//Resize payload region of ptr to size.
//Copy old data to new payload and free old payload
void *realloc(void *ptr, size_t size);

#endif