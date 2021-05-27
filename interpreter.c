#include "interpreter.h"
#include "registers.h"
#include "display.h"
#include "memory.h"
#include "keyboard.h"
#include "../utils/misc/random.h"

void CLS(void)
{
    clear_display();
}

void RET(void)
{
    set_PC(pop_SP());
}

void instruction_0x0(unsigned char *opcode)
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

void LD_Vx_Vy(unsigned char *opcode)
{
    set_Vx(get_Vx((*opcode & MASK_Y) >> 4), (*opcode & MASK_X) >> 8);
}

void OR_Vx_Vy(unsigned char *opcode)
{
    set_Vx(get_Vx((*opcode & MASK_X) >> 8) | get_Vx((*opcode & MASK_Y) >> 4), (*opcode & MASK_X) >> 8);
}

void AND_Vx_Vy(unsigned char *opcode)
{
    set_Vx(get_Vx((*opcode & MASK_X) >> 8) & get_Vx((*opcode & MASK_Y) >> 4), (*opcode & MASK_X) >> 8);
}

void XOR_Vx_Vy(unsigned char *opcode)
{
    set_Vx(get_Vx((*opcode & MASK_X) >> 8) ^ get_Vx((*opcode & MASK_Y) >> 4), (*opcode & MASK_X) >> 8);
}

void ADD_Vx_Vy(unsigned char *opcode)
{
    unsigned short val = get_Vx((*opcode & MASK_X) >> 8) + get_Vx((*opcode & MASK_Y) >> 4);
    set_Vx(val > 255 ? 1 : 0, 0xF);
    set_Vx((unsigned char)(val & 0xFF), get_Vx((*opcode & MASK_X) >> 8));
}

void SUB_Vx_Vy(unsigned char *opcode)
{
    unsigned short val = get_Vx((*opcode & MASK_X) >> 8) - get_Vx((*opcode & MASK_Y) >> 4);
    set_Vx(get_Vx((*opcode & MASK_X) >> 8) > get_Vx((*opcode & MASK_Y) >> 4) ? 1 : 0, 0xF);
    set_Vx(val, get_Vx((*opcode & MASK_X) >> 8));
}

void SHR_Vx(unsigned char *opcode)
{
    unsigned char vx = get_Vx((*opcode & MASK_X) >> 8);
    set_Vx(vx & 0x01 ? 1 : 0, 0xF);
    set_Vx(vx >> 1, (*opcode & MASK_X) >> 8);
}

void SUBN_Vx_Vy(unsigned char *opcode)
{
    unsigned char val = get_Vx((*opcode & MASK_Y) >> 4) - get_Vx((*opcode & MASK_X) >> 8);
    set_Vx(get_Vx((*opcode & MASK_Y) >> 4) > get_Vx((*opcode & MASK_X) >> 8) ? 1 : 0, 0xF);
    set_Vx(val, get_Vx((*opcode & MASK_X) >> 8));
}

void SHL_Vx(unsigned char *opcode)
{
    unsigned char vx = get_Vx((*opcode & MASK_X) >> 8);
    set_Vx(vx & 0x80 ? 1 : 0, 0xF);
    set_Vx(vx << 1, (*opcode & MASK_X) >> 8);
}

void instruction_0x8(unsigned char *opcode)
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

void DRW_Vx_Vy_nibble(unsigned char *opcode)
{
    unsigned char n = *opcode & MASK_LOW_BYTE_LOW_NIBBLE, buff[n];
    read_from_mem(buff, get_I(), n);
    SPRITE sp = { (*opcode & MASK_X) >> 8, (*opcode & MASK_Y) >> 4, buff, NULL };
    draw_sprites(&sp);
}

void instruction_0xD(unsigned char *opcode)
{
    DRW_Vx_Vy_nibble(opcode);
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

void LD_Vx_K(unsigned char *opcode)
{
    unsigned char key;
    get_key_pressed_block(&key);
    set_Vx(key, (*opcode & MASK_X) >> 8);
}

void LD_F_Vx(unsigned char *opcode)
{
    set_I(get_Vx((*opcode & MASK_X) >> 8));
}

void LD_B_Vx(unsigned char *opcode)
{
    unsigned char val = get_Vx((*opcode & MASK_X) >> 8);
    write_byte_to_mem(val % 10, get_I() + 2), val /= 10;
    write_byte_to_mem(val % 10, get_I() + 1), val /= 10;
    write_byte_to_mem(val, get_I());
}

void LD_I_Vx(unsigned char *opcode)
{
    unsigned char i, x = (*opcode & MASK_X) >> 8;
    for (i = 0; i < x; ++i)
        write_byte_to_mem(get_Vx(i), get_I() + i);
}

void LD_Vx_I(unsigned char *opcode)
{
    unsigned char i, x = (*opcode & MASK_X) >> 8, buff[x];
    read_from_mem(buff, get_I(), x);
    for (i = 0; i < x; ++i)
        set_Vx(buff[i], i);
}

void instruction_0xF(unsigned char *opcode)
{
    switch(*opcode & MASK_LOW_BYTE) {
    case 0x07:
        set_Vx(get_DT(), (*opcode & MASK_X) >> 8);
        break;
    case 0x0A:
        LD_Vx_K(opcode);
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
    instructions[(*opcode & MASK_HIGH_BYTE_HIGH_NIBBLE) >> 12](opcode);
}
