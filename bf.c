#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bf.h"

int main(int argc, char** argv)
{
    printf("\nRunning brainfuck interpretation. Output is:\n");
    interpereter(argv[1]);
    exit(0);
}
