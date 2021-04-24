#include "memory.h"
#define LINE 8

static unsigned char memory[MEMORY_LENGTH];
unsigned char *mem_ptr = &memory[0], *mem_curr_addr = &memory[0];

void write_to_mem(unsigned char data, unsigned short address)
{
    *(mem_ptr + address) = data;
}

int read_from_mem(void *buffer, unsigned short address, size_t block)
{
    int bytes_read = 0;
    return bytes_read;
}

void load_file_to_mem(FILE **f, unsigned short from_address)
{
    char c;
    mem_curr_addr = &memory[from_address];
    while((c = getc(*f)) != EOF)
        *mem_curr_addr++ = c;
}

void load_block_to_mem(void *block, unsigned short from_address, size_t size)
{
    int i;
    unsigned char *block_ptr = block;
    mem_curr_addr = &memory[from_address];
    for(i = 0; i < size; ++i)
        *mem_curr_addr++ = *block_ptr++;
}
