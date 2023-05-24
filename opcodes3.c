#include "includes/monty.h"
#include "includes/opcodes.h"
#include <ctype.h>
#include <stdlib.h>

/**
 * pchar_opcode - print character form the ascii table
 * @stack: pointer to the stack head
 * @line_number: the current line number
 */
void pchar_opcode(stack_t **stack, unsigned int UNUSE line_number)
{
	stack_t *a;

	a = stack_pop(stack);
	if (!a)
		monty_exit_msg("can't pchar, stack empty");
	if (a->n < 0 || a->n >= 128)
	{
		free(a);
		monty_exit_msg("can't pchar, value out of range");
	}
	printf("%c", a->n);
	free(a);
}

/**
 * pstr_opcode - print strings using characters from the ascii table
 * @stack: pointer to the stack head
 * @line_number: the current line number
 *
 * Description:
 * The string ends with \0 character
 * or with character out of range or empty stack.
 */
void pstr_opcode(stack_t **stack, unsigned int UNUSE line_number)
{
	stack_t *a;

	for (a = stack_pop(stack); a; a = stack_pop(stack))
	{
		if (a->n <= 0 || a->n >= 128)
		{
			free(a);
			break;
		}
		printf("%c", a->n);
		free(a);
	}
	putchar(10);
}


/**
 * rotl_opcode - rotates the stack to the top
 * @stack: pointer to the stack head
 * @line_number: the current line number
 */
void rotl_opcode(stack_t **stack, unsigned int UNUSE line_number)
{
	stack_t *t, *h;

	t = stack_top(stack);
	h = *stack;

	if (!t || t == h)
		return;

	t->next = h;
	t->prev->next = NULL;
	t->prev = NULL;
	h->prev = t;
	*stack = t;
}

/**
 * rotr_opcode - rotates the stack to the bottom
 * @stack: pointer to the stack head
 * @line_number: the current line number
 */
void rotr_opcode(stack_t **stack, unsigned int UNUSE line_number)
{
	stack_t *t, *h;

	t = stack_top(stack);
	h = *stack;

	if (!t || t == h)
		return;

	t->next = h;
	h->prev = t;
	h->next->prev = NULL;
	*stack = h->next;
	h->next = NULL;
}

/**
 * nop_opcode - do no thing
 * @stack: pointer to the stack head
 * @line_number: the current line number
 */
void nop_opcode(UNUSE stack_t **stack, unsigned int UNUSE line_number)
{}
