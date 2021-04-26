#include "registers.h"

static struct registers {
    unsigned char Vx[16];
    unsigned short I;
    unsigned char DT;
    unsigned char ST;
    unsigned short PC;
    unsigned short SP;
};

typedef struct registers *REGISTERS;
