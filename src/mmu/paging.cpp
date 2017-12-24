#include "paging.h"

extern "C" void setup_paging(uint32_t* page_directory_address); //External ASM function: paging.asm

void initializePaging()
{
    initializePageDirectory();
    initializePageTable(first_page_table);
    setup_paging(page_directory);
}

void initializePageDirectory()
{
    for(int i=0; i<1024; ++i)
    {
        page_directory[i] = 0x00000002;
    }
}

void initializePageTable(uint32_t page_table[])
{
    for(unsigned int i=0; i<1024; ++i)
    {
        page_table[i] = (i * 0x1000) | 3; //Supervisor, read/write, present
    }
}