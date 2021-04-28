#include "registers.h"
#define SP_REGISTER_INDEX_START -1
#define STACK_LENGTH 16
#define Vx_REGISTER_LENGTH 16

static struct registers {
    unsigned char Vx[Vx_REGISTER_LENGTH];
    unsigned short I;
    unsigned char DT;
    unsigned char ST;
    unsigned short PC;
    unsigned short SP[STACK_LENGTH];
} *REGISTERS;

static short SP_index = SP_REGISTER_INDEX_START;

void init_registers(void)
{

}

void set_Vx(unsigned char value, unsigned char Vn)
{
    REGISTERS->Vx[Vn] = value;
}

void set_I(unsigned short value)
{
    REGISTERS->I = value;
}

void set_DT(unsigned char value)
{
    REGISTERS->DT = value;
}

void set_ST(unsigned char value)
{
    REGISTERS->ST = value;
}

void set_PC(unsigned short address)
{
    REGISTERS->PC = address;
}

void push_SP(unsigned short address)
{
    if (SP_index < STACK_LENGTH)
        REGISTERS->SP[++SP_index] = address;
}

unsigned char get_Vx(unsigned char Vn)
{
    return REGISTERS->Vx[Vn];
}

unsigned short get_I(void)
{
    return REGISTERS->I;
}

unsigned char get_DT(void)
{
    return REGISTERS->DT;
}

unsigned char get_ST(void)
{
    return REGISTERS->ST;
}

unsigned short get_PC(void)
{
    return REGISTERS->PC;
}

unsigned short pop_SP(void)
{
    unsigned short address = 0xFFFF;
    if (SP_index > SP_REGISTER_INDEX_START)
        address = REGISTERS->SP[SP_index--];
    return address;
}
