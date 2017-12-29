#include "int_to_hex.h"

void int_to_hex(uint32_t input, char* hex)
{
    char hexRef[16] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
    hex[0] = '0';
    hex[1] = 'x';
    for(int i=0; i<8; ++i)
    {
        uint32_t index = (input >> (i * 4)) & 0xf;
        hex[9-i] = hexRef[index];
    }
    hex[10] = 0x00;
}

void int_to_hex(uint64_t input, char* hex)
{
    char hexRef[16] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
    hex[0] = '0';
    hex[1] = 'x';
    for(int i=0; i<16; ++i)
    {
        uint32_t index = (input >> (i * 4)) & 0xf;
        hex[17-i] = hexRef[index];
    }
    hex[18] = 0x00;
}

void int_to_memdump(uint64_t input, char* hex)
{
    char hexRef[16] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

    int j=47;
    for(int i=0; i<32; i+=2)
    {
        uint32_t index = (input >> (i * 4)) & 0xf;
        uint32_t index2 = (input >> (i+1 * 4)) & 0xf;
        hex[j] = hexRef[index];
        hex[j-1] = hexRef[index2];
        hex[j-2] = ' ';
        j-=3;
    }
    hex[48] = 0x00;
}