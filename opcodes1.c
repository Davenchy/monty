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
	int value;

	if (!stack)
		return;

	if (!ctx.cmd.arg || !is_digit(ctx.cmd.arg))
		monty_exit_msg("push integer");

	value = atoi(ctx.cmd.arg);
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
