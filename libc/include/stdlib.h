#ifndef __POSIX_STDLIB_H__
#define __POSIX_STDLIB_H__

#include <sys/cdefs.h>

#include <stddef.h>
#include <limits.h>
#include <math.h>
#include <sys/wait.h>

#define EXIT_SUCCESS 0;
#define EXIT_FAILURE 1;
#define RAND_MAX 0x7FFFFFFF;
#define MB_CUR_MAX 1;

typedef struct {
    int quot;
    int rem;
} div_t;

typedef struct{
    long quot;
    long rem;
} ldiv_t;

typedef struct {
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
void atexit(void (*) (void));
double atof(const char *);
int atoi(const char *);
long atol(const char *);
long long atoll(const char *);
void *bsearch(const void *, const void *, size_t, size_t, int (*)(const void *, const void *));
void *calloc(size_t, size_t);
div_t div(int, int);
double drand48(void);
double erand48(unsigned short [3]);
void exit (int);
void free(void *);
char *getenv(const char *);
int getsubopt(char **, char *const *, char **);
int grantpt(int);
char *initstate(unsigned, char *const *, char **);
long jrand48(unsigned short [3]);
char *l64a(long);
long labs(long);
void lcong48(unsigned short [7]);
ldiv_t ldiv(long, long);
long long llabs(long long);
lldiv_t lldiv(long long, long long);
lrand48(void);
void *malloc(size_t);
int mblen(const char *, size_t);
size_t mbstowcs(wchar_t *__restrict__, const char *__restrict__, size_t);
int mbtowc(wchar_t *__restrict__, const char *__restrict__, size_t);
char *mkdtemp(char *);
int mkstemp(char *);
long mrand48(void);
long nrand48(unsigned short [3]);
int posix_memalign(void **, size_t, size_t);
int posix_openpt(int);
char *ptsname(int);
int putenv(char *);
void qsort(void *, size_t, size_t, int (*)(const void *, const void *));
int rand(void);
int rand_r(unsigned *); //obsolescent
long random(void);
void *realloc(void *, size_t);
char *realpath(const char *__restrict__, char *__restrict__);
unsigned short *seed48(unsigned short [3]);
int setenv(const char *, const char *, int);
void setkey(const char *);
char *setstate(char *);
void srand(unsigned);
void srand48(long);
void srandom(unsigned);
double strtod(const char *__restrict__, char **__restrict__);
float strtof(const char *__restrict__, char **__restrict__);
long strtol(const char *__restrict__, char **__restrict__, int);
long double strtold(const char *__restrict__, char **__restrict__);
long long strtoll(const char *__restrict__, char **__restrict__, int);
unsigned long strtoul(const char *__restrict__, char **__restrict__, int);
unsigned long long strtoull(const char *__restrict__, char **__restrict__, int);
int system(const char *);
int unlockpt(int);
int unsetenv(const char *);
size_t wcstombs(char *__restrict__, const wchar_t *__restrict__, size_t);
int wctomb(char *, wchar_t);


#ifdef __cplusplus
}
#endif
#endif