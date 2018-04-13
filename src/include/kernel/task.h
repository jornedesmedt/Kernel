#ifdef __TASK_H__
#define __TASK_H__

#include <stdint.h>

typedef struct page
{
    unsigned int present:1;
    unsigned int read_write:1;
    unsigned int user_supervisor:1;
    unsigned int writethrough:1;
    unsigned int cache_disabled:1;
    unsigned int accessed:1;
    unsigned int dirty:1;
    unsigned int zero:1;
    unsigned int global:1;
    unsigned int available:3;
    unsigned int address:20;
}__attribute__((packed)) page_t;

typedef struct page_directory_entry
{
    unsigned int present:1;
    unsigned int read_write:1;
    unsigned int user_supervisor:1;
    unsigned int writethrough:1;
    unsigned int cache_disabled:1;
    unsigned int accessed:1;
    unsigned int zero:1;
    unsigned int page_size:1;
    unsigned int ignored:1;  //Ignored
    unsigned int available:3;
    unsigned int address:20;
}__attribute__((packed)) page_directory_entry_t;

typedef struct page_table
{
    page_t pages[1024];
} page_table_t;

typedef struct page_directory
{
    page_directory_entry_t tables[1024]
} page_directory_t;

#endif