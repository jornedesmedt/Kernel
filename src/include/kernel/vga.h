#ifndef __VGA_H_INCLUDED__
#define __VGA_H_INCLUDED__

#include <stdint.h>
#include <stddef.h>

namespace vga
{
   static const size_t VGA_WIDTH = 80;
   static const size_t VGA_HEIGHT = 25;

   //When used as background colors, 0x8 to 0xf are the same as 0x0 to 0x7, but the text will blink
    enum vga_color 
    {
        VGA_COLOR_BLACK = 0x0,
        VGA_COLOR_BLUE = 0x1,
        VGA_COLOR_GREEN = 0x2,
        VGA_COLOR_CYAN = 0x3,
        VGA_COLOR_RED = 0x4,
        VGA_COLOR_MAGENTA = 0x5,
        VGA_COLOR_BROWN = 0x6,
        VGA_COLOR_LIGHT_GREY = 0x7,
        VGA_COLOR_DARK_GREY = 0x8,
        VGA_COLOR_LIGHT_BLUE = 0x9,
        VGA_COLOR_LIGHT_GREEN = 0xa,
        VGA_COLOR_LIGHT_CYAN = 0xb,
        VGA_COLOR_LIGHT_RED = 0xc,
        VGA_COLOR_LIGHT_MAGENTA = 0xd,
        VGA_COLOR_LIGHT_BROWN = 0xe,
        VGA_COLOR_WHITE = 0xf,
    };

    class Vga
    {
    private:
        static uint16_t* buffer;
    public:
        static void putEntryAt(char c, uint8_t color, size_t x, size_t y);
        static void putEntryAt(uint16_t entry, size_t x, size_t y);
        static void putEntryAt(uint16_t entry, const size_t index);
        static void clear(uint8_t color);
        static uint16_t getEntryAt(size_t x, size_t y);
        static uint16_t getEntryAt(const size_t index);
        //Color operations
        static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg)
        {
            return fg | bg << 4;
        }

        /*static inline uint8_t set_blink(uint8_t color)
        {
            return color |= 1 << 7;
        }

        static inline uint8_t unset_blink(uint8_t color)
        {
            return color &= ~(1 << 7);
        }

        static inline uint8_t toggle_blink(uint8_t color)
        {
            return color ^= 1 << 7;
        }

        static inline bool get_blink(uint8_t color)
        {
            return (color >> 7) & 1;
        }
        
        static inline uint8_t set_fg_bright(uint8_t color)
        {
            return color | (1 << 3);
        }

        static inline uint8_t unset_fg_bright(uint8_t color)
        {
            return color & ~(1 << 3);
        }

        static inline uint8_t toggle_fg_bright(uint8_t color)
        {
            return color ^ (1 << 3);
        }

        static inline bool get_fg_bright(uint8_t color)
        {
            return (color >> 3) & 1;
        }*/
        
        //Entry operations
        static inline uint16_t vga_entry(unsigned char uc, uint8_t color)
        {
            return (uint16_t) uc | (uint16_t) color << 8;
        }

        static inline void copyFromTo(const size_t src, const size_t dest)
        {
            buffer[dest] = buffer[src];
        }
    };
}

#endif