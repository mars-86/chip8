#include "memory.h"
#define LINE 8

static unsigned char memory[MEMORY_LENGTH];
unsigned char *mem_ptr = &memory[0], *mem_curr_addr = &memory[0];

void write_byte_to_mem(unsigned char data, unsigned short address)
{
    *(mem_ptr + address) = data;
}

size_t write_block_to_mem(void *block, unsigned short from_address, size_t size)
{
    int bytes_write;
    unsigned char *block_ptr = block;
    mem_curr_addr = &memory[from_address];
    for (bytes_write = 0; bytes_write < size; ++bytes_write)
        *mem_curr_addr++ = *block_ptr++;
    return bytes_write;
}

size_t read_from_mem(unsigned char *buffer, unsigned short from_address, size_t block_size)
{
    int bytes_read;
    unsigned char *buffer_ptr = buffer;
    mem_curr_addr = &memory[from_address];
    for (bytes_read = 0; bytes_read < block_size; ++bytes_read)
        *buffer_ptr++ = *mem_curr_addr++;
    return bytes_read;
}

void load_file_to_mem(FILE **f, unsigned short from_address)
{
    int c;
    mem_curr_addr = &memory[from_address];
    while ((c = getc(*f)) != EOF)
        *mem_curr_addr++ = (unsigned char)c;
}
