#include "paging.h"

extern "C" void setup_paging(uint32_t* page_directory_address); //External ASM function: paging.asm

void initializePaging()
{
    initializePageDirectory();
    first_page_table = allocateNext();
    initializePageTable(first_page_table);
    setup_paging(page_directory);
}

void initializePageDirectory()
{
    page_directory = (uint32_t*) KERNEL_END;
    for(int i=0; i<1024; ++i)
    {
        page_directory[i] = 0x00000002; //Readwrite
    }
}

void initializePageTable(uint32_t page_table[])
{
    for(unsigned int i=0; i<1024; ++i)
    {
        page_table[i] = (i * 0x1000) | 3; //Supervisor, read/write, present
    }

    for(uint32_t i=0; i<1024;++i)
    {
        if(page_directory[i] & 1 == 0) //Check the page directory for an entry where the present flag is not set
        {
            //Add page table to directory
            page_directory[directoryIndex] = ((uint32_t)&page_table) | 3; //Set address and set present and read/write
            return;
        }
    }
    //TODO: Page directory full
}

uint32_t* allocateNext()
{    
    //Check if the new address is still within available memory

    for(uint32_t i=0; i<MEMORY_MAP_COUNT; ++i) //Find the current memory block
    {
        uint32_t blockMin = (uint32_t)MEMORY_MAP[i].addr;
        uint32_t blockMax = (uint32_t)MEMORY_MAP[i].addr + (uint32_t)MEMORY_MAP[i].len;
        uint32_t addr = (uint32_t) &freeAddress;

        if(addr >= blockMin && addr < blockMax)
        {
            //This is the block we're in now.
            if(addr <= blockMax - 0x1000)
            {
                //There's enough space in the current block for another 4kb
                //increment freeAddress
                freeAddress = (uint32_t*)((uint32_t)&freeAddress + 0x1000); //Add 4kb
                return freeAddress;
            }
            else
            {
                //Check if there's another available block
                for(int j=0; i+j<MEMORY_MAP_COUNT; j++)
                {
                    if(MEMORY_MAP[i+j].type == MULTIBOOT_MEMORY_AVAILABLE && MEMORY_MAP[i+j].len > 0x1000) //Is block availble and does it have enough space?
                    {
                        if(MEMORY_MAP[i+j].addr % 0x1000 == 0) //Check if address is 4kb aligned
                        {
                            freeAddress = (uint32_t *) MEMORY_MAP[i+j].addr;
                        }
                        else
                        {
                            addr = (MEMORY_MAP[i+j].addr & 0xFFFFF000) + 0x1000; //Get next 4kb aligned address
                            blockMax = (uint32_t)MEMORY_MAP[i+j].addr + (uint32_t)MEMORY_MAP[i+j].len; //Calculate end of the block
                            if(addr <= blockMax - 0x1000) //Does new aligned space still fit inside the new block?
                            {
                                freeAddress = (uint32_t*) addr;
                                return freeAddress;
                            }
                            else
                            {
                                continue; //Check next block in the memory map
                            }
                        }
                    }
                }
                break; //All blocks have been checked, no need to continue the outer loop.
            }
        }
    }

    return NULL; //Return null if no space was found
}