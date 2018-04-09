#include <string.h>

void *memmove(void *dst, const void *src, size_t n)
{
    unsigned char* to = (unsigned char*) dst;
    const unsigned char* from = (const unsigned char*) src;

    if(from < to)
    {
        for(size_t i=0;i<n;i++)
        {
            to[i]=from[i];
        }
    }
    else
    {
        for(size_t i=n;i>0;i--)
        {
            to[i-1]=from[i-1];
        }
    }

    return dst;
}