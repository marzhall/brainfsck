#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define increment '+'
#define decrement '-'
#define shiftl '<'
#define shiftr '>'
#define print '.'
#define jumpForward '['
#define jumpBack ']'
#define grabInput ','

typedef struct
{
    void* previous;
    int location;
} stackEntry;

typedef struct
{
    void* previous;
    char content;
    int count;
} output;

void freeStack(void* stack, char type)
{
    if (stack == NULL)
    {
        return;
    }
    
    switch (type)
    {
        case 'o':
            while (stack != NULL)
            {
                output* tempOutput = (output*)stack;
                stack = tempOutput->previous;
                free(tempOutput);
            }
        case 's':
            while (stack != NULL)
            {
                stackEntry* tempOutput = (stackEntry*)stack;
                stack = tempOutput->previous;
                free(tempOutput);
            }
    }

}

int interpereter(char* program, char** result)
{
    if (program == NULL)
    {
        printf("Null program argument supplied to the interpereter.");
        return 1;
    }
    if (!strcmp(program, ""))
    {
        printf("[Interpreter's note: Input was empty]");
        return 0;
    }

    int* stack = malloc(sizeof(int)*4096);
    int stackLocation = 0;
    stackEntry* bracketStack = NULL;
    output* outputStack = NULL;
    for (int programPointer = 0; programPointer < strlen(program); programPointer++)
    {
        switch (program[programPointer])
        {
            case increment:
                stack[stackLocation]++;
                break;
            case decrement:
                stack[stackLocation]--;
                break;
            case shiftl:
                stackLocation--;
                break;
            case shiftr:
                stackLocation++;
                break;
            case grabInput:
            {
                printf("[PROMPT] Enter a number or a character. In order to input a single-digit number as a character, type a period first, e.g. '.1'\n");
                int x;
                if (!scanf("%d", &x))
                {
                    char y;
                    if (!scanf(".%c", &y))
                    {
                        scanf("%c", &y);
                    }

                    stack[stackLocation] = (int)y;
                }
                else
                {
                    stack[stackLocation] = x;
                }

            }
                break;
            case print:
            {
                output* newOutput = malloc(sizeof(output));
                newOutput->previous = outputStack;
                newOutput->content = (char)stack[stackLocation];
                if (outputStack == NULL)
                {
                    newOutput->count = 1;
                }
                else
                {
                    newOutput->count = outputStack->count + 1;
                }

                outputStack = newOutput;
                break;
            }
            case jumpBack:
            {
                int breakEarly = 0;
                if (stack[stackLocation] != 0)
                {
                    breakEarly = 1;
                    if (bracketStack == NULL)
                    {
                        printf("unmatched ']' at index %d.\n", programPointer);
                        return 1;
                    }

                    programPointer = bracketStack->location;
                }

                if (!breakEarly)
                {
                    stackEntry* temp = bracketStack;
                    bracketStack = bracketStack->previous;
                    free(temp);
                }
            }

                break;
            case jumpForward:
            {
                stackEntry* newStackEntry = malloc(sizeof(stackEntry));
                newStackEntry->previous = bracketStack;
                newStackEntry->location = programPointer;
                bracketStack = newStackEntry;
                if (stack[stackLocation] == 0)
                {
                    int bracketCounter = 1;
                    int searchPointer = 1;
                    while (bracketCounter !=0)
                    {
                        if (program[programPointer + searchPointer] == jumpBack)
                        {
                            bracketCounter--;
                        }
                        if (program[programPointer + searchPointer] == jumpForward)
                        {
                            bracketCounter++;
                        }

                        searchPointer++;
                    }
                }
                break;
            }
            default:
               printf("junk character '%c' at index '%d. Quitting. \n", program[programPointer], programPointer);
               freeStack(bracketStack, 's');
               freeStack(outputStack, 'o');
               return 1;
        }
    }

    if (outputStack == NULL)
    {
        return 0;
    }

    // transcribe the outputs to a string in reverse order, starting from the latest output
    *result = malloc(sizeof(char)*(outputStack->count + 1));
    (*result)[outputStack->count] = '\0';
    void* oldHead = outputStack;
    while (outputStack != NULL)
    {
        (*result)[outputStack->count - 1] = outputStack->content;
        outputStack = outputStack->previous;
    }

    freeStack(oldHead, 'o');
    return 0;
}

