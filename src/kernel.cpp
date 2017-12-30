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
   #include "mmu/mm_explore.h"

   using namespace terminal;
    
   /* Check if the compiler thinks we are targeting the wrong operating system. */
   #if defined(__linux__)
   #error "You are not using a cross-compiler, you will most certainly run into trouble"
   #endif

   extern uint32_t KERNEL_START;
   extern uint32_t KERNEL_END;
   extern uint32_t stack_top;

    void clear_memory(Terminal* terminal)
    {
        uint32_t i = 0;
        uint32_t* memory = (uint32_t*) ((uint32_t)&KERNEL_END);
        while((uint32_t)&memory[i] <0x7fff000)
        {            
            memory[i] = 0;
            ++i;
        }

        //terminal->println("Memory cleared 0x3fffffff...");
        /*while(i<0x7FEF0000)
        {
            uint32_t* memory = (uint32_t*) ((uint32_t)&KERNEL_END);
            memory[i] = 0;
            ++i;
        }*/

        terminal->println("Memory cleared...");
    }
    
   #if defined(__cplusplus)
   extern "C" /* Use C linkage for kernel_main. */
   #endif

    void kernel_main(multiboot_info* mbt, unsigned int magic)
    {
        /* Initialize terminal interface */
        
            Terminal terminal;
            terminal.initialize();

            terminal.println("Clearing memory");
            clear_memory(&terminal);

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

        uint32_t start_address = (uint32_t)&KERNEL_START;
        char t[11];
        int_to_hex(start_address, t);
        terminal.println(t);

        uint32_t end_address = (uint32_t)&KERNEL_END;
        char t2[11];
        int_to_hex(end_address, t2);
        terminal.println(t2);

        char t5[11];
        int_to_hex(KERNEL_END, t5);
        terminal.println(t5);

        char t6[11];
        int_to_hex((uint32_t)&stack_top, t6);
        terminal.println(t6);

        memdump(&terminal, (uint32_t)&KERNEL_END);
    }