#ifndef _CHIP8_KEYBOARD_INCLUDED_H_
#define _CHIP8_KEYBOARD_INCLUDED_H_

void init_keyboard(void);
int get_key_pressed_block(unsigned char *key);
int get_key_pressed_non_block(unsigned char *key);

#endif // _CHIP8_KEYBOARD_INCLUDED_H_
