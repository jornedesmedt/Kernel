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

   extern uint32_t KERNEL_START;
   extern uint32_t KERNEL_END;
   extern uint32_t stack_top;

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

   void memdump(Terminal *terminal, uint32_t address)
   {
        uint64_t* memory = (uint64_t*)address;
        for(uint32_t i=0;i<24;++i)
        {
            char addr[11];
            int_to_hex((uint32_t)&memory[i*2], addr);
            char hexOutput[49];
            char* str = (char*) &memory[i*2];
            char out[18];
            out[0] = ' ';
            out[17] = 0x00;

            int_to_memdump((uint8_t*)&memory[i*2], hexOutput);


            for(int j=0; j<16; ++j)
            {
                if(!(str[j] == '\n' || str[j] == 0x00))
                {
                    out[j+1] = str[j];
                }
                else
                {
                    out[j+1] = '.';
                }
            }

            terminal->print(addr);
            terminal->print(hexOutput);
            terminal->println(out);

            //char o[19];
            //int_to_hex(memory[i*2], o);
            //terminal->println(o);
        }
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

        //char o[19];
        //int_to_hex((uint64_t)0x0123456789abcdef, o);
        //terminal.println(o);

        //char o2[5] = {0x73, 0x74, 0x75, 0x76, 0x00};
        //terminal.println(o2);

        memdump(&terminal, (uint32_t)&KERNEL_END);

        /*uint32_t* memory = (uint32_t*) ((uint32_t)&KERNEL_END + 0x94);
        uint32_t m=0;
        while(m<20)
        {
            uint32_t curr_addr = (uint32_t)&memory[m];
            char addr[11];
            int_to_hex(curr_addr, addr);
            ((Terminal*) &terminal)->print(addr);
            ((Terminal*) &terminal)->print(" | ");
            char bytes[11];
            int_to_hex(memory[m], bytes);
            ((Terminal*) &terminal)->println(bytes);
            ++m;
        }
        terminal.println("Yay");
        while(memory[m]==0)
        {
            uint32_t curr_addr = (uint32_t)&KERNEL_END + m*4;
            char addr[11];
            int_to_hex(curr_addr, addr);
            ((Terminal*) &terminal)->print(addr);
            ((Terminal*) &terminal)->print(" | ");
            char bytes[11];
            int_to_hex(memory[m], bytes);
            ((Terminal*) &terminal)->println(bytes);
            ++m;
        }

        while(memory[m]!=0)
        {
            uint32_t curr_addr = (uint32_t)&KERNEL_END + m*4;
            char addr[11];
            int_to_hex(curr_addr, addr);
            ((Terminal*) &terminal)->print(addr);
            ((Terminal*) &terminal)->print(" | ");
            char bytes[11];
            int_to_hex(memory[m], bytes);
            ((Terminal*) &terminal)->println(bytes);
            ++m;
        }

        char M[11];
        int_to_hex(m, M);
        terminal.println(M);*/
   }