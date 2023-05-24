#include "includes/monty.h"
#include "includes/opcodes.h"
#include "includes/reader.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * push_opcode - push value to the stack
 * @stack: pointer to the stack head
 * @line_number: the current line number
 */
void push_opcode(stack_t **stack, unsigned int UNUSE line_number)
{
	CTX_DEC;
	int value;

	if (!stack)
		return;

	if (!CTX_CMD.arg || !is_digit(CTX_CMD.arg))
		monty_exit_msg("usage: push integer");

	value = atoi(CTX_CMD.arg);
	stack_push(stack, value);
}

/**
 * pall_opcode - print all values in the stack from top to bottom
 * @stack: pointer to the stack head
 * @line_number: the current line number
 */
void pall_opcode(stack_t **stack, unsigned int UNUSE line_number)
{
	stack_t *curr;

	if (!stack)
		return;

	for (curr = stack_top(stack); curr; curr = curr->prev)
		printf("%d\n", curr->n);
}

/**
 * pint_opcode - print the value at the top of the stack
 * @stack: pointer to the stack head
 * @line_number: the current line number
 */
void pint_opcode(stack_t **stack, unsigned int UNUSE line_number)
{
	stack_t *curr;

	curr = stack_top(stack);
	if (curr)
		printf("%d\n", curr->n);
	else
		monty_exit_msg("can't pint, stack empty");
}
