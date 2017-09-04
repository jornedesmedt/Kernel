#include "terminal.h"
using namespace vga;
using namespace string;

namespace terminal
{

    size_t Terminal::row = 0;
    size_t Terminal::column = 0;
    uint8_t Terminal::color = 0;
    uint16_t* Terminal::buffer = 0;
    
    void Terminal::initialize(void) 
    {
        Terminal::row = 0;
        Terminal::column = 0;
        Terminal::color = Vga::vga_entry_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
        Terminal::buffer = (uint16_t*) 0xB8000;
        for (size_t y = 0; y < VGA_HEIGHT; y++) 
        {
            for (size_t x = 0; x < VGA_WIDTH; x++) 
            {
                const size_t index = y * VGA_WIDTH + x;
                buffer[index] = Vga::vga_entry(' ', color);
            }
        }
    }

    void Terminal::setColor(uint8_t color)
    {
        Terminal::color = color;
    }
     
    void Terminal::putEntryAt(char c, uint8_t color, size_t x, size_t y)
    {
        const size_t index = y * VGA_WIDTH + x;
        Terminal::buffer[index] = Vga::vga_entry(c, color);
    }
     
    void Terminal::putChar(char c)
    {
        putEntryAt(c, color, column, row);
        if (++column == VGA_WIDTH)
        {
            column = 0;
            if (++row == VGA_HEIGHT)
            {
                row = 0;
            }
        }
    }
     
    void Terminal::write(const char* data, size_t size)
    {
        for (size_t i = 0; i < size; i++)
        {
            switch(data[i])
            {
                 case '\n':
                     newline();
                     break;
                 default:
                     putChar(data[i]);
                     break;
            }
        }
    }
     
    void Terminal::print(const char* data)
    {
        write(data, strlen(data));
    }
}