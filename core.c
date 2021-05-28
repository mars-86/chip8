#include "core.h"
#include "memory.h"
#include "memory_dump.h"
#include "interpreter.h"
#include "../utils/file_manip.h"
#include "registers.h"
#include "register_dump.h"
#include "display.h"
#include "keyboard.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <wchar.h>

int init_device(void)
{
    init_registers();
    init_display(NULL);
    init_keyboard();
    return 0;
}

int load_rom(const char *path)
{
    FILE *f;
    if (open_file(&f, path, "rb")) {
        perror("file");
        return 1;
    }
    load_file_to_mem(&f, CHIP8_PROGRAM_START);
    set_PC(CHIP8_PROGRAM_START);
    fclose(f);
    return 0;
}

void load_instruction(void)
{
    unsigned char opcode[2];
    read_from_mem(opcode, get_PC(), 2);
    printf("%.2X%.2X", opcode[0], opcode[1]);
    // getchar();
    interpret(opcode);
    increment_PC(1);
}

int main_loop(void)
{
    unsigned char key = ' ';
    while(key != 'q') {
        key = ' ';
        // clear_display();
        load_instruction();
        get_key_pressed_non_block(&key);
        print();
        // reg_dump();
        Sleep(33);
    }
    return 0;
    /*
    int i;
    for (i = 0; i < 500; ++i) {
        unsigned char key = ' ';
        clear_display();
        SPRITE sprite = { i + 20, 10, hex_digits[15], NULL };
        SPRITE sprite2 = { i + 12, 15, hex_digits[7], NULL };
        SPRITE sprite3 = { i + 2, 3, hex_digits[3], NULL };
        draw_sprites(&sprite);
        draw_sprites(&sprite2);
        draw_sprites(&sprite3);
        get_key_pressed_non_block(&key);
        print();
        printf("%c", key);
        Sleep(33);
    } */
}

void release_resources(void)
{
    free_registers_resources();
}
