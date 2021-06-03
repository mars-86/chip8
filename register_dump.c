#include "registers.h"
#include <stdio.h>

void print_registers(void)
{
    int i;
    unsigned short *stack = get_stack_top();
    printf("\nVx --\t");
    for (i = 0; i < Vx_REGISTER_LENGTH; ++i) printf("%.2d   | ", i);
    printf("\n\t");
    for (i = 0; i < Vx_REGISTER_LENGTH; ++i) printf("%.2X   | ", get_Vx(i));
    printf("\nStk --\t");
    for (i = 0; i < STACK_LENGTH; ++i) printf("%.4X | ", stack[i]);
    printf("\nI  --\t%.4X\tDT --\t%.2X\tST --\t%.2X\tPC --\t%.4X\n\n",
           get_I(), get_DT(), get_ST(), get_PC());
}

void reg_dump(void)
{
    print_registers();
}
