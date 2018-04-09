#ifndef __POSIX_STRING_H_INCLUDED__
#define __POSIX_STRING_H_INCLUDED__

#include <stddef.h>
#include <stdarg.h>
#include <overloading.h>

#ifdef __cplusplus
extern "C" {
#endif

void *memset(void *, int, size_t);
//size_t strlen(const char *);
size_t strlen1(const char *);
size_t strlen2(const char *, size_t);

#define strlen(...)\
        CAT(strlen, COUNT_PARMS(__VA_ARGS__)) (__VA_ARGS__)

#ifdef __cplusplus
}
#endif

#endif