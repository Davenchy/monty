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
	CTX_DEC;
	int i, len;
	instruction_t instructions[] = {
		{ "push", push_opcode }, { "pall", pall_opcode },
		{ NULL, NULL },
	};

	parse_line(CTX_LINE, &CTX_CMD);
	len = strlen(CTX_CMD.opcode);
	for (i = 0; instructions[i].opcode; i++)
		if (!strncmp(instructions[i].opcode, CTX_CMD.opcode, len))
		{
			instructions[i].f(&ctx->stack, ctx->line_number);
			return;
		}

	monty_destroy("L%lu: unknown instruction %s\n",
							 ctx->line_number, CTX_CMD.opcode);
}

/**
 * main_loop - the main interpreter loop to read line by line and execute them
 * Return: status code
 */
int main_loop(void)
{
	CTX_DEC;
	ssize_t state = 0;

loop:
	fflush(stdout);
	state = readline();
	if (state == T_EOF)
		goto end;
	if (state == T_ERR)
		monty_exit_msg("Error: malloc failed\n");
	if (T_HAS_DATA(state))
		runner();
	if (CTX_LINE)
	{
		free(CTX_LINE);
		CTX_LINE = NULL;
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
	context_t *ctx;
	int state = EXIT_SUCCESS;

	if (!context_init())
	{
		fprintf(stderr, "Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}
	ctx = CTX_LOAD;

	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}

	filepath = argv[1];
	CTX_FILE = fopen(filepath, "r");
	if (!CTX_FILE)
	{
		fprintf(stderr, "Error: Can't open file %s\n", filepath);
		exit(EXIT_FAILURE);
	}

	state = main_loop();
	context_destroy();
	return (state);
}
