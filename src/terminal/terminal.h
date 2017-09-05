#ifndef __TERMINAL_H_INCLUDED__
#define __TERMINAL_H_INCLUDED__

#include <stddef.h>
#include <stdint.h>
#include "../vga/vga.h"
#include "../misc/string.h"

namespace terminal
{
    class Terminal
    {
        //TODO: make statics non static once memory allocation is implemented
    private:
        static size_t row;
        static size_t column;
        static uint8_t color;
    public:
        static void initialize(void);
        static void setColor(uint8_t color);
        
        static void putChar(char c);
        static void putChar(char c, uint8_t color);
        static void write(const char* data, size_t size);
        static void write(const char* data, size_t size, uint8_t color);
        static void print(const char* data);
        static void println(const char* data);
        static void print(const char* data, uint8_t color);
        static void println(const char* data, uint8_t color);
        static void printError(const char* data);
        static void scrollUp();
        static inline void newline()
        {
             if (++row == vga::VGA_HEIGHT)
             {
                 scrollUp();
             }
             column = 0;
        }
    };
}
#endif