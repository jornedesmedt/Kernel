#include <string.h>

//ISO C
size_t strlen1(const char* s)
{
    size_t len = 0;
    while (s[len])
        len++;
    return len;
}

//POSIX extention on ISO C
size_t strlen2(const char* s, size_t maxlen)
{
    size_t len = 0;
    while (s[len] && len < maxlen)
        len++;
    return len;
}