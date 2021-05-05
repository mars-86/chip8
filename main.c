#include <stdio.h>
#include <stdlib.h>
#include "memory.h"
#include "memory_dump.h"
#include "../utils/file_manip.h"
#include "registers.h"
#include "register_dump.h"
#include "display.h"

int main(int argc, char *argv[])
{
    init_registers();
    init_display();
    FILE *f;
    if (open_file(&f, "../Animal Race [Brian Astle].ch8", "rb")) {
        perror("file");
        return 1;
    }
    load_file_to_mem(&f, CHIP8_PROGRAM_START);
    set_PC(CHIP8_PROGRAM_START);
    fclose(f);
    free_registers_resources();
    int i;
    for (i = 0; i < 20; ++i) {
        SPRITE sprite = { i + 20, 10, hex_digits[15], NULL };
        SPRITE sprite2 = { i + 12, 15, hex_digits[7], NULL };
        SPRITE sprite3 = { i + 2, 3, hex_digits[3], NULL };
        draw_sprites(&sprite);
        draw_sprites(&sprite2);
        draw_sprites(&sprite3);
        print();
        clear_display();
    }
    return 0;
}
