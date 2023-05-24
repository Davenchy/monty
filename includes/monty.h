#ifndef __MONTY_H__
#define __MONTY_H__

#include "reader.h"
#include "stack.h"
#include <stdio.h>

#define CTX_LOAD context_control(NULL, A_GET)
#define CTX_SET(ctx) context_control(ctx, A_SET)
#define CTX_DEC context_t *ctx = CTX_LOAD

#define CTX_FILE (ctx->file)
#define CTX_LINE (ctx->line)
#define CTX_CMD (ctx->cmd)

/**
 * enum action_e - the action to control the context storage
 * @A_GET: get the stored context object
 * @A_SET: set a context object
 */
typedef enum action_e
{ A_GET, A_SET } action_t;

/**
 * struct context_s - object that holds the state of the interpreter
 * @file: the currently opend file stream object
 * @cmd: the command params
 * @stack: the current stack state
 * @line: the readed line from the file
 * @line_number: the current line number in the script file
 */
typedef struct context_s
{
	FILE *file;
	command_t cmd;
	stack_t *stack;
	char *line;
	size_t line_number;
} context_t;

int context_init(void);
void context_destroy(void);
context_t *context_control(context_t *ctx, action_t action);
void monty_exit_msg(const char *msg);
/**
 * monty_destroy - free memory show error message and exit
 * @format: the printf format
 */
extern void monty_destroy(const char *format, ...)
	__attribute__((noreturn, format(printf, 1, 2)));

#endif
