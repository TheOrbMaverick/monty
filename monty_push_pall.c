#include "monty.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stddef.h>

/**
 * push - Pushes an element to the stack.
 * @stack: Double pointer to the beginning of the stack.
 * @value: The value to be pushed onto the stack.
 */

void push(stack_t **stack, unsigned int line_number)
{
    stack_t *new_node = NULL;

    new_node = (stack_t *)malloc(sizeof(stack_t));
    if (new_node == NULL)
    {
        fprintf(stderr, "Error: malloc failed\n");
        exit(EXIT_FAILURE);
    }

    new_node->n = line_number;
    new_node->prev = NULL;
    new_node->next = *stack;

    if (*stack != NULL)
    {
        (*stack)->prev = new_node;
    }

    *stack = new_node;
}

/**
 * pall - Prints all the values on the stack.
 * @stack: Double pointer to the beginning of the stack.
 * @line_number: Line number in the file where the opcode appears.
 */
void pall(stack_t **stack, unsigned int line_number)
{
    stack_t *current = NULL;
    (void)line_number; /* Unused parameter */

    current = *stack;

    while (current != NULL)
    {
        printf("%d\n", current->n);
        current = current->next;
    }
}

/**
 * is_int - Checks if a string is a valid integer.
 * @str: String to be checked.
 * Return: 1 if the string is a valid integer, 0 otherwise.
 */
int is_int(const char *str)
{
    if (*str == '-')
        str++;

    while (*str)
    {
        if (!isdigit((unsigned char)*str))
            return 0;
        str++;
    }

    return 1;
}
