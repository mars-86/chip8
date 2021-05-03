#include <stdio.h>
#include <stdlib.h>
#include "memory.h"
#include "memory_dump.h"
#include "../utils/file_manip.h"
#include "registers.h"
#include "register_dump.h"
#include "sprite.h"
#include "display.h"

int main(int argc, char *argv[])
{
    init_registers();
    FILE *f;
    if (open_file(&f, "../Animal Race [Brian Astle].ch8", "rb")) {
        perror("file");
        return 1;
    }
    load_file_to_mem(&f, CHIP8_PROGRAM_START);
    set_PC(CHIP8_PROGRAM_START);
    fclose(f);
    free_registers_resources();
    draw_sprite(hex_digits[15]);
    return 0;
}
