#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bf.h"

int main(int argc, char** argv)
{
    if (argc == 1)
    {
        printf("You need to pass the brainfuck program as an argument, e.g.\n ./bfi '++++++++++++++++++.'\n"); 
        return 1;
    }

    printf("\nRunning brainfuck interpretation. Output is:\n");
    interpereter(argv[1]);
    exit(0);
}
