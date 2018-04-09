#include "system.h"

#define IDT_TASK_GATE_32_BIT 0x5;
#define IDT_INTERRUPT_GATE_16_BIT 0x6;
#define IDT_TRAP_GATE_16_BIT 0x7;
#define IDT_INTERRUPT_GATE_32_BIT 0xE;
#define IDT_TRAP_GATE_32_BIT 0xF;

typedef struct
{
    uint16_t base_low;
    uint16_t selector;
    uint8_t zero;
    uint8_t type; //Present, DPL, Storage Segment, Gate type
    uint16_t base_high;
} __attribute__((packed)) idt_entry_t;

struct idt_entry_unencoded
{
    uint32_t base;
    uint16_t selector;
    uint8_t present;
    uint8_t DPL;
    uint8_t storage_segment;
    uint8_t gate_type;
};

typedef struct
{
    uint16_t limit;
    uint32_t base;
} __attribute__((packed)) idt_descriptor_t;

static struct
{
    idt_entry_t entries[256];
    idt_descriptor_t descriptor;
} idt;

void encode_idt_entry(idt_entry_t* target, struct idt_entry_unencoded source)
{
    target->base_low = source.base & 0xFF;
    target->base_high = (source.base >> 16) && 0xFF;
    target->selector = source.selector;
    target->zero = 0;
    target->type = ((source.present & 1) << 7) | ((source.DPL & 3) << 5) | ((source.storage_segment & 1) << 4 ) | (source.gate_type & 0xF);
}

void setup_idt()
{
    idt.descriptor.base = (uint32_t)&idt.entries[0];
    idt.descriptor.limit = sizeof idt.entries - 1;
    //memset(&idt.entries[0], sizeof idt.entries);
}