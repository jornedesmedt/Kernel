/* Surely you will remove the processor conditionals and this comment
   appropriately depending on whether or not you use C++. */
   #if !defined(__cplusplus)
   #include <stdbool.h> /* C doesn't have booleans by default. */
   #endif
   #include <stddef.h>
   #include <stdint.h>
   #include "vga/vga.h"
   #include "terminal/terminal.h"
   #include "misc/int_to_hex.h"
   #include "test/testclass.h"
   //#include "mmu/mm_detection_real.h"
   #include "mmu/multiboot.h"

   using namespace terminal;
    
   /* Check if the compiler thinks we are targeting the wrong operating system. */
   #if defined(__linux__)
   #error "You are not using a cross-compiler, you will most certainly run into trouble"
   #endif

   void printMmap(multiboot_memory_map_t mmap, Terminal terminal)
   {
        char address[19];
        char length[19];
        char type[11];

        int_to_hex((uint64_t)mmap.addr, address);
        int_to_hex((uint64_t)mmap.len, length);
        int_to_hex((uint32_t)mmap.type, type);

        terminal.print(address);
        terminal.print(" | ");
        terminal.print(length);
        terminal.print(" | ");
        terminal.print(type);
        terminal.newline();
   }
    
   #if defined(__cplusplus)
   extern "C" /* Use C linkage for kernel_main. */
   #endif

   void kernel_main(multiboot_info* mbt, unsigned int magic)
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
       uint32_t input = 0xfedcba98;
       char h[11];
       int_to_hex(input, h);
       terminal.println(h);

       uint64_t input2 = 0xfedcba9876543210;
       char h2[19];
       int_to_hex(input2, h2);
       terminal.println(h2);
       terminal.println("Testing 1");
       multiboot_memory_map_t mmaptest;
       terminal.println("Testing 2");
       mmaptest.addr = 0xaaacba9876543210;
       mmaptest.len = 0xbbbcba9876543210;
       mmaptest.type = 0xccccba98;
       terminal.println("Test Memory Map...");
       printMmap(mmaptest, terminal);
       terminal.println("And now for the real Memory Map...");
       terminal.println("Base address       | Length             | Type");
       multiboot_memory_map_t* mmap = (multiboot_memory_map_t*)mbt->mmap_addr;
       //printMmap(mmap[0], terminal);
       bool ordered = true;
       uint32_t i=0;
       uint64_t total_memory = 0;
       for(uint32_t addr=mbt->mmap_addr; addr < mbt->mmap_addr + mbt->mmap_length; addr+= mmap[i].size + sizeof(mmap[i].size))
       {
           //if(mmap[i].len > 0)
           //{
                printMmap(mmap[i], terminal);
                if(i>0 && mmap[i].addr < mmap[i-1].addr)
                {
                    ordered = false;
                }
                total_memory += mmap[i].len;
            //}
            ++i;
        }
        
        terminal.print("Printed ");
        char mmap_count[11];
        int_to_hex(i, mmap_count);
        terminal.print(mmap_count);
        terminal.println(" entries...");

        char mapped_memory[19];
        int_to_hex(total_memory, mapped_memory);
        terminal.print("Total memory mapped: ");
        terminal.println(mapped_memory);

        if(ordered)
        {
            terminal.println("Order is correct");
        }
        else
        {
            terminal.println("Order is wrong");
        }
        /*while(mmap < mbt->mmap_addr + mbt->mmap_length)
        {            
            mmap = (multiboot_memory_map_t*) ( (unsigned int)mmap + mmap->size + sizeof(mmap->size) );
        }*/

       //SMAP_entry_t* smap = (SMAP_entry_t*) 0x1000;
       //const int smap_size = 0x2000;
       
       //int entry_count = detectMemory(smap, smap_size / sizeof(SMAP_entry_t));

       /*if(entry_count == -1)
       {
           terminal.printError("ERROR: SMAP entry count is -1");
        }
        else
        {
            //process memory map
            terminal.println("Base address       | Length             | Type       | ACPI");
            for(int i=0; i< entry_count; ++i)
            {
                char address[19];
                char length[19];
                char type[11];
                char acpi[11];

                int_to_hex(smap[i].baseAddress, address);
                int_to_hex(smap[i].length, length);
                int_to_hex(smap[i].type, type);
                int_to_hex(smap[i].ACPI, acpi);

                terminal.print(address);
                terminal.print(" | ");
                terminal.print(length);
                terminal.print(" | ");
                terminal.print(type);
                terminal.print(" | ");
                terminal.print(acpi);
                terminal.newline();
            }
        }*/
   }