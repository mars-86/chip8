#ifndef _CHIP8_SPRITE_INCLUDED_H_
#define _CHIP8_SPRITE_INCLUDED_H_

#include "digit.h"

struct sprite {
    unsigned short x;
    unsigned short y;
    unsigned char *pixels;
    unsigned short size;
    struct sprite *next;
};

typedef struct sprite SPRITE;

#endif // _CHIP8_SPRITE_INCLUDED_H_
