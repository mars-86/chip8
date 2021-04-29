#ifndef _CHIP8_REGISTERS_INCLUDED_H_
#define _CHIP8_REGISTERS_INCLUDED_H_

#define MASK_NNN 0xFFF
#define MASK_HIGH_BYTE 0xFF00
#define MASK_LOW_BYTE 0x00FF
#define MASK_LOW_BYTE_LOW_NIBBLE 0x000F
#define MASK_LOW_BYTE_HIGH_NIBBLE 0x00F0
#define MASK_HIGH_BYTE_LOW_NIBBLE 0x0F00
#define MASK_HIGH_BYTE_HIGH_NIBBLE 0xF000
#define MASK_X MASK_HIGH_BYTE_LOW_NIBBLE
#define MASK_Y MASK_LOW_BYTE_HIGH_NIBBLE
#define MASK_KK MASK_LOW_BYTE

void init_registers(void);

void set_Vx(unsigned char value, unsigned char Vn);
void set_I(unsigned short value);
void set_DT(unsigned char value);
void set_ST(unsigned char value);
void set_PC(unsigned short address);
void push_SP(unsigned short address);

unsigned char get_Vx(unsigned char Vn);
unsigned short get_I(void);
unsigned char get_DT(void);
unsigned char get_ST(void);
unsigned short get_PC(void);
unsigned short pop_SP(void);

#endif // _CHIP8_REGISTERS_INCLUDED_H_
