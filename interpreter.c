#include "interpreter.h"
#include "instruction.h"
#include "registers.h"
#include "display.h"
#include "memory.h"
#include "keyboard.h"

void instruction_0x0(unsigned short *opcode)
{
    switch((*opcode & MASK_HIGH_BYTE_LOW_NIBBLE) >> 8) {
    case 0x0:
        switch(*opcode & MASK_LOW_BYTE){
        case 0xE0:
            CLS();
            break;
        case 0xEE:
            RET();
            break;
        default:
            ;
        }
    default:
        break;
    }
}

void instruction_0x1(unsigned short *opcode)
{
    JP_addr(opcode);
}

void instruction_0x2(unsigned short *opcode)
{
    CALL_addr(opcode);
}

void instruction_0x3(unsigned short *opcode)
{
    SE_Vx_byte(opcode);
}

void instruction_0x4(unsigned short *opcode)
{
    SNE_Vx_byte(opcode);
}

void instruction_0x5(unsigned short *opcode)
{
    SE_Vx_Vy(opcode);
}

void instruction_0x6(unsigned short *opcode)
{
    LD_Vx_byte(opcode);
}

void instruction_0x7(unsigned short *opcode)
{
    ADD_Vx_byte(opcode);
}

void instruction_0x8(unsigned short *opcode)
{
    switch(*opcode & MASK_LOW_BYTE_LOW_NIBBLE) {
    case 0x0:
        LD_Vx_Vy(opcode);
        break;
    case 0x1:
        OR_Vx_Vy(opcode);
        break;
    case 0x2:
        AND_Vx_Vy(opcode);
        break;
    case 0x3:
        XOR_Vx_Vy(opcode);
        break;
    case 0x4:
        ADD_Vx_Vy(opcode);
        break;
    case 0x5:
        SUB_Vx_Vy(opcode);
        break;
    case 0x6:
        SHR_Vx(opcode);
        break;
    case 0x7:
        SUBN_Vx_Vy(opcode);
        break;
    case 0xE:
        SHL_Vx(opcode);
        break;
    default:
        break;
    }
}

void instruction_0x9(unsigned short *opcode)
{
    SNE_Vx_Vy(opcode);
}

void instruction_0xA(unsigned short *opcode)
{
    LD_I_addr(opcode);
}

void instruction_0xB(unsigned short *opcode)
{
    JP_V0_addr(opcode);
}

void instruction_0xC(unsigned short *opcode)
{
    RND_Vx_byte(opcode);
}

void instruction_0xD(unsigned short *opcode)
{
    DRW_Vx_Vy_nibble(opcode);
}

void instruction_0xE(unsigned short *opcode)
{
    switch(*opcode & MASK_LOW_BYTE) {
    case 0x9E:
        break;
    case 0xA1:
        break;
    }
}

void instruction_0xF(unsigned short *opcode)
{
    switch(*opcode & MASK_LOW_BYTE) {
    case 0x07:
        LD_Vx_DT(opcode);
        break;
    case 0x0A:
        LD_Vx_K(opcode);
        break;
    case 0x15:
        LD_DT_Vx(opcode);
        break;
    case 0x18:
        LD_ST_Vx(opcode);
        break;
    case 0x1E:
        ADD_I_Vx(opcode);
        break;
    case 0x29:
        LD_F_Vx(opcode);
        break;
    case 0x33:
        LD_B_Vx(opcode);
        break;
    case 0x55:
        LD_I_Vx(opcode);
        break;
    case 0x65:
        LD_Vx_I(opcode);
        break;
    default:
        break;
    }
}

void (*instructions[])(unsigned short *) = {
    instruction_0x0, instruction_0x1, instruction_0x2,
    instruction_0x3, instruction_0x4, instruction_0x5,
    instruction_0x6, instruction_0x7, instruction_0x8,
    instruction_0x9, instruction_0xA, instruction_0xB,
    instruction_0xC, instruction_0xD, instruction_0xE,
    instruction_0xF
};

void interpret(unsigned char *opcode)
{
    unsigned short opc = (*opcode << 8) | *(opcode + 1);
    instructions[(opc & MASK_HIGH_BYTE_HIGH_NIBBLE) >> 12](&opc);
}
