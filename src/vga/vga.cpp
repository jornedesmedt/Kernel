#include <kernel/vga.h>

namespace vga
{
    uint16_t* Vga::buffer = (uint16_t*) 0xC00B8000;

    void Vga::putEntryAt(char c, uint8_t color, size_t x, size_t y)
    {
        const size_t index = y * VGA_WIDTH + x;
        Vga::buffer[index] = vga_entry(c, color);
    }

    void Vga::putEntryAt(uint16_t entry, size_t x, size_t y)
    {
        const size_t index = y * VGA_WIDTH + x;
        buffer[index] = entry;
    }

    void Vga::putEntryAt(uint16_t entry, const size_t index)
    {
        buffer[index] = entry;
    }
    
    void Vga::clear(uint8_t color)
    {
        for (size_t y = 0; y < VGA_HEIGHT; y++) 
        {
            for (size_t x = 0; x < VGA_WIDTH; x++) 
            {
                const size_t index = y * VGA_WIDTH + x;
                buffer[index] = vga_entry(' ', color);
            }
        }
    }

    uint16_t Vga::getEntryAt(size_t x, size_t y)
    {
        return buffer[y * VGA_WIDTH + x];
    }

    uint16_t Vga::getEntryAt(const size_t index)
    {
        return buffer[index];
    }
}