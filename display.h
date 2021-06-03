#ifndef _CHIP8_DISPLAY_INCLUDED_H_
#define _CHIP8_DISPLAY_INCLUDED_H_

#include "sprite.h"
#include <windows.h>

#define HEX_DIGITS_START 0x0000
#define HEX_DIGITS_SIZE 5

void init_display(HANDLE *handle);
void clear_display(void);
void draw(const unsigned char **sprites);
void draw_pixel(const unsigned char *pixel);
void draw_sprites(SPRITE *sprites, unsigned char *collision);
size_t get_sprite(unsigned char *buffer, short x, short y, size_t n);
void print(void);
void cursor_to_start(void);

#endif // _CHIP8_DISPLAY_INCLUDED_H_
