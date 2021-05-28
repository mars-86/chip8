#ifndef _CHIP8_CORE_INCLUDED_H_
#define _CHIP8_CORE_INCLUDED_H_

int init_device(void);
int load_rom(const char *path);
int main_loop(void);
void release_resources(void);

#endif // _CHIP8_CORE_INCLUDED_H_
