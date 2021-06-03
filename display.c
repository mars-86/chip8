#include "display.h"
#include "../utils/os/terminal.h"
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <assert.h>
#define ROWS 32
#define COLS 64
#define LINEAR_LENGTH ROWS * COLS// + COLS - 1
#define BIT_MASK 0x80
#define _DISPLAY_IS_VOID(c) ((!(c ^ 0x20)) ? 1 : 0)
#define _DISPLAY_FILL_CHAR 219

void draw_sprite(SPRITE *sprite, unsigned char *collision);
void paint_screen(void);
void line_feed(void);
static unsigned char back_display[LINEAR_LENGTH];
static unsigned char display[LINEAR_LENGTH];
static HANDLE stdout_h;

void init_display(HANDLE *handle)
{
    OS_VT_SET_SCREEN_BUFFER(ALTERNATE_SCREEN_BUFFER);
    OS_VT_CURSOR_VISIBILITY(CURSOR_VISIBILITY_HIDE);
    // OS_VT_TERMINAL_SIZE(ROWS, COLS + 1);
    stdout_h = handle;
    clear_display();
}

void clear_display(void)
{
    memset(back_display, 0, LINEAR_LENGTH * sizeof(char));
    line_feed();
    OS_VT_CURSOR_XY(1, 1);
}

void draw_sprites(SPRITE *sprites, unsigned char *collision)
{
    SPRITE *sprite = sprites;
    while (sprite != NULL) {
        draw_sprite(sprite, collision);
        sprite = sprite->next;
    }
}

void print(void)
{
    paint_screen();
    write(STDOUT_FILENO, display, LINEAR_LENGTH);
}

void draw_sprite(SPRITE *sprite, unsigned char *collision)
{
    int i, j, size = 0;
    unsigned char spr, pixel;
    *collision = 0;
    for (i = sprite->y; size < sprite->size; ++i, ++size)
        for (j = sprite->x, spr = *(sprite->pixels)++; spr; ++j, spr <<= 1) {
            pixel = (back_display[(COLS * i) + (j + 1)] ^ ((spr & BIT_MASK) >> 7));
            assert(pixel <= 1);
            if (!pixel) *collision = 1;
            back_display[(COLS * i) + (j + 1)] = pixel ? 1 : 0;
        }
}

size_t get_sprite(unsigned char *buffer, short x, short y, size_t n)
{
    int i, size;
    unsigned char byte;
    for (i = y, size = 0; size < n; ++i, ++size) {
        byte = back_display[(COLS * i) + (x + 1)];
        buffer[size] = _DISPLAY_IS_VOID(byte) ? 0 : byte;
    }
    return size;
}

void paint_screen(void)
{
    int i;
    for (i = 0; i < LINEAR_LENGTH; ++i)
        display[i] = back_display[i] == 1 ? _DISPLAY_FILL_CHAR : ' ';
    line_feed();
}

void line_feed(void)
{
    int i;
    for (i = COLS - 1; i < LINEAR_LENGTH; i += COLS)
        display[i] = '\n';
}

void cursor_to_start(void)
{
    OS_VT_CURSOR_XY(1, 1);
}
