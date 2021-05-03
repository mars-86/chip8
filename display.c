#include "display.h"
#include <stdio.h>
#define BIT_MASK 0x01

void draw_sprite(const unsigned char *sprite)
{
    int i;
    for (i = 0; i < 5; ++i) {
        unsigned char spr = *(sprite + i);
        while (spr) {
            spr & BIT_MASK ? putc('*', stdout) : putc(' ', stdout);
            spr >>= 1;
        }
        putc('\n', stdout);
    }
}
