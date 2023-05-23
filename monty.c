#include "includes/monty.h"
#include "includes/reader.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

__attribute__((noreturn)) void main_loop(FILE * file);

/**
 * main_loop - the main interpreter loop to read line by line and execute them
 * @file: the opend script file stream object
 */
void main_loop(FILE *file)
{
	char *line = NULL;
	ssize_t state = 0;

loop:
	fflush(stdout);
	state = readline(file, &line);
	if (state == T_EOF)
		goto end;
	if (state == T_ERR)
		goto err;
	if (T_HAS_DATA(state))
		printf("%s\n", line);
	if (line)
		free(line);
	goto loop;
end:
	fclose(file);
	exit(EXIT_SUCCESS);
err:
	fclose(file);
	fprintf(stderr, "Error: malloc failed\n");
	exit(EXIT_FAILURE);
}

/**
 * main - Monty language bytecodes interpreter
 * @argc: number of arguments
 * @argv: array of arguments
 * Return: exit status code
 */
int main(int argc, char **argv)
{
	FILE *file = NULL;
	char *filepath = NULL;

	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}

	filepath = argv[1];
	file = fopen(filepath, "r");
	if (!file)
	{
		fprintf(stderr, "Error: Can't open file %s\n", filepath);
		exit(EXIT_FAILURE);
	}

	main_loop(file);
}
