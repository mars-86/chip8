#include "instruction.h"
#include "registers.h"
#include "display.h"
#include "memory.h"
#include "keyboard.h"
#include "../utils/misc/random.h"
#include "instruction_dump.h"
#include "instruction_misc.h"

void SYS_addr(unsigned short *opcode)
{

}

void CLS(void)
{
    clear_display();
    DUMP_INSTRUCTION();
}

void RET(void)
{
    set_PC(pop_SP());
    DUMP_INSTRUCTION();
}

void JP_addr(unsigned short *opcode)
{
    set_PC(_GET_NNN(opcode));
    DUMP_INSTRUCTION_ADDR(opcode);
}

void CALL_addr(unsigned short *opcode)
{
    push_SP(get_PC());
    set_PC(_GET_NNN(opcode));
    DUMP_INSTRUCTION_ADDR(opcode);
}

void SE_Vx_byte(unsigned short *opcode)
{
    get_Vx(_GET_X(opcode)) == _GET_KK(opcode) ? increment_PC(2) : increment_PC(1);
}

void SNE_Vx_byte(unsigned short *opcode)
{
    get_Vx(_GET_X(opcode)) != _GET_KK(opcode) ? increment_PC(2) : increment_PC(1);
}

void SE_Vx_Vy(unsigned short *opcode)
{
    get_Vx(_GET_X(opcode)) == get_Vx(_GET_Y(opcode)) ? increment_PC(2) : increment_PC(1);
}

void LD_Vx_byte(unsigned short *opcode)
{
    set_Vx(_GET_KK(opcode), _GET_X(opcode));
}

void ADD_Vx_byte(unsigned short *opcode)
{
    unsigned short Vn = _GET_X(opcode);
    set_Vx(get_Vx(Vn) + _GET_KK(opcode), Vn);
}

void LD_Vx_Vy(unsigned short *opcode)
{
    set_Vx(get_Vx(_GET_Y(opcode)), _GET_X(opcode));
}

void OR_Vx_Vy(unsigned short *opcode)
{
    set_Vx(get_Vx(_GET_X(opcode)) | get_Vx(_GET_Y(opcode)), _GET_X(opcode));
}

void AND_Vx_Vy(unsigned short *opcode)
{
    set_Vx(get_Vx(_GET_X(opcode)) & get_Vx(_GET_Y(opcode)), _GET_X(opcode));
}

void XOR_Vx_Vy(unsigned short *opcode)
{
    set_Vx(get_Vx(_GET_X(opcode)) ^ get_Vx(_GET_Y(opcode)), _GET_X(opcode));
}

void ADD_Vx_Vy(unsigned short *opcode)
{
    unsigned short val = get_Vx(_GET_X(opcode)) + get_Vx(_GET_Y(opcode));
    set_Vx(val > 255 ? 1 : 0, 0xF);
    set_Vx((unsigned short)(val & 0xFF), get_Vx(_GET_X(opcode)));
}

void SUB_Vx_Vy(unsigned short *opcode)
{
    unsigned short val = get_Vx(_GET_X(opcode)) - get_Vx(_GET_Y(opcode));
    set_Vx(get_Vx(_GET_X(opcode)) > get_Vx(_GET_Y(opcode)) ? 1 : 0, 0xF);
    set_Vx(val, get_Vx(_GET_X(opcode)));
}

void SHR_Vx(unsigned short *opcode)
{
    unsigned short vx = get_Vx(_GET_X(opcode));
    set_Vx(vx & 0x01 ? 1 : 0, 0xF);
    set_Vx(vx >> 1, _GET_X(opcode));
}

void SUBN_Vx_Vy(unsigned short *opcode)
{
    unsigned short val = get_Vx(_GET_Y(opcode)) - get_Vx(_GET_X(opcode));
    set_Vx(get_Vx(_GET_Y(opcode)) > get_Vx(_GET_X(opcode)) ? 1 : 0, 0xF);
    set_Vx(val, get_Vx(_GET_X(opcode)));
}

void SHL_Vx(unsigned short *opcode)
{
    unsigned short vx = get_Vx(_GET_X(opcode));
    set_Vx(vx & 0x80 ? 1 : 0, 0xF);
    set_Vx(vx << 1, _GET_X(opcode));
}

void SNE_Vx_Vy(unsigned short *opcode)
{
    get_Vx(_GET_X(opcode)) != get_Vx(_GET_Y(opcode)) ? increment_PC(2) : increment_PC(1);
}

void LD_I_addr(unsigned short *opcode)
{
    set_I(_GET_NNN(opcode));
    DUMP_INSTRUCTION_ADDR(opcode);
}

void JP_V0_addr(unsigned short *opcode)
{
    set_PC(_GET_NNN(opcode) + get_Vx(0));
}

void RND_Vx_byte(unsigned short *opcode)
{
    set_Vx(get_random_uint8() & _GET_KK(opcode), _GET_X(opcode));
}

void DRW_Vx_Vy_nibble(unsigned short *opcode)
{
    unsigned short n = *opcode & MASK_LOW_BYTE_LOW_NIBBLE,
                    x = _GET_X(opcode), y = _GET_Y(opcode);
    unsigned char mbuff[n];
    unsigned char collision;
    read_from_mem(mbuff, get_I(), n);
    SPRITE sp = { get_Vx(x), get_Vx(y), mbuff, n, NULL };
    draw_sprites(&sp, &collision);
    set_Vx(collision, 0xF);
}

void LD_Vx_DT(unsigned short *opcode)
{
    set_Vx(get_DT(), _GET_X(opcode));
}

void LD_Vx_K(unsigned short *opcode)
{
    unsigned char key;
    get_key_pressed_block(&key);
    set_Vx(key, _GET_X(opcode));
}

void LD_DT_Vx(unsigned short *opcode)
{
    set_DT(get_Vx(_GET_X(opcode)));
}

void LD_ST_Vx(unsigned short *opcode)
{
    set_ST(get_Vx(_GET_X(opcode)));
}

void ADD_I_Vx(unsigned short *opcode)
{
    set_I(get_I() + _GET_X(opcode));
}

void LD_F_Vx(unsigned short *opcode)
{
    set_I(HEX_DIGITS_START | ((get_Vx(_GET_X(opcode))) * HEX_DIGITS_SIZE));
}

void LD_B_Vx(unsigned short *opcode)
{
    unsigned short val = get_Vx(_GET_X(opcode));
    write_byte_to_mem(val % 10, get_I() + 2), val /= 10;
    write_byte_to_mem(val % 10, get_I() + 1), val /= 10;
    write_byte_to_mem(val, get_I());
}

void LD_I_Vx(unsigned short *opcode)
{
    unsigned short i, x = _GET_X(opcode);
    for (i = 0; i < x; ++i)
        write_byte_to_mem(get_Vx(i), get_I() + i);
}

void LD_Vx_I(unsigned short *opcode)
{
    unsigned short i, x = _GET_X(opcode);
    unsigned char buff[x];
    read_from_mem(buff, get_I(), x);
    for (i = 0; i < x; ++i)
        set_Vx(buff[i], i);
}
