#include "core.h"
#include "memory.h"
#include "memory_dump.h"
#include "interpreter.h"
#include "../utils/file_manip.h"
#include "registers.h"
#include "register_dump.h"
#include "display.h"
#include "keyboard.h"
#include "digit.h"
#include "instruction_dump.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <wchar.h>
// #define __DEBUG__

void init_memory(void)
{
    int i, digit_len = HEX_DIGITS_SIZE;
    unsigned short from_addr = HEX_DIGITS_START;
    for (i = 0; i < 0xF; ++i, from_addr += digit_len)
        write_block_to_mem(hex_digits[i], from_addr, digit_len);
}

int init_device(void)
{
    init_registers();
    init_memory();
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

void fetch_instruction(void)
{
    unsigned char opcode[2];
    read_from_mem(opcode, get_PC(), 2);
    interpret(opcode);
    increment_PC(1);
}

int main_loop(void)
{
    unsigned char key = ' ';
    while(key != 'q') {
        key = ' ';
        cursor_to_start();
        // clear_display();
        fetch_instruction();
        get_key_pressed_non_block(&key);
        print();
// #ifdef __DEBUG__
        reg_dump();
        // mem_dump_partial(get_PC(), 32);
        instruction_dump();
        getchar();
// #endif // __DEBUG__
        Sleep(33);
    }

    /*
    int i;
    unsigned char col;
    for (i = 0; i < 500; ++i) {
        unsigned char key = ' ';
        clear_display();
        SPRITE sprite = { i + 20, 10, hex_digits[15], NULL };
        SPRITE sprite2 = { i + 12, 15, hex_digits[7], NULL };
        SPRITE sprite3 = { i + 2, 3, hex_digits[3], NULL };
        draw_sprites(&sprite, &col);
        draw_sprites(&sprite2, &col);
        draw_sprites(&sprite3, &col);
        get_key_pressed_non_block(&key);
        print();
        // printf("%c", key);
        Sleep(33);
    }
    */
    return 0;
}

void release_resources(void)
{
    free_registers_resources();
}
