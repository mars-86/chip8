#ifndef _CHIP8_MEMORY_INCLUDED_H_
#define _CHIP8_MEMORY_INCLUDED_H_

#include <stdio.h>
#define MEMORY_LENGTH 0xFFF
#define CHIP8_PROGRAM_START 0x200
#define ETI_PROGRAM_START 0x600

void write_byte_to_mem(unsigned char data, unsigned short address);
size_t write_block_to_mem(void *block, unsigned short from_address, size_t size);
size_t read_from_mem(unsigned char *buffer, unsigned short from_address, size_t block_size);
void load_file_to_mem(FILE **f, unsigned short from_address);

#endif // _CHIP8_MEMORY_INCLUDED_H_
