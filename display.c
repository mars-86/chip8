#include "display.h"
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#define ROWS 32
#define COLS 64
#define BIT_MASK 0x80

void draw_sprite(SPRITE *sprite);
static unsigned char display[ROWS][COLS];
static unsigned char display_arr[ROWS * COLS + ROWS];

void init_display(void)
{
    int i, cr;
    for (i = 0; i < ROWS; ++i)
        display_arr[ROWS]
    clear_display();
}

void clear_display(void)
{
    int i;
    for (i = 0; i < ROWS; ++i)
        memset(display, ' ', COLS);
}

void draw_sprites(SPRITE *sprites)
{
    SPRITE *sprite = sprites;
    while (sprite != NULL) {
        draw_sprite(sprite);
        sprite = sprite->next;
    }
}

void print(void)
{
    int i, j;
    for (i = 0; i < ROWS; ++i) {
        write(STDOUT_FILENO, display[i], COLS);
        putc('\n', stdout);
    }
}

void draw_sprite(SPRITE *sprite)
{
    int i, j;
    unsigned char spr;
    for (i = sprite->y; *(sprite->pixels) != '\0'; ++i)
        for (j = sprite->x, spr = *(sprite->pixels)++; spr; ++j, spr <<= 1)
            display[i][j] = spr & BIT_MASK ? '*' : ' ';
}
