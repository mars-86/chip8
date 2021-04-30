#include "interpreter.h"
#include "registers.h"

struct registers *REGISTERS;

void exec_instruction_0x0(unsigned char *opcode)
{
    switch(*opcode & MASK_LOW_BYTE){
    case 0xE0:
        break;
    case 0xEE:
        set_PC(pop_SP());
        break;
    default:
        ;
    }
}

void instruction_0x0(unsigned char *opcode)
{
    switch(*opcode & MASK_HIGH_BYTE_LOW_NIBBLE) {
    case 0x0:
        exec_instruction_0x0(opcode);
    }
}

void instruction_0x1(unsigned char *opcode)
{
    set_PC((*opcode & MASK_NNN));
}

void instruction_0x2(unsigned char *opcode)
{
    push_SP(get_PC());
    set_PC((*opcode & MASK_NNN));
}

void instruction_0x3(unsigned char *opcode)
{
    get_Vx((*opcode & MASK_HIGH_BYTE_LOW_NIBBLE) >> 8) == (*opcode & MASK_KK) ? increment_PC(2) : increment_PC(1);
}

void instruction_0x4(unsigned char *opcode)
{

}

void instruction_0x5(unsigned char *sub_opcode)
{

}

void instruction_0x6(unsigned char *sub_opcode)
{

}

void instruction_0x7(unsigned char *sub_opcode)
{

}

void instruction_0x8(unsigned char *sub_opcode)
{

}

void instruction_0x9(unsigned char *sub_opcode)
{

}

void instruction_0xA(unsigned char *sub_opcode)
{

}

void instruction_0xB(unsigned char *sub_opcode)
{

}

void instruction_0xC(unsigned char *sub_opcode)
{

}

void instruction_0xD(unsigned char *sub_opcode)
{

}

void instruction_0xE(unsigned char *sub_opcode)
{

}

void instruction_0xF(unsigned char *sub_opcode)
{

}

void (*instructions[])(unsigned char *) = {
    instruction_0x0, instruction_0x1, instruction_0x2,
    instruction_0x3, instruction_0x4, instruction_0x5,
    instruction_0x6, instruction_0x7, instruction_0x8,
    instruction_0x9, instruction_0xA, instruction_0xB,
    instruction_0xC, instruction_0xD, instruction_0xE,
    instruction_0xF
};

void interpret(unsigned char *opcode)
{
    instructions[*opcode & MASK_HIGH_BYTE_HIGH_NIBBLE](opcode);
}
