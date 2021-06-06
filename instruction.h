#ifndef _CHIP8_INSTRUCTION_INCLUDED_H_
#define _CHIP8_INSTRUCTION_INCLUDED_H_

void SYS_addr(unsigned short *opcode);
void CLS(void);
void RET(void);

void JP_addr(unsigned short *opcode);

void CALL_addr(unsigned short *opcode);

void SE_Vx_byte(unsigned short *opcode);

void SNE_Vx_byte(unsigned short *opcode);

void SE_Vx_Vy(unsigned short *opcode);

void LD_Vx_byte(unsigned short *opcode);
void ADD_Vx_byte(unsigned short *opcode);
void LD_Vx_Vy(unsigned short *opcode);
void OR_Vx_Vy(unsigned short *opcode);
void AND_Vx_Vy(unsigned short *opcode);
void XOR_Vx_Vy(unsigned short *opcode);
void ADD_Vx_Vy(unsigned short *opcode);
void SUB_Vx_Vy(unsigned short *opcode);
void SHR_Vx(unsigned short *opcode);
void SUBN_Vx_Vy(unsigned short *opcode);
void SHL_Vx(unsigned short *opcode);

void SNE_Vx_Vy(unsigned short *opcode);

void LD_I_addr(unsigned short *opcode);

void JP_V0_addr(unsigned short *opcode);

void RND_Vx_byte(unsigned short *opcode);

void DRW_Vx_Vy_nibble(unsigned short *opcode);

void SKP_Vx(unsigned short *opcode);
void SKNP_vx(unsigned short *opcode);

void LD_Vx_DT(unsigned short *opcode);
void LD_Vx_K(unsigned short *opcode);
void LD_DT_Vx(unsigned short *opcode);
void LD_ST_Vx(unsigned short *opcode);
void ADD_I_Vx(unsigned short *opcode);
void LD_F_Vx(unsigned short *opcode);
void LD_B_Vx(unsigned short *opcode);
void LD_I_Vx(unsigned short *opcode);
void LD_Vx_I(unsigned short *opcode);

#endif // _CHIP8_INSTRUCTION_INCLUDED_H_
