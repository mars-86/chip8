#include "instruction_dump.h"

char instructions_history[DUMP_INSTRUCTION_MAX][DUMP_INSTRUCTION_LEN];

void instruction_dump(void)
{
    int i;
    for (i = 0; i < DUMP_INSTRUCTION_MAX; ++i)
        printf("%s\n", instructions_history[i]);
}
