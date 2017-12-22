/* Surely you will remove the processor conditionals and this comment
   appropriately depending on whether or not you use C++. */
   #if !defined(__cplusplus)
   #include <stdbool.h> /* C doesn't have booleans by default. */
   #endif
   #include <stddef.h>
   #include <stdint.h>
   #include "vga/vga.h"
   #include "terminal/terminal.h"
   #include "test/testclass.h"

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
       Terminal terminal;
       terminal.initialize();
    
       /* Newline support is left as an exercise. */
       terminal.print("Hello, kernel World!\nLook! A new line!\nFrom the terminal class!\n");
       terminal.println("println");
       for(size_t i=0; i<vga::VGA_HEIGHT; ++i)
       {
            terminal.println("Hello?");
       }
       terminal.println("Cheese!");
       terminal.println("For everyone!");
       terminal.printError("No, wait... Cheese for noone...");
       terminal.newline();
       for(uint8_t color = 0x00; color < 0xff; ++color)
       {
            terminal.putChar('*', color);
       }
       terminal.putChar('*', 0xff);
       terminal.newline();
       terminal.println("More testery");
       terminal.printError("Another error");
       terminal.scrollUp();
       Test test;
       terminal.println(test.getFoo());
   }