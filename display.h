#ifndef _CHIP8_DISPLAY_INCLUDED_H_
#define _CHIP8_DISPLAY_INCLUDED_H_

#include "sprite.h"
#include <windows.h>

void init_display(HANDLE *handle);
void clear_display(void);
void draw(const unsigned char **sprites);
void draw_pixel(const unsigned char *pixel);
void draw_sprites(SPRITE *sprites);
void print(void);

#endif // _CHIP8_DISPLAY_INCLUDED_H_
