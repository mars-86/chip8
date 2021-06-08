#ifndef _CHIP8_INSTRUCTION_MISC_INCLUDED_H_
#define _CHIP8_INSTRUCTION_MISC_INCLUDED_H_

#define MASK_NNN 0x0FFF
#define MASK_LOW_BYTE 0x00FF
#define MASK_HIGH_BYTE 0xFF00
#define MASK_LOW_BYTE_LOW_NIBBLE 0x000F
#define MASK_LOW_BYTE_HIGH_NIBBLE 0x00F0
#define MASK_HIGH_BYTE_LOW_NIBBLE 0x0F00
#define MASK_HIGH_BYTE_HIGH_NIBBLE 0xF000
#define MASK_X MASK_HIGH_BYTE_LOW_NIBBLE
#define MASK_Y MASK_LOW_BYTE_HIGH_NIBBLE
#define MASK_KK MASK_LOW_BYTE

#define _GET_X(opcode) (((*opcode) & (MASK_X)) >> (8))
#define _GET_Y(opcode) (((*opcode) & (MASK_Y)) >> (4))
#define _GET_KK(opcode) ((*opcode) & (MASK_KK))
#define _GET_NNN(opcode) ((*opcode) & (MASK_NNN))

#endif // _CHIP8_INSTRUCTION_MISC_INCLUDED_H_
