#define increment '+'
#define decrement '-'
#define shiftl '<'
#define shiftr '>'
#define print '.'
#define jumpForward '['
#define jumpBack ']'

typedef struct
{
    void* previous;
    int location;
} stackEntry;

void interpereter(char* program)
{
    int* stack = malloc(sizeof(int)*4096);
    int stackLocation = 0;
    stackEntry* bracketStack = NULL;
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
            case print:
                printf("%c", (char)stack[stackLocation]);
                break;
            case jumpBack:
            {
                int breakEarly = 0;
                if (stack[stackLocation] != 0)
                {
                    breakEarly = 1;
                    if (bracketStack == NULL)
                    {
                        printf("unmatched ']' at index %d.\n", programPointer);
                        return;
                    }

                    programPointer = bracketStack->location;
                }

                if (!breakEarly) bracketStack = bracketStack->previous;
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
               printf("junk character '%c' in program at index '%d. Quitting. \n'", program[programPointer], programPointer);
               return;
        }
    }
}
