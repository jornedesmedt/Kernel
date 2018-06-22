#ifndef __PAGE_FRAME_ALLOCATOR_H__
#define __PAGE_FRAME_ALLOCATOR_H__
#include <kernel/task.h>
#include <kernel/multiboot.h>

typedef struct page_node
{
    page_t* page;
    page_node_t* previous;
    page_node_t* next;
} page_node_t;

typedef struct page_frame
{
    bool usable;
    uintptr_t frame_start;
    page_node_t* first; //Store all references to the current frame in a linked list, will usually only contain one page, unless page is shared
} page_frame_t;

void create_frames(multiboot_memory_map_t *mmap);

#endif