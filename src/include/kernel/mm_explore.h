#ifndef __MM_EXPLORE_H_INCLUDED__
#define __MM_EXPLORE_H_INCLUDED__

#include <stdint.h>
#include <kernel/multiboot.h>
#include <kernel/int_to_hex.h>
#include <kernel/terminal.h>

void memdump_line(uint8_t* input, char* hex);
void memdump(terminal::Terminal *terminal, uint32_t address);
void printMmap(multiboot_memory_map_t mmap, terminal::Terminal *terminal);

#endif