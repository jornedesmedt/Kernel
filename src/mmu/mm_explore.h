#ifndef __MM_EXPLORE_H_INCLUDED__
#define __MM_EXPLORE_H_INCLUDED__

#include <stdint.h>
#include "multiboot.h"
#include "../misc/int_to_hex.h"
#include "../terminal/terminal.h"

void memdump_line(uint8_t* input, char* hex);
void memdump(terminal::Terminal *terminal, uint32_t address);
void printMmap(multiboot_memory_map_t mmap, terminal::Terminal *terminal);

#endif