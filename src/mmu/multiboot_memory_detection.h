#ifndef __MULTIBOOT_MEMORY_DETECTION_H_INCLUDED__
#define __MULTIBOOT_MEMORY_DETECTION_H_INCLUDED__
//May be required for running in real mode
//__asm__(".code16gcc\n");

typedef struct multiboot_memory_map {
	unsigned int size;
	unsigned int base_addr_low,base_addr_high;
// You can also use: unsigned long long int base_addr; if supported.
	unsigned int length_low,length_high;
// You can also use: unsigned long long int length; if supported.
	unsigned int type;
} multiboot_memory_map_t;

#endif