#include "interpreter.h"

void exec_instruction_0x0(unsigned char *sub_opcode)
{
    switch(sub_opcode){
    case 0xE0:
        break;
    case 0xEE:
        break;
    default:
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

}

void instruction_0x3(unsigned char *opcode)
{

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

void interpret(unsigned char *opcode)
{
    switch(opcode[0] & 0xC){
    case 0x0:
        instruction_0x0(opcode);
        break;
    case 0x1:
        instruction_0x1(opcode);
        break;
    case 0x2:
        instruction_0x2(opcode);
        break;
    case 0x3:
        instruction_0x3(opcode);
        break;
    case 0x4:
        instruction_0x4(opcode);
        break;
    case 0x5:
        instruction_0x5(opcode);
        break;
    case 0x6:
        instruction_0x6(opcode);
        break;
    case 0x7:
        instruction_0x7(opcode);
        break;
    case 0x8:
        instruction_0x8(opcode);
        break;
    case 0x9:
        instruction_0x9(opcode);
        break;
    case 0xA:
        instruction_0xA(opcode);
        break;
    case 0xB:
        instruction_0xB(opcode);
        break;
    case 0xC:
        instruction_0xC(opcode);
        break;
    case 0xD:
        instruction_0xD(opcode);
        break;
    case 0xE:
        instruction_0xE(opcode);
        break;
    case 0xF:
        instruction_0xF(opcode);
        break;
    default:
    }
}
