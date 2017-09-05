#include "terminal.h"
using namespace vga;
using namespace string;

namespace terminal
{

    size_t Terminal::row = 0;
    size_t Terminal::column = 0;
    uint8_t Terminal::color = 0;
    
    void Terminal::initialize(void) 
    {
        Terminal::row = 0;
        Terminal::column = 0;
        Terminal::color = Vga::vga_entry_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
        Vga::clear(color);
    }

    void Terminal::setColor(uint8_t color)
    {
        Terminal::color = color;
    }

    void Terminal::putChar(char c)
    {
        Vga::putEntryAt(c, color, column, row);
        if (++column == VGA_WIDTH)
        {
            column = 0;
            if (++row == VGA_HEIGHT)
            {
                scrollUp();
            }
        }
    }

    void Terminal::putChar(char c, uint8_t color)
    {
        Vga::putEntryAt(c, color, column, row);
        if (++column == VGA_WIDTH)
        {
            column = 0;
            if (++row == VGA_HEIGHT)
            {
                scrollUp();
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

    void Terminal::write(const char* data, size_t size, uint8_t color)
    {
        for (size_t i = 0; i < size; i++)
        {
            switch(data[i])
            {
                 case '\n':
                     newline();
                     break;
                 default:
                     putChar(data[i], color);
                     break;
            }
        }
    }
     
    void Terminal::print(const char* data)
    {
        write(data, strlen(data));
    }

    void Terminal::print(const char* data, uint8_t color)
    {
        write(data, strlen(data), color);
    }

    void Terminal::println(const char* data)
    {
        write(data, strlen(data));
        newline();
    }

    void Terminal::println(const char* data, uint8_t color)
    {
        write(data, strlen(data), color);
        newline();
    }

    void Terminal::printError(const char* data)
    {
        write(data, strlen(data), Vga::vga_entry_color(VGA_COLOR_WHITE, VGA_COLOR_RED));
        newline();
    }

    void Terminal::scrollUp()
    {
        for (size_t y = 0; y < VGA_HEIGHT; y++) 
        {
            for (size_t x = 0; x < VGA_WIDTH; x++) 
            {
                const size_t index = y * VGA_WIDTH + x;
                if(y < VGA_HEIGHT -1)
                {
                    const size_t index_below = (y+1) * VGA_WIDTH + x;
                    Vga::putEntryAt(Vga::getEntryAt(index_below), index);
                }
                else
                {
                    Vga::putEntryAt(Vga::vga_entry(' ', color), index);
                }
            }
        }
        --row;
    }
}