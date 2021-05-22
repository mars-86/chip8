#include "interpreter.h"
#include "registers.h"
#include "display.h"
#include "../utils/misc/random.h"

void instruction_0x0(unsigned char *opcode)
{
    switch((*opcode & MASK_HIGH_BYTE_LOW_NIBBLE) >> 8) {
    case 0x0:
        switch(*opcode & MASK_LOW_BYTE){
        case 0xE0:
            clear_display();
            break;
        case 0xEE:
            set_PC(pop_SP());
            break;
        default:
            ;
        }
    default:
        break;
    }
}

void instruction_0x1(unsigned char *opcode)
{
    set_PC(*opcode & MASK_NNN);
}

void instruction_0x2(unsigned char *opcode)
{
    push_SP(get_PC());
    set_PC(*opcode & MASK_NNN);
}

void instruction_0x3(unsigned char *opcode)
{
    get_Vx((*opcode & MASK_X) >> 8) == (*opcode & MASK_KK) ? increment_PC(2) : increment_PC(1);
}

void instruction_0x4(unsigned char *opcode)
{
    get_Vx((*opcode & MASK_X) >> 8) != (*opcode & MASK_KK) ? increment_PC(2) : increment_PC(1);
}

void instruction_0x5(unsigned char *opcode)
{
    get_Vx((*opcode & MASK_X) >> 8) == get_Vx((*opcode & MASK_Y) >> 4) ? increment_PC(2) : increment_PC(1);
}

void instruction_0x6(unsigned char *opcode)
{
    set_Vx(*opcode & MASK_KK, (*opcode & MASK_X) >> 8);
}

void instruction_0x7(unsigned char *opcode)
{
    unsigned char Vn = (*opcode & MASK_X) >> 8;
    set_Vx(get_Vx(Vn) + (*opcode & MASK_KK), Vn);
}

void instruction_0x8(unsigned char *opcode)
{

}

void instruction_0x9(unsigned char *opcode)
{
    get_Vx((*opcode & MASK_X) >> 8) != get_Vx((*opcode & MASK_Y) >> 4) ? increment_PC(2) : increment_PC(1);
}

void instruction_0xA(unsigned char *opcode)
{
    set_I(*opcode & MASK_NNN);
}

void instruction_0xB(unsigned char *opcode)
{
    set_PC((*opcode & MASK_NNN) + get_Vx(0));
}

void instruction_0xC(unsigned char *opcode)
{
    set_Vx(get_random_uint8() & (*opcode & MASK_KK), (*opcode & MASK_X) >> 8);
}

void instruction_0xD(unsigned char *opcode)
{

}

void instruction_0xE(unsigned char *opcode)
{
    switch(*opcode & MASK_LOW_BYTE) {
    case 0x9E:
        break;
    case 0xA1:
        break;
    }
}

void instruction_0xF(unsigned char *opcode)
{
    switch(*opcode & MASK_LOW_BYTE) {
    case 0x07:
        set_Vx(get_DT(), (*opcode & MASK_X) >> 8);
        break;
    case 0x0A:
        break;
    case 0x15:
        set_DT(get_Vx((*opcode & MASK_X) >> 8));
        break;
    case 0x18:
        set_ST(get_Vx((*opcode & MASK_X) >> 8));
        break;
    case 0x1E:
        set_I(get_I() + ((*opcode & MASK_X) >> 8));
        break;
    case 0x29:
        break;
    case 0x33:
        break;
    case 0x55:
        break;
    case 0x65:
        break;
    default:
        break;
    }
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
