#include "monty.h"
#include <stdio.h>
#include <stdlib.h>

void sub(stack_t **stack, unsigned int line_number)
{
    if (*stack == NULL || (*stack)->next == NULL)
    {
        fprintf(stderr, "L%u: can't sub, stack too short\n", line_number);
        exit(EXIT_FAILURE);
    }

    (*stack)->next->n -= (*stack)->n;

    pop(stack, line_number); /* Remove the top element */
}
