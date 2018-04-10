#ifndef __TERMINAL_H_INCLUDED__
#define __TERMINAL_H_INCLUDED__

#include <stddef.h>
#include <stdint.h>
#include <kernel/vga.h>
#include <string.h>

namespace terminal
{
    //class Terminal
    //{
        
    //private:
        static size_t row;
        static size_t column;
        static uint8_t color;
    //public:
        void initialize(void);
        void setColor(uint8_t color);
        
        void putChar(char c);
        void putChar(char c, uint8_t color);
        void write(const char* data, size_t size);
        void write(const char* data, size_t size, uint8_t color);
        void print(const char* data);
        void println(const char* data);
        void print(const char* data, uint8_t color);
        void println(const char* data, uint8_t color);
        void printError(const char* data);
        void scrollUp();
        void setPos(size_t row, size_t col);
        inline void newline()
        {
             if (++row == vga::VGA_HEIGHT)
             {
                 scrollUp();
             }
             column = 0;
        }
    //};
}
#endif