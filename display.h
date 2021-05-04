#ifndef _CHIP8_DISPLAY_INCLUDED_H_
#define _CHIP8_DISPLAY_INCLUDED_H_

#include "sprite.h"

void init_display(void);
void draw(const unsigned char **sprites);
void draw_pixel(const unsigned char *pixel);
void draw_sprite(SPRITE *sprite);
void print(void);

#endif // _CHIP8_DISPLAY_INCLUDED_H_
