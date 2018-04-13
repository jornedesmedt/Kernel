#include <kernel/system.h>

#define PAGE_DIRECTORY_BASE_4KB_FLAGS 0x03 //Supervisor, write, present
#define PAGE_DIRECTORY_BASE_4MB_FLAGS 0x83 //4MB, Supervisor, write, present

typedef struct
{
    uint8_t flags; //0, Dirty, Accessed, Cache Disable, Write through, User/Supervisor, Read/Write, Present
    uint8_t page_table_address_low; //4 bits of page table address, followed by 3 available and 1 ignored bits
    uint16_t page_table_address_high;
}__attribute__((packed)) page_directory_entry_t;

typedef struct
{
    uint8_t flags; //Page size (0 for 4kb), 0, Accessed, Cache Disable, Write through, User/Supervisor, Read/Write, Present
    uint8_t page_address_low; //4 bits of page table address, followed by 3 available and 1 ignored bits
    uint16_t page_address_high;
}__attribute__((packed)) page_table_entry_t;

typedef struct
{
    page_directory_entry_t entries[1024];
} __attribute__((packed)) page_directory_t;

typedef struct
{
    page_table_entry_t entries[1024];
} __attribute__((packed)) page_table_t;


//misc is bits 9-11 or bits 1-3 of page_table_address_low
void encode_page_directory_entry(idt_entry_t* target, uint32_t page_table_address, uint8_t flags, uint8_t misc)
{
    target->flags = flags;
    target->page_table_address_low = (page_table_address & 0XF0) | ((misc << 1) & 0x0F) 
    target->page_table_address_high = (page_table_address >> 16) & 0xFF;
}