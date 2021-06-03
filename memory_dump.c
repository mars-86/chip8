#include <stdio.h>
#include "memory.h"
#include "memory_dump.h"
#define LINE 8

extern unsigned char *mem_ptr;

void mem_dump(void)
{
    int i, j, line;
    for(i = 0; i < MEMORY_LENGTH; i += 8) {
        printf("%.4X ", i), line = i + LINE;
        for(j = i; j < line; ++j)
            printf("%.2X ", *(mem_ptr + j));
        for(j = i; j < line; ++j)
            printf("%c", *(mem_ptr + j) & 0x20 ? *(mem_ptr + j) : '.');
        putchar('\n');
    }
}

void mem_dump_partial(unsigned short from_addr, size_t len)
{
    int i, j, line;
    while(from_addr % 8) --from_addr;
    for(i = from_addr; i < from_addr + len; i += 8) {
        printf("%.4X ", i), line = i + LINE;
        for(j = i; j < line; ++j)
            printf("%.2X ", *(mem_ptr + j));
        for(j = i; j < line; ++j)
            printf("%c", *(mem_ptr + j) & 0x20 ? *(mem_ptr + j) : '.');
        putchar('\n');
    }
}
