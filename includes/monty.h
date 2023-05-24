#ifndef __MONTY_H__
#define __MONTY_H__

#include "reader.h"
#include "stack.h"
#include <stdio.h>

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

extern context_t ctx;

void context_init(void);
void context_destroy(void);
void monty_exit_msg(const char *msg);
/**
 * monty_destroy - free memory show error message and exit
 * @format: the printf format
 */
extern void monty_destroy(const char *format, ...)
	__attribute__((noreturn, format(printf, 1, 2)));

#endif
