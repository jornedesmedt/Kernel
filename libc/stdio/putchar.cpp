#include <stdio.h>
#if defined(__is_libk)
    #include <kernel/terminal.h>
#endif

int putchar(int c)
{
#if defined(__is_libk)
    terminal::putChar((char)c);
#else
    //TODO: implement stdio
#endif
    return c;
}