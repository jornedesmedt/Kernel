/* Surely you will remove the processor conditionals and this comment
   appropriately depending on whether or not you use C++. */
   #if !defined(__cplusplus)
   #include <stdbool.h> /* C doesn't have booleans by default. */
   #endif
   #include <stddef.h>
   #include <stdint.h>
   #include "vga/vga.h"
   #include "terminal/terminal.h"

   using namespace terminal;
    
   /* Check if the compiler thinks we are targeting the wrong operating system. */
   #if defined(__linux__)
   #error "You are not using a cross-compiler, you will most certainly run into trouble"
   #endif
    
   /* Hardware text mode color constants. */
   
    
   /*static inline uint8_t vga_entry_color(enum Vga::vga_color fg, enum Vga::vga_color bg) {
       return fg | bg << 4;
   }
    
   static inline uint16_t vga_entry(unsigned char uc, uint8_t color) {
       return (uint16_t) uc | (uint16_t) color << 8;
   }*/
    
   
    
   /*size_t terminal_row;
   size_t terminal_column;
   uint8_t terminal_color;
   uint16_t* terminal_buffer;
    
   void terminal_initialize(void) {
       terminal_row = 0;
       terminal_column = 0;
       terminal_color = Vga::vga_entry_color(Vga::VGA_COLOR_WHITE, Vga::VGA_COLOR_BLACK);
       terminal_buffer = (uint16_t*) 0xB8000;
       for (size_t y = 0; y < VGA_HEIGHT; y++) {
           for (size_t x = 0; x < VGA_WIDTH; x++) {
               const size_t index = y * VGA_WIDTH + x;
               terminal_buffer[index] = Vga::vga_entry(' ', terminal_color);
           }
       }
   }*/
    
   /*void terminal_setcolor(uint8_t color) {
       terminal_color = color;
   }
    
   void terminal_putentryat(char c, uint8_t color, size_t x, size_t y)
   {
       const size_t index = y * VGA_WIDTH + x;
       terminal_buffer[index] = Vga::vga_entry(c, color);
   }
    
   void terminal_putchar(char c) {
       terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
       if (++terminal_column == VGA_WIDTH) {
           terminal_column = 0;
           if (++terminal_row == VGA_HEIGHT)
               terminal_row = 0;
       }
   }

   inline void terminal_newline()
   {
        if (++terminal_row == VGA_HEIGHT)
        {
            terminal_row = 0;
        }
        terminal_column = 0;
   }
    
   void terminal_write(const char* data, size_t size) {
       for (size_t i = 0; i < size; i++)
       {
           switch(data[i])
           {
                case '\n':
                    terminal_newline();
                    break;
                default:
                    terminal_putchar(data[i]);
                    break;
           }
       }
   }
    
   void terminal_writestring(const char* data) {
       terminal_write(data, strlen(data));
   }*/
    
   #if defined(__cplusplus)
   extern "C" /* Use C linkage for kernel_main. */
   #endif
   void kernel_main(void) {
       /* Initialize terminal interface */
       Terminal::initialize();
    
       /* Newline support is left as an exercise. */
       Terminal::print("Hello, kernel World!\nLook! A new line!\nFrom the terminal class!");
   }