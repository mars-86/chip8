#include "registers.h"
#include <stdio.h>

void reg_dump(void)
{
    int i;
    printf("\nVx --\t");
    for (i = 0; i < 16; ++i)
        printf("%d: %.2X | ", i, get_Vx(i));
    printf("\nI  --\t%.4X\nDT --\t%.2X\nST --\t%.2X\nPC --\t%.4X\n",
           get_I(), get_DT(), get_ST(), get_PC());
}
