#include "instruction.h"
#include "registers.h"
#include "display.h"
#include "../utils/misc/random.h"

void SYS_addr(unsigned short *opcode)
{

}

void CLS(void)
{
    clear_display();
}

void RET(void)
{
    set_PC(pop_SP());
}

void JP_addr(unsigned short *opcode)
{
    set_PC(*opcode & MASK_NNN);
}

void CALL_addr(unsigned short *opcode)
{
    push_SP(get_PC());
    set_PC(*opcode & MASK_NNN);
}

void SE_Vx_byte(unsigned short *opcode)
{
    get_Vx((*opcode & MASK_X) >> 8) == (*opcode & MASK_KK) ? increment_PC(2) : increment_PC(1);
}

void SNE_Vx_byte(unsigned short *opcode)
{
    get_Vx((*opcode & MASK_X) >> 8) != (*opcode & MASK_KK) ? increment_PC(2) : increment_PC(1);
}

void SE_Vx_Vy(unsigned short *opcode)
{
    get_Vx((*opcode & MASK_X) >> 8) == get_Vx((*opcode & MASK_Y) >> 4) ? increment_PC(2) : increment_PC(1);
}

void LD_Vx_byte(unsigned short *opcode)
{
    set_Vx(*opcode & MASK_KK, (*opcode & MASK_X) >> 8);
}

void ADD_Vx_byte(unsigned short *opcode)
{
    unsigned short Vn = (*opcode & MASK_X) >> 8;
    set_Vx(get_Vx(Vn) + (*opcode & MASK_KK), Vn);
}

void LD_Vx_Vy(unsigned short *opcode)
{
    set_Vx(get_Vx((*opcode & MASK_Y) >> 4), (*opcode & MASK_X) >> 8);
}

void OR_Vx_Vy(unsigned short *opcode)
{
    set_Vx(get_Vx((*opcode & MASK_X) >> 8) | get_Vx((*opcode & MASK_Y) >> 4), (*opcode & MASK_X) >> 8);
}

void AND_Vx_Vy(unsigned short *opcode)
{
    set_Vx(get_Vx((*opcode & MASK_X) >> 8) & get_Vx((*opcode & MASK_Y) >> 4), (*opcode & MASK_X) >> 8);
}

void XOR_Vx_Vy(unsigned short *opcode)
{
    set_Vx(get_Vx((*opcode & MASK_X) >> 8) ^ get_Vx((*opcode & MASK_Y) >> 4), (*opcode & MASK_X) >> 8);
}

void ADD_Vx_Vy(unsigned short *opcode)
{
    unsigned short val = get_Vx((*opcode & MASK_X) >> 8) + get_Vx((*opcode & MASK_Y) >> 4);
    set_Vx(val > 255 ? 1 : 0, 0xF);
    set_Vx((unsigned short)(val & 0xFF), get_Vx((*opcode & MASK_X) >> 8));
}

void SUB_Vx_Vy(unsigned short *opcode)
{
    unsigned short val = get_Vx((*opcode & MASK_X) >> 8) - get_Vx((*opcode & MASK_Y) >> 4);
    set_Vx(get_Vx((*opcode & MASK_X) >> 8) > get_Vx((*opcode & MASK_Y) >> 4) ? 1 : 0, 0xF);
    set_Vx(val, get_Vx((*opcode & MASK_X) >> 8));
}

void SHR_Vx(unsigned short *opcode)
{
    unsigned short vx = get_Vx((*opcode & MASK_X) >> 8);
    set_Vx(vx & 0x01 ? 1 : 0, 0xF);
    set_Vx(vx >> 1, (*opcode & MASK_X) >> 8);
}

void SUBN_Vx_Vy(unsigned short *opcode)
{
    unsigned short val = get_Vx((*opcode & MASK_Y) >> 4) - get_Vx((*opcode & MASK_X) >> 8);
    set_Vx(get_Vx((*opcode & MASK_Y) >> 4) > get_Vx((*opcode & MASK_X) >> 8) ? 1 : 0, 0xF);
    set_Vx(val, get_Vx((*opcode & MASK_X) >> 8));
}

void SHL_Vx(unsigned short *opcode)
{
    unsigned short vx = get_Vx((*opcode & MASK_X) >> 8);
    set_Vx(vx & 0x80 ? 1 : 0, 0xF);
    set_Vx(vx << 1, (*opcode & MASK_X) >> 8);
}

void SNE_Vx_Vy(unsigned short *opcode)
{
    get_Vx((*opcode & MASK_X) >> 8) != get_Vx((*opcode & MASK_Y) >> 4) ? increment_PC(2) : increment_PC(1);
}

void LD_I_addr(unsigned short *opcode)
{
    set_I(*opcode & MASK_NNN);
}

void JP_V0_addr(unsigned short *opcode)
{
    set_PC((*opcode & MASK_NNN) + get_Vx(0));
}

void RND_Vx_byte(unsigned short *opcode)
{
    set_Vx(get_random_uint8() & (*opcode & MASK_KK), (*opcode & MASK_X) >> 8);
}

void DRW_Vx_Vy_nibble(unsigned short *opcode)
{
    unsigned short n = *opcode & MASK_LOW_BYTE_LOW_NIBBLE,
                    x = (*opcode & MASK_X) >> 8, y = (*opcode & MASK_Y) >> 4;
    unsigned char mbuff[n];
    unsigned char collision;
    read_from_mem(mbuff, get_I(), n);
    SPRITE sp = { get_Vx(x), get_Vx(y), mbuff, n, NULL };
    draw_sprites(&sp, &collision);
    set_Vx(collision, 0xF);
}

void LD_Vx_DT(unsigned short *opcode)
{
    set_Vx(get_DT(), (*opcode & MASK_X) >> 8);
}

void LD_Vx_K(unsigned short *opcode)
{
    unsigned char key;
    get_key_pressed_block(&key);
    set_Vx(key, (*opcode & MASK_X) >> 8);
}

void LD_DT_Vx(unsigned short *opcode)
{
    set_DT(get_Vx((*opcode & MASK_X) >> 8));
}

void LD_ST_Vx(unsigned short *opcode)
{
    set_ST(get_Vx((*opcode & MASK_X) >> 8));
}

void ADD_I_Vx(unsigned short *opcode)
{
    set_I(get_I() + ((*opcode & MASK_X) >> 8));
}

void LD_F_Vx(unsigned short *opcode)
{
    set_I(HEX_DIGITS_START | ((get_Vx((*opcode & MASK_X) >> 8)) * HEX_DIGITS_SIZE));
}

void LD_B_Vx(unsigned short *opcode)
{
    unsigned short val = get_Vx((*opcode & MASK_X) >> 8);
    write_byte_to_mem(val % 10, get_I() + 2), val /= 10;
    write_byte_to_mem(val % 10, get_I() + 1), val /= 10;
    write_byte_to_mem(val, get_I());
}

void LD_I_Vx(unsigned short *opcode)
{
    unsigned short i, x = (*opcode & MASK_X) >> 8;
    for (i = 0; i < x; ++i)
        write_byte_to_mem(get_Vx(i), get_I() + i);
}

void LD_Vx_I(unsigned short *opcode)
{
    unsigned short i, x = (*opcode & MASK_X) >> 8;
    unsigned char buff[x];
    read_from_mem(buff, get_I(), x);
    for (i = 0; i < x; ++i)
        set_Vx(buff[i], i);
}
