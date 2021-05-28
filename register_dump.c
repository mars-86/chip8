#include "registers.h"
#include <stdio.h>

void print_registers(void)
{
    int i;
    printf("\nVx --\t");
    for (i = 0; i < Vx_REGISTER_LENGTH; ++i) printf("%.2d | ", i);
    printf("\n\t");
    for (i = 0; i < Vx_REGISTER_LENGTH; ++i) printf("%.2X | ", get_Vx(i));
    printf("\nI  --\t%.4X\nDT --\t%.2X\nST --\t%.2X\nPC --\t%.4X\n",
           get_I(), get_DT(), get_ST(), get_PC());
}

void print_stack(void)
{
    unsigned short *stack = get_stack_top(), i;
    printf("\nStk --\t");
    for (i = 0; i < STACK_LENGTH; ++i) printf("%.2d   | ", i);
    printf("\n\t");
    for (i = 0; i < STACK_LENGTH; ++i) printf("%.4X | ", stack[i]);
}

void reg_dump(void)
{
    print_registers();
    print_stack();
}
