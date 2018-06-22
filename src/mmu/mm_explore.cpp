#include <kernel/mm_explore.h>
#include <stdio.h>

void memdump_line(uint8_t* input, char* hex)
{
char hexRef[16] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

for(int i=0; i<16; ++i)
{
    uint32_t index = input[i] & 0xf;
    uint32_t index2 = input[i] >> 4;

    hex[i*3]  = ' ';
    hex[i*3+2] = hexRef[index];
    hex[i*3+1] = hexRef[index2];
}
hex[48] = 0x00;
}

void memdump(/*terminal::Terminal *terminal,*/ uint32_t address)
{
    uint64_t* memory = (uint64_t*)address;
    for(uint32_t i=0;i<24;++i)
    {
        char addr[11];
        int_to_hex((uint32_t)&memory[i*2], addr);
        char hexOutput[49];
        char* str = (char*) &memory[i*2];
        char out[18];
        out[0] = ' ';
        out[17] = 0x00;

        memdump_line((uint8_t*)&memory[i*2], hexOutput);


        for(int j=0; j<16; ++j)
        {
            if(!(str[j] == '\n' || str[j] == 0x00))
            {
                out[j+1] = str[j];
            }
            else
            {
                out[j+1] = '.';
            }
        }

        terminal::print(addr);
        terminal::print(hexOutput);
        terminal::println(out);
    }
}

//Print an memory map entry to the screen.
//Terminal must be a pointer, because otherwise the position won't be updated and the same line will be overwritten on the next print.
void printMmap(multiboot_memory_map_t mmap/*, terminal::Terminal *terminal*/)
{
    char address[19];
    char length[19];
    char type[11];

    const char * typeString[] = {"Available (1)", "Reserved (2)", "ACPI reclaimable (3)", "ACPI NVS (4)", "BADRAM (5)"};

    int_to_hex((uint64_t)mmap.addr, address);
    int_to_hex((uint64_t)mmap.len, length);
    int_to_hex((uint32_t)mmap.type, type);

    printf("%s | %s | %s\n", address, length, typeString[mmap.type-1]);
    /*terminal::print(address);
    terminal::print(" | ");
    terminal::print(length);
    terminal::print(" | ");
    terminal::print(type);
    terminal::newline();*/
}