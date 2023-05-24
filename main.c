#include "includes/monty.h"
#include "includes/opcodes.h"
#include "includes/reader.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

/**
 * runner - the core function to execute opcodes
 */
void runner(void)
{
	int i, len;
	instruction_t instructions[] = {
		{ "push", push_opcode }, { "pall", pall_opcode },
		{ NULL, NULL },
	};

	parse_line(ctx.line, &ctx.cmd);
	len = strlen(ctx.cmd.opcode);
	for (i = 0; instructions[i].opcode; i++)
		if (!strncmp(instructions[i].opcode, ctx.cmd.opcode, len))
		{
			instructions[i].f(&ctx.stack, ctx.line_number);
			return;
		}

	monty_destroy("L%lu: unknown instruction %s\n",
							 ctx.line_number, ctx.cmd.opcode);
}

/**
 * main_loop - the main interpreter loop to read line by line and execute them
 * Return: status code
 */
int main_loop(void)
{
	ssize_t state = 0;

loop:
	fflush(stdout);
	state = readline();
	if (state == T_EOF)
		goto end;
	if (state == T_ERR)
	{
		fprintf(stderr, "Error: malloc failed\n");
		return (EXIT_FAILURE);
	}
	if (T_HAS_DATA(state))
		runner();
	if (ctx.line)
	{
		free(ctx.line);
		ctx.line = NULL;
	}
	goto loop;
end:
	return (EXIT_SUCCESS);
}

/**
 * main - Monty language bytecodes interpreter
 * @argc: number of arguments
 * @argv: array of arguments
 * Return: exit status code
 */
int main(int argc, char **argv)
{
	char *filepath = NULL;
	int state = EXIT_SUCCESS;

	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}

	filepath = argv[1];
	context_init();
	ctx.file = fopen(filepath, "r");
	if (!ctx.file)
	{
		fprintf(stderr, "Error: Can't open file %s\n", filepath);
		exit(EXIT_FAILURE);
	}

	state = main_loop();
	context_destroy();
	return (state);
}
