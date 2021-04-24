#include <stdio.h>
#include <stdlib.h>
#include "memory.h"
#include "memory_dump.h"

int main(int argc, char *argv[])
{
    FILE *f;
    if (!(f = fopen("Brix [Andreas Gustafsson, 1990].ch8", "r"))) {
        perror("file");
        return 1;
    }
    unsigned char block[15] = {5,4,3,2,6,8,9,14,22,4,2,77,43,21,87};
    load_block_to_mem(block, 0x300, 15);
    load_file_to_mem(&f, CHIP8_PROGRAM_START);
    mem_dump();
    fclose(f);
    return 0;
}
