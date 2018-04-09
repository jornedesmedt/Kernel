#include "system.h"
#define GDT_FLAG_GRANULARITY_PAGE 0x8
#define GDT_FLAG_SIZE_32_BIT 0x4
#define GDT_ACCESS_PRESENT 0x80
#define GDT_ACCESS_PRIVILEGE_RING_0 0x00 //Default
#define GDT_ACCESS_PRIVILEGE_RING_1 0x20
#define GDT_ACCESS_PRIVILEGE_RING_2 0x40
#define GDT_ACCESS_PRIVILEGE_RING_3 0x60
#define GDT_ACCESS_BASE 0x10
#define GDT_ACCESS_EXECUTABLE 0x08
#define GDT_ACCESS_DATA_DIRECTION_DOWN 0x04
#define GDT_ACCESS_CODE_CONFORM_ALLOW_LOWER_RINGS 0x04
#define GDT_ACCESS_CODE_READABLE 0x02
#define GDT_ACCESS_DATA_WRITABLE 0x02
#define GDT_ACCESS_ACCESSED 0x01 //Automatically set by the cpu, might be useful to read?

#define GDT_FLAT_NULL           0x0000000000000000
#define GDT_FLAT_CODE_KERNEL    0x0000FFFF00CF9A00
#define GDT_FLAT_DATA_KERNEL    0x0000FFFF00CF9200
#define GDT_FLAT_CODE_USER      0x0000FFFF00CFFA00
#define GDT_FLAT_DATA_USER      0x0000FFFF00CFF200


typedef struct
{
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_middle;
    uint8_t access;
    uint8_t flags_limit_middle;
    uint8_t base_high;
} __attribute__((packed)) gdt_entry_t;

struct gdt_entry_unencoded
{
    uint32_t base;
    uint32_t limit;
    uint8_t access;
    uint8_t flags;
};

typedef struct
{
    uint16_t limit;
    uint32_t base;
} __attribute__((packed)) gdt_descriptor_t;

static struct
{
    gdt_entry_t entries[5];
    gdt_descriptor_t descriptor;
} gdt;


void encodeGdtEntry(gdt_entry_t *target, struct gdt_entry_unencoded source)
{
    target->flags_limit_middle = source.flags;

    //Encode the limit
    target->limit_low = source.limit & 0xFFFF; //Limit 0:15
    target->flags_limit_middle =  ((source.limit>>16) & 0xF) | ((source.flags<<4) & 0xF0); //Limit 16:23 

    //Encode base
    target->base_low = source.base & 0xFFFF; // Base 0:15
    target->base_middle = (source.base>>16) & 0xFF; //Base 16:23
    target->base_high = (source.base>>24) & 0xFF; //Base 24:31    
    
    //Encode the type
    target->access = source.access;
}

extern "C" void gdt_flush(uint32_t);

void setup_gdt()
{
    gdt.descriptor.base = (uint32_t)&gdt.entries[0];
    gdt.descriptor.limit = sizeof gdt.entries - 1;

    encodeGdtEntry(&gdt.entries[0], {.base=0, .limit=0, .access=0, .flags=0}); //Null Segment
    encodeGdtEntry(&gdt.entries[1], {.base=0, .limit=0xffffffff, .access=0x9A, .flags=0xC}); //Kernel code
    encodeGdtEntry(&gdt.entries[2], {.base=0, .limit=0xffffffff, .access=0x92, .flags=0xC}); //Kernel data
    encodeGdtEntry(&gdt.entries[3], {.base=0, .limit=0xffffffff, .access=0xFA, .flags=0xC}); //User code
    encodeGdtEntry(&gdt.entries[4], {.base=0, .limit=0xffffffff, .access=0xF2, .flags=0xC}); //User data

    //TODO: TSS stuff

    //Flush gdt
    gdt_flush((uint32_t)&gdt.descriptor);
}