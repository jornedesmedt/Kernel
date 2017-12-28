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

    //Print an memory map entry to the screen.
    //Terminal must be a pointer, because otherwise the position won't be updated and the same line will be overwritten on the next print.
   void printMmap(multiboot_memory_map_t mmap, Terminal *terminal)
   {
        char address[19];
        char length[19];
        char type[11];

        int_to_hex((uint64_t)mmap.addr, address);
        int_to_hex((uint64_t)mmap.len, length);
        int_to_hex((uint32_t)mmap.type, type);

        terminal->print(address);
        terminal->print(" | ");
        terminal->print(length);
        terminal->print(" | ");
        terminal->print(type);
        terminal->newline();
   }
    
   #if defined(__cplusplus)
   extern "C" /* Use C linkage for kernel_main. */
   #endif

   void kernel_main(multiboot_info* mbt, unsigned int magic)
   {
       /* Initialize terminal interface */
       Terminal terminal;
       terminal.initialize();

       char mmap_addr[11];
       char mmap_length[11];
       int_to_hex((uint32_t)mbt->mmap_addr, mmap_addr);
       int_to_hex((uint32_t)mbt->mmap_length, mmap_length);
       terminal.print("MMAP Address : ");
       terminal.println(mmap_addr);
       terminal.print("MMAP Length  : ");
       terminal.println(mmap_length);
       
       terminal.println("Base address       | Length             | Type");
       multiboot_memory_map_t* mmap = (multiboot_memory_map_t*)mbt->mmap_addr;
       //printMmap(mmap[0], terminal);
       bool ordered = true;
       uint32_t i=0;
       uint64_t total_memory = 0;
       uint32_t addr=0;
       
       do
       {           
            printMmap(mmap[i], &terminal);
            if(i>0 && mmap[i].addr < mmap[i-1].addr)
            {
                ordered = false;
            }
            total_memory += mmap[i].len;
            ++i;
            uint32_t size = mmap[i].size /*+ sizeof(mmap[i].size)*/;
            addr += size;
        }
        while(addr < mbt->mmap_length && mmap[i].size > 0);
        
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

        uint32_t test = 0x78 + 0x18;
        char t[11];
        int_to_hex(test, t);
        terminal.println(t);
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