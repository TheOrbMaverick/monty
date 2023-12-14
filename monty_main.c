#define _POSIX_C_SOURCE 200809L

#include "monty.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void process_file(const char *filename);
void execute_opcode(const char *opcode, stack_t **stack, unsigned int line_number);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "USAGE: monty file\n");
        return EXIT_FAILURE;
    }

    process_file(argv[1]);

    return EXIT_SUCCESS;
}

void process_file(const char *filename)
{
    char *line = NULL;
    size_t len = 0;
    unsigned int line_number = 0;
    stack_t *stack = NULL;
    char *opcode;
    char *arg;

    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        fprintf(stderr, "Error: Can't open file %s\n", filename);
        exit(EXIT_FAILURE);
    }

    while (getline(&line, &len, file) != -1)
    {
        line_number++;
        opcode = strtok(line, " \t\n$");  /* Include $ as a delimiter */

        if (opcode != NULL && *opcode != '#')
        {
            /* If push, get the argument and pass it to the push function */
            if (strcmp(opcode, "push") == 0)
            {
                arg = strtok(NULL, " \t\n$");
                if (arg == NULL || !is_int(arg))
                {
                    fprintf(stderr, "L%u: usage: push integer\n", line_number);
                    exit(EXIT_FAILURE);
                }

                execute_opcode(opcode, &stack, line_number);
            }
            else
            {
                execute_opcode(opcode, &stack, line_number);
            }
        }
    }

    free(line);
    fclose(file);
}

void execute_opcode(const char *opcode, stack_t **stack, unsigned int line_number)
{
    int i = 0;

    instruction_t instructions[] = {
        {"push", push},
        {"pall", pall},
	{"pint", pint},
        /* Add other opcode-function pairs as needed */
        {NULL, NULL} /* Terminator for the array */
    };

    while (instructions[i].opcode != NULL)
    {
        if (strcmp(opcode, instructions[i].opcode) == 0)
        {
            /* If push, get the argument and pass it to the push function */
            if (strcmp(opcode, "push") == 0)
            {
                char *arg = strtok(NULL, " \t\n$");
                if (arg == NULL || !is_int(arg))
                {
                    fprintf(stderr, "L%u: usage: push integer\n", line_number);
                    exit(EXIT_FAILURE);
                }

                instructions[i].f(stack, line_number);
            }
            else
            {
                instructions[i].f(stack, line_number);
            }

            return;
        }
        i++;
    }

    fprintf(stderr, "L%u: unknown instruction %s\n", line_number, opcode);
    exit(EXIT_FAILURE);
}
