#include "display.h"
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#define ROWS 32
#define COLS 64
#define LINEAR_LENGTH ROWS * COLS + COLS
#define BIT_MASK 0x80

void draw_sprite(SPRITE *sprite);
void line_feed(void);
static unsigned char display[LINEAR_LENGTH];
static HANDLE stdout_h;

void init_display(HANDLE *handle)
{
    stdout_h = handle;
    clear_display();
}

void clear_display(void)
{
    memset(display, ' ', LINEAR_LENGTH);
    line_feed();
    // SetConsoleCursorPosition(stdout_h, (COORD){1, 1});
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
    write(STDOUT_FILENO, display, LINEAR_LENGTH);
}

void draw_sprite(SPRITE *sprite)
{
    int i, j;
    unsigned char spr;
    for (i = sprite->y; *(sprite->pixels) != '\0'; ++i)
        for (j = sprite->x, spr = *(sprite->pixels)++; spr; ++j, spr <<= 1)
            display[(COLS * i) + (j + 1)] = spr & BIT_MASK ? '*' : ' ';
    line_feed();
}

void line_feed(void)
{
    int i;
    for (i = COLS; i <= LINEAR_LENGTH; i += COLS)
        display[i] = '\n';
    wprintf(L"\x1B[1;1H");
}
