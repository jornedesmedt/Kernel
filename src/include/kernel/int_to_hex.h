#ifndef __INT_TO_HEX_H_INCLUDED__
#define __INT_TO_HEX_H_INCLUDED__
#include <stdint.h>

void int_to_hex(uint32_t input, char* hex);
void int_to_hex(uint64_t input, char* hex);
#endif