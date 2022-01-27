#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "bf.h"

int main(int argc, char** argv)
{
    bool looping = false;
    int opt;
    while ((opt = getopt(argc, argv, "r")) != -1) {
        switch(opt) {
        case 'r' :
            looping = true;
            break;
        default:
            printf("Pass a brainfuck program as an argument to have it computed. Use '-r' if you want to keep entering computations using the same tape once you've started the editor.");
        }
    }

    if (optind >= argc) {
        printf("You need to pass the brainfuck program as an argument, e.g.\n ./bfi '++++++++++++++++++.'\n"); 
        return 1;
    }

    printf("\nRunning brainfuck interpretation. Output is:\n");
    int returnCode = 0;
    
    // If we loop, stackp will hold the state of the 'tape.'
    int** stackp = malloc(sizeof(int*));
    *stackp = NULL;
    char* programOut = malloc(sizeof(char*));
    char* command = malloc(sizeof(char)*20000);
    strncpy(command, argv[optind], sizeof(command));
    bool notargv = false;
    do
    {
        returnCode = interpereter(command, &programOut, stackp);
        if (returnCode == 0)
        {
            printf(programOut);
        }
        else
        {
            printf("There was a problem executing the program.\n");
        }

        printf("\n");

        if (looping) {
            if (notargv) {
                free(command);
            } else {
                command = NULL;
            }

            printf(":");
            size_t len = 0;
            ssize_t nread;
            nread = getline(&command, &len, stdin);
            if (nread == -1)
            {
                perror("Error: Getting a command failed.");
                exit(0);
            }
            //remove the endline, which we don't want to execute
            command[strcspn(command, "\n")] = '\0';
        }

        notargv = true;
    }
    while (looping);

    exit(returnCode);
}
