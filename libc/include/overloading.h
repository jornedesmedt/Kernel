///Just a header file containing some definitions to help with overloading C functions

#ifndef __OVERLOADING_H__
#define __OVERLOADING_H__

#define COUNT_PARMS2(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _, ...) _
#define COUNT_PARMS(...)\
        COUNT_PARMS2(__VA_ARGS__, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1)
#define CAT(A, B) CAT2(A, B)
#define CAT2(A, B) A ## B

#endif