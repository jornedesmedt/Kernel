/* Surely you will remove the processor conditionals and this comment
appropriately depending on whether or not you use C++. */
#if !defined(__cplusplus)
#include <stdbool.h> /* C doesn't have booleans by default. */
#endif
#include <stddef.h>
#include <stdint.h>
#include <kernel/vga.h>
#include <kernel/terminal.h>
#include <kernel/int_to_hex.h>
//#include "test/testclass.h"
//#include "mmu/mm_detection_real.h"
#include <kernel/multiboot.h>
#include <kernel/mm_explore.h>
#include <kernel/mm.h>
#include <kernel/system.h>
#include <string.h>
#include <stdio.h>

using namespace terminal;

/* Check if the compiler thinks we are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

extern uint32_t KERNEL_START;
extern uint32_t KERNEL_END;
extern uint32_t stack_top;
extern uint32_t* BootPageDirectory;


#if defined(__cplusplus)
extern "C" /* Use C linkage for kernel_main. */
#endif

void kernel_main(multiboot_info* mbt, unsigned int magic)
{
    setup_gdt();
    /* Initialize terminal interface */
    //Terminal terminal;
    terminal::initialize();
    terminal::println("Terminal initialized");

    char mem_lower[11];
    int_to_hex((uint32_t)mbt->mem_lower, mem_lower);
    char mem_upper[11];
    int_to_hex((uint32_t)mbt->mem_upper, mem_upper); 
    printf("mem_lower: %s\nmem_upper: %s\n", mem_lower, mem_upper);

    char k_end[11];
    int_to_hex((uint32_t)&KERNEL_END, k_end);
    terminal::println(k_end);

    /*char term_ptr[11];
    int_to_hex((uint32_t)&terminal, term_ptr);
    terminal::println(term_ptr);*/

    char string[32] = "hello, world";
    terminal::println(string);
    size_t count1 = strlen(string);
    char c1[11];
    int_to_hex((uint32_t)count1, c1);
    terminal::println(c1);
     size_t count2 = strlen(string, 5);
    char c2[11];
    int_to_hex((uint32_t)count2, c2);
    terminal::println(c2);
    
    
    //init_mm(mbt->mmap_addr, mbt->mmap_length);
    /*terminal.println("Memory initialized");
    char mm_count[11];
    int_to_hex(MEMORY_MAP_COUNT, mm_count);
    terminal.print(mm_count);
    terminal.println(" memory blocks mapped...");
    char mm_total[11];
    int_to_hex(TOTAL_MEMORY, mm_total);
    terminal.print("Total memory :  ");
    terminal.print(mm_total);
    terminal.println(" bytes");
    char mm_usable[11];
    int_to_hex(USABLE_MEMORY, mm_usable);
    terminal.print("Usable memory : ");
    terminal.print(mm_usable);
    terminal.println(" bytes");
    char kernel_size[11];
    int_to_hex((uint32_t) &KERNEL_END - (uint32_t) &KERNEL_START, kernel_size);
    terminal.print("Used by kernel : ");
    terminal.print(kernel_size);
    terminal.println(" bytes");*/

    

        //terminal.println("Clearing memory");
        //clear_memory(&terminal);

    /*char mmap_addr[11];
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
            
    }
    while((uint32_t)&mmap[i] < (uint32_t) mbt->mmap_addr + mbt->mmap_length);
    
    terminal.print("Printeddd ");
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
    terminal.println(t6);*/

    //memdump(&terminal, (uint32_t)0x108000);
}

/*struct interrupt_frame
{
    uint32_t error_code;
    uint32_t eip;
    uint32_t cs; //Code segment register
    uint32_t eflags; //eflags register, contains processor state
};

extern "C" __attribute__ ((interrupt)) void interrupt_handler(struct interrupt_frame* frame)
{
    
}*/