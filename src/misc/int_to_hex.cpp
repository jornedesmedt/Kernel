#include "int_to_hex.h"

void int32_to_hex(uint32_t input, char* hex)
{
    char hexRef[16] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
    //char hex [10];
    hex[0] = '0';
    hex[1] = 'x';
    for(int i=0; i<8; ++i)
    {
        uint32_t index = (input >> (i * 4)) & 0x0000000f;
        hex[9-i] = hexRef[index];
    }
    //out = hex;
}

/*const char* int_to_hex(int64_t i)
{

}*/