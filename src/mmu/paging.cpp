#include "paging.h"

extern "C" void setup_paging(uint32_t* page_directory_address); //External ASM function: paging.asm
//Turns out I should be doing this from boot.asm, before calling kernel_main
void initializePaging()
{
    initializePageDirectory();
    //first_page_table = allocateNext();
    //initializePageTable(first_page_table);
    //Identity page first megabytes
    setupIdentityPaging(page_directory, 0x0, 0xfffff, 3);
    //TODO: Map kernel from KERNEL_START->KERNEL_END to 0xc0000000->+kernel size
    //TODO: Map paging structures beyond 0xc0000000, after the kernel
    setupVirtualAddressPaging(page_directory, KERNEL_START, freeAddress + 0x0fff, 0xc000000, 3);

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

void setupVirtualAddressPaging(uint32_t* page_directory, uint32_t startAddress, uint32_t endAddress, uint32_t startVirtualAddress, uint32_t flags=0)
{
    uint32_t endVirtualAddress = startVirtualAddress + endAddress - startAddress;
    uint32_t addressDifference = startVirtualAddress - startAddress;

    uint32_t index_directory_first_table = startVirtualAddress / PAGE_TABLE_SIZE;
    uint32_t index_directory_last_table = endVirtualAddress / PAGE_TABLE_SIZE;
    uint32_t index_first_page = (startVirtualAddress % PAGE_TABLE_SIZE) / PAGE_TABLE_SIZE;
    uint32_t index_last_page = (endVirtualAddress % PAGE_TABLE_SIZE) / PAGE_TABLE_SIZE;
}

void setupIdentityPaging(uint32_t* page_directory, uint32_t startAddress, uint32_t endAddress, uint32_t flags = 0)
{
    uint32_t index_directory_first_table = startAddress / PAGE_TABLE_SIZE;
    uint32_t index_directory_last_table = endAddress / PAGE_TABLE_SIZE;
    uint32_t index_first_page = (startAddress % PAGE_TABLE_SIZE) / PAGE_TABLE_SIZE;
    uint32_t index_last_page = (endAddress % PAGE_TABLE_SIZE) / PAGE_TABLE_SIZE;

    for(uint32_t i=index_directory_first_table; i<=index_directory_last_table; ++i)
    {
        //Generate tables
        uint32_t* page_table = allocateNext();
        
        //Fill table
        for(unsigned int j=((i==index_directory_first_table)?index_first_page:0); j<=((i==index_directory_last_table)?index_last_page:1023); ++i)
        {
            //i * 0x1000 is identity paging, writing the same address as the area the page refers to
            page_table[i] = (i * PAGE_TABLE_SIZE) | (j * PAGE_SIZE) | flags; //Supervisor, read/write, present
            //Add page_table to directory
            page_directory[i] = ((uint32_t)&page_table) | 3;
        }
        
    }
}

void addPageTableToDirectory(uint32_t* page_table)
{
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