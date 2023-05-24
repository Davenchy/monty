#include "includes/monty.h"
#include <stdarg.h>
#include <stdlib.h>

context_t ctx;

/**
 * context_init - initialize the global context object
 */
void context_init(void)
{
	ctx.file = NULL;
	ctx.stack = NULL;
	ctx.line = NULL;
	ctx.cmd.opcode = NULL;
	ctx.cmd.arg = NULL;
	ctx.line_number = 0;
}

/**
 * context_destroy - destroy the global context object
 */
void context_destroy(void)
{
	if (ctx.file)
		fclose(ctx.file);
	/* if (ctx.stack) free stack */
	if (ctx.line)
		free(ctx.line);
}

/**
 * monty_exit_msg - end the interpreter with error message
 * @msg: the error message
 */
void monty_exit_msg(const char *msg)
{
	monty_destroy("L%lu: usage: %s\n", ctx.line_number, msg);
}

/**
 * monty_destroy - free memory show error message and exit
 * @format: the printf format
 */
void monty_destroy(const char *format, ...)
{
	va_list ap;

	va_start(ap, format);
	vfprintf(stderr, format, ap);
	va_end(ap);

	exit(EXIT_FAILURE);
}
