#ifndef __POSIX_STDIO_H__
#define __POSIX_STDIO_H__

#include <sys/cdefs.h>

#define EOF (-1)

#ifdef __cplusplus
extern "C"{
#endif

int printf(const char *__restrict__, ...);
int putchar(int);
int puts(const char*);

#ifdef __cplusplus
}
#endif
#endif