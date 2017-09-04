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
    
   #if defined(__cplusplus)
   extern "C" /* Use C linkage for kernel_main. */
   #endif
   void kernel_main(void)
   {
       /* Initialize terminal interface */
       Terminal::initialize();
    
       /* Newline support is left as an exercise. */
       Terminal::print("Hello, kernel World!\nLook! A new line!\nFrom the terminal class!\n");
       Terminal::println("println");
       for(size_t i=0; i<vga::VGA_HEIGHT; ++i)
       {
            Terminal::println("Hello?");
       }
       Terminal::println("Cheese!");
       Terminal::println("For everyone!");
       Terminal::printError("No, wait... Cheese for noone...");
       Terminal::newline();
       for(uint8_t color = 0x00; color < 0xff; ++color)
       {
            Terminal::putChar('*', color);
       }
       Terminal::putChar('*', 0xff);
   }