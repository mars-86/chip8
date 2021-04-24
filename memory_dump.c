#include <stdio.h>
#include "memory.h"
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
