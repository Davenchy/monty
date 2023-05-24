#include "includes/monty.h"
#include "includes/opcodes.h"
#include <stdlib.h>

/**
 * add_opcode - adds the top most two elements of the stack
 * @stack: pointer to the stack head
 * @line_number: the current line number
 */
void add_opcode(stack_t **stack, unsigned int UNUSE line_number)
{
	stack_t *a, *b;

	a = stack_pop(stack);
	b = stack_top(stack);
	if (!a || !b)
		monty_exit_msg("can't add, stack too short");
	b->n += a->n;
	free(a);
}

/**
 * nop_opcode - do no thing
 * @stack: pointer to the stack head
 * @line_number: the current line number
 */
void nop_opcode(UNUSE stack_t **stack, unsigned int UNUSE line_number)
{}
