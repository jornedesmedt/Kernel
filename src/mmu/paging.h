#ifndef __PAGING_H_INCLUDED__
#define __PAGING_H_INCLUDED__

#include <stdint.h>
#include "mm.h"
#include "multiboot.h"

        /*
        *   Page directory enties are 32 bits each, 4KB aligned
        *   31-12:  Page table 4KB aligned address
        *   11-9:   Not used by processor, free usage for OS
        *   8:      Ignored
        *   7:      Page size (0=4KB, 1=4MB)
        *   6:      
        *   5:      Accessed
        *   4:      Cache disabled
        *   3:      Write through
        *   2:      User(1)/Superviser(0)
        *   1:      Read/Write
        *   0:      Present (1 if page is in physical memory). If 0, processor ignores all other bits.
        */
        uint32_t* page_directory;//[1024] __attribute__((aligned(4096))); //Ignore error, it's wrong
        uint32_t* first_page_table;//[1024] __attribute__((aligned(4096)));
        uint32_t directoryIndex = 0;

        void initializePageDirectory();
        void initializePageTable(uint32_t page_table[]);
        void initializePaging();

        extern uint32_t KERNEL_START; //Physical start of the kernel, set in linker
        extern uint32_t KERNEL_END; //Physical end of the kernel, set in linker
        
        uint32_t* freeAddress;
        uint32_t* allocateNext(); //Return a pointer to the next free address for a directory table, page table or page and incremement freeAddress to the end
#endif