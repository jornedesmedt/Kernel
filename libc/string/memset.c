#include <string.h>
void *memset(void *str, int value, size_t size)
{
    unsigned char* buffer = (unsigned char*) str;
    for(size_t i=0; i<size; i++)
    {
        buffer[i] = (unsigned char) value;
    }
    return str;
}