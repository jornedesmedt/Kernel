#include <kernel/terminal.h>
using namespace vga;

namespace terminal
{

    //static size_t row = 0;
    //static size_t column = 0;
    //static uint8_t color = 0;
    
    void initialize(void) 
    {
        terminal::row = 0;
        terminal::column = 0;
        terminal::color = Vga::vga_entry_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
        Vga::clear(terminal::color);
    }

    void setColor(uint8_t color)
    {
        terminal::color = color;
    }

    /*void putChar(char c)
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
    }*/

    void putChar(char c, uint8_t color)
    {
        if(!color)
        {
            color = terminal::color;
        }
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
     
    /*void write(const char* data, size_t size)
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
    }*/

    void write(const char* data, size_t size, uint8_t color)
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
     
    /*void print(const char* data)
    {
        write(data, strlen(data));
    }*/

    void print(const char* data, uint8_t color)
    {
        write(data, strlen(data), color);
    }

    /*void println(const char* data)
    {
        write(data, strlen(data));
        newline();
    }*/

    void println(const char* data, uint8_t color)
    {
        write(data, strlen(data), color);
        newline();
    }

    void printError(const char* data)
    {
        write(data, strlen(data), Vga::vga_entry_color(VGA_COLOR_WHITE, VGA_COLOR_RED));
        newline();
    }

    void scrollUp()
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

    void setPos(size_t row, size_t col)
    {
        terminal::row = row;
        terminal::column = col;
    }
}