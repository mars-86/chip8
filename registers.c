#include "registers.h"
#include "memory.h"
#include <stdlib.h>
#include <string.h>
#define SP_REGISTER_INDEX_START -1
#define STACK_FAULT 0xFFFF

static struct registers {
    unsigned char Vx[Vx_REGISTER_LENGTH];
    unsigned short I;
    unsigned char DT;
    unsigned char ST;
    unsigned short PC;
    short SP;
} *REGISTERS;

static unsigned short stack[STACK_LENGTH];
extern unsigned char *mem_ptr;

void init_registers(void)
{
    REGISTERS = (struct registers *)malloc(sizeof(struct registers));
    memset(REGISTERS->Vx, 0, Vx_REGISTER_LENGTH);
    REGISTERS->I = REGISTERS->DT = REGISTERS->ST = 0;
    REGISTERS->PC = mem_ptr;
    REGISTERS->SP = SP_REGISTER_INDEX_START;
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
    if (REGISTERS->SP < STACK_LENGTH)
        stack[++REGISTERS->SP] = address;
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
    unsigned short address = STACK_FAULT;
    if (REGISTERS->SP > SP_REGISTER_INDEX_START)
        address = stack[REGISTERS->SP--];
    return address;
}

void increment_PC(unsigned short n)
{
    REGISTERS->PC += (n << 1); // instructions are two bytes long
}

unsigned short *get_stack_top(void)
{
    unsigned short *top = stack;
    return top;
}

void free_registers_resources(void)
{
    if (REGISTERS != NULL) free(REGISTERS);
}
