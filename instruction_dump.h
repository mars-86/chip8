#ifndef _CHIP8_INSTRUCTION_DUMP_INCLUDED_H_
#define _CHIP8_INSTRUCTION_DUMP_INCLUDED_H_

#include "instruction_misc.h"
#include <string.h>
#include "../utils/string/string_manip.h"

#define DUMP_INSTRUCTION_MAX 5
#define DUMP_INSTRUCTION_LEN 32

extern char instructions_history[DUMP_INSTRUCTION_MAX][DUMP_INSTRUCTION_LEN];

void instruction_dump(void);
static int i = 0;

#define _CHECK_I(i) i = (i == (DUMP_INSTRUCTION_MAX - 1)) ? (DUMP_INSTRUCTION_MAX - 1) : (i + 1)

#define DUMP_INSTRUCTION() \
    memset(instructions_history[0], '\0', DUMP_INSTRUCTION_LEN * sizeof(char)); \
    sprintf(instructions_history[i], "%s%c", __FUNCTION__, '\0'); \
    _CHECK_I(i)

#define DUMP_INSTRUCTION_ADDR(opcode) \
    char iname[8]; \
    memcpy(iname, __FUNCTION__, 4); \
    memset(instructions_history[i], 0, DUMP_INSTRUCTION_LEN * sizeof(char)); \
    sprintf(instructions_history[i], "%s %.4x", iname, _GET_NNN(opcode)); \
    _CHECK_I(i)

#endif // _CHIP8_INSTRUCTION_DUMP_INCLUDED_H_
