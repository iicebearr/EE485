#include <stdio.h>
#include "swapper.h"

#define MAX_STR 20

int main(int argc, char *argv[])
{
    int a, b;
    char name[MAX_STR];

    printf("Please enter two numbers: ");
    scanf("%d %d", &a, &b);

    swapper_v1(&a,&b);

    printf("Swapping is completed. What's your name? ");
    scanf("%19s", name);

    printf("Ok, %s. Good job!\n", name);
    
    return 0;
}