#ifndef _CHIP8_REGISTERS_INCLUDED_H_
#define _CHIP8_REGISTERS_INCLUDED_H_

#define STACK_LENGTH 16
#define Vx_REGISTER_LENGTH 16

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

void increment_PC(unsigned short n);
unsigned short *get_stack_top(void);
void free_registers_resources(void);

#endif // _CHIP8_REGISTERS_INCLUDED_H_
