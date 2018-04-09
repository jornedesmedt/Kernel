#include <string.h>

void *memcpy(void *__restrict__ dst, const void *__restrict__ src, size_t n)
{
   /* size_t d = &dst;
    size_t s = &src;
    if(d==s || ((d<s) && (s-d<n)) || ((d>s) && (d-s<n)))
    {
        return; //ERROR, overlap, undefined behaviour, return nothing.
    }*/

    unsigned char* to = (unsigned char*) dst;
    unsigned char* from = (unsigned char*) src;

    for(size_t i=0;i<n;i++)
    {
        to[i]=from[i];
    }
    return dst;
}