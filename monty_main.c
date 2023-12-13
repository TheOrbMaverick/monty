#include "monty.h"
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    stack_t *stack = NULL; /* Initialize an empty stack */

    /* Example usage: push 1, push 2, push 3, pall */
    push(&stack, 1);
    push(&stack, 2);
    push(&stack, 3);
    pall(&stack, 1); /* The line number here is just a placeholder, replace it with the actual line number */

    /* Clean up the stack if needed */

    return (0);
}
