/*
swapper.c
*/

#include "swapper.h"

int buf[1024] = {1};

void swapper_v1(int *a, int *b)
{
    int local_a, local_b;

    local_a = *a;
    local_b = *b;
    
    *a = local_b;
    *b = local_a;
}