#include "display.h"
#include <stdio.h>
#include <string.h>
#define ROWS 32
#define COLS 64
#define BIT_MASK 0x80

static unsigned char display[ROWS][COLS];

void init_display(void)
{
    int i;
    for (i = 0; i < ROWS; ++i)
        memset(display, ' ', COLS);
}

void draw_sprite(SPRITE *sprite)
{
    int i, j;
    unsigned char spr;
    for (i = sprite->y; *(sprite->pixels) != '\0'; ++i)
        for (j = sprite->x, spr = *(sprite->pixels)++; spr; ++j, spr <<= 1)
            display[i][j] = spr & BIT_MASK ? '*' : ' ';
}

void print(void)
{
    int i, j;
    for (i = 0; i < ROWS; ++i) {
        for (j = 0; j < COLS; ++j)
            putc(display[i][j], stdout);
        putc('\n', stdout);
    }
}
