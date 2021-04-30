#include <stdio.h>
#include <stdlib.h>
#include "memory.h"
#include "memory_dump.h"
#include "../utils/file_manip.h"
#include "registers.h"

int main(int argc, char *argv[])
{
    init_registers();
    FILE *f;
    if (open_file(&f, "../Brix [Andreas Gustafsson, 1990].ch8", "rb")) {
        perror("file");
        return 1;
    }
    load_file_to_mem(&f, CHIP8_PROGRAM_START);
    mem_dump();
    set_PC(0x200);
    fclose(f);
    return 0;
}
