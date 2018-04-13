#ifndef __POSIX_STDLIB_H__
#define __POSIX_STDLIB_H__

#include <sys/cdefs.h>
#include <stddef.h>
#include <sys/wait.h>

#define EXIT_SUCCESS 0;
#define EXIT_FAILURE -1;
#define RAND_MAX 0x7FFFFFFF;
#define MB_CUR_MAX 1;

typedef struct div {
    int quot;
    int rem;
} div_t;

typedef struct ldiv {
    long quot;
    long rem;
} ldiv_t;

typedef struct lldiv {
    long long quot;
    long long rem;
} lldiv_t;

#ifdef __cplusplus
extern "C"{
#endif

__attribute__((__noreturn__))
void _Exit(int);
long a641(const char *);
void abort(void);
void abs(int);
void atexit(int);

#ifdef __cplusplus
}
#endif
#endif