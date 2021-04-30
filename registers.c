#include "registers.h"
#include "memory.h"
#include <stdlib.h>
#define SP_REGISTER_INDEX_START -1
#define STACK_LENGTH 16
#define Vx_REGISTER_LENGTH 16
#define STACK_FAULT 0xFFFF

static struct registers {
    unsigned char Vx[Vx_REGISTER_LENGTH];
    unsigned short I;
    unsigned char DT;
    unsigned char ST;
    unsigned char *PC;
    unsigned short SP[STACK_LENGTH];
} *REGISTERS;

static short SP_index = SP_REGISTER_INDEX_START;
extern unsigned char *mem_ptr;

void init_registers(void)
{
    REGISTERS = (struct registers *)malloc(sizeof(struct registers));
    REGISTERS->PC = NULL;
    int i;
    for (i = 0; i < Vx_REGISTER_LENGTH; ++i)
        printf("%d ", REGISTERS->Vx[i]);
    REGISTERS->PC = mem_ptr;
    free(REGISTERS);
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
    REGISTERS->PC = &mem_ptr[address];
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
    return (*(REGISTERS->PC) << 8) | *(REGISTERS->PC + 1);
}

unsigned short pop_SP(void)
{
    unsigned short address = STACK_FAULT;
    if (SP_index > SP_REGISTER_INDEX_START)
        address = REGISTERS->SP[SP_index--];
    return address;
}

void increment_PC(unsigned short n)
{
    REGISTERS->PC += (n << 1); // instructions are two bytes long
}
