#include "monty.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void process_file(const char *filename);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("USAGE: monty file");
        return EXIT_FAILURE;
    }

    process_file(argv[1]);

    return EXIT_SUCCESS;
}

void process_file(const char *filename)
{
    unsigned int line_number = 0;
    char line[256];
    char *opcode;
    char *arg;
    unsigned int global_arg;
    int i = 0;

    stack_t *stack = NULL;

    instruction_t instructions[] = {
        {"push", push},
        {"pall", pall},
        {"pop", pop},
        {"swap", swap},
        {"add", add},
        {"nop", nop}, /* Add the nop opcode */
        /* Add other opcode-function pairs as needed */
        {NULL, NULL} /* Terminator for the array */
    };

    FILE *file = fopen(filename, "r");

    if (file == NULL)
    {
        fprintf(stderr, "Error: Can't open file %s\n", filename);
        exit(EXIT_FAILURE);
    }

    while (fgets(line, sizeof(line), file))
    {
        line_number++;

        opcode = strtok(line, " \t\n$");

        if (opcode != NULL)
        {
            arg = strtok(NULL, " \t\n$");

            if (arg == NULL || !is_int(arg))
            {
                fprintf(stderr, "L%u: usage: push integer\n", line_number);
                exit(EXIT_FAILURE);
            }

            global_arg = atoi(arg);

            while (instructions[i].opcode != NULL && strcmp(opcode, instructions[i].opcode) != 0)
            {
                i++;
            }

            if (instructions[i].opcode != NULL)
            {
                if (strcmp(instructions[i].opcode, "push") == 0)
                {
                    /* For "push," call the push function */
                    instructions[i].f(&stack, global_arg);
                }
                else
                {
                    /* For other instructions, call the corresponding function */
                    instructions[i].f(&stack, line_number);
                }
            }
            else
            {
                fprintf(stderr, "L%u: unknown instruction %s\n", line_number, opcode);
                exit(EXIT_FAILURE);
            }
        }
    }

    fclose(file); /* Close the file after processing */
}
