#include "interpreter.h"

void exec_instruction_0x0(unsigned char *sub_opcode)
{
    switch(*sub_opcode){
    case 0xE0:
        break;
    case 0xEE:
        break;
    default:
        ;
    }
}

void instruction_0x0(unsigned char *opcode)
{
    unsigned char *sub_opcode = &opcode[1];
    switch(sub_opcode[0] & 0x03) {
    case 0x00:
        exec_instruction_0x0(sub_opcode);
    }
}

void instruction_0x1(unsigned char *opcode)
{
    (*opcode & 0x0FFF);
}

void instruction_0x2(unsigned char *opcode)
{
    (*opcode & 0x0FFF);
}

void instruction_0x3(unsigned char *opcode)
{
    (*opcode & 0x0FFF);
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

void (*instructions)(unsigned char *)[] = {
    instruction_0x0, instruction_0x1, instruction_0x2,
    instruction_0x3, instruction_0x4, instruction_0x5,
    instruction_0x6, instruction_0x7, instruction_0x8,
    instruction_0x9, instruction_0xA, instruction_0xB,
    instruction_0xC, instruction_0xD, instruction_0xE,
    instruction_0xF
}

void interpret(unsigned char *opcode)
{
    instructions[opcode[0] & 0xC)](opcode);
}
