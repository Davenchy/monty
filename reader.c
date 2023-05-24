#include "includes/reader.h"
#include "includes/monty.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

/**
 * skip_whitespaces - a util function to skip whitespaces while reading line
 * @c: the last character value
 * Return: the last modified character value
 */
char skip_whitespaces(char c)
{
	CTX_DEC;

	for (; c != -1 && c != 10 && c != '#' && isspace(c); c = fgetc(CTX_FILE))
		continue;
	if (c == '#')
		for (; c != -1 && c != 10; c = fgetc(CTX_FILE))
			continue;
	return (c);
}

/**
 * readtoken - read the next token
 * @buffer: the temp buffer to read characters into
 * @c: the last character value
 * @size: pointer to the temp buffer size
 * @tsize: pointer to the token size
 * Return: the last modified character value
 */
char readtoken(char *buffer, char c, size_t *size, size_t *tsize)
{
	CTX_DEC;

loop:
	if (c == -1 || c == '#' || *size > BUFFER_SIZE || isspace(c))
		return (c);
	buffer[(*size)++] = c;
	c = fgetc(CTX_FILE);
	(*tsize)++;
	goto loop;
}

/**
 * readline - read the next script line from the script file
 *
 * Description:
 * resetting lineptr value to NULL so make sure to free memory before call
 * if any allocated.
 *
 * returns pointer to allocated cstring
 * that has the next format `opcode[ arg]`.
 *
 * Return: the size of the line or T_ERR on error T_EMPTY on empty line T_EOF
 * on end of file
 */
ssize_t readline(void)
{
	CTX_DEC;
	char buffer[BUFFER_SIZE], c = 0;
	size_t size = 0, opsize = 0, argsize = 0;

	CTX_LINE = NULL;
loop:
	if (c == 10)
		ctx->line_number++;
	c = fgetc(CTX_FILE);
	c = skip_whitespaces(c);
	c = readtoken(buffer, c, &size, &opsize);
	/* is empty line */
	if (!opsize && c != -1)
		goto loop;

	/* EOF */
	if (c == -1)
		return (T_EOF);

	c = skip_whitespaces(c);
	c = readtoken(buffer, c, &size, &argsize);

	/* allocate token */
	size = opsize + argsize + (argsize ? 1 : 0);
	CTX_LINE = malloc(size);
	if (!CTX_LINE)
		return (T_ERR);
	CTX_LINE[size] = 0;

	/* copy bytes */
	memcpy(CTX_LINE, buffer, opsize);
	if (argsize)
	{
		CTX_LINE[opsize] = ' ';
		memcpy(CTX_LINE + opsize + 1, buffer + opsize, argsize);
	}

	ctx->line_number++;
	return (size);
}

/**
 * parse_line - parse command line into tokens
 * @line: the command line cstring
 * @cmd: the command object to fill with tokens
 * Return: 1 on success and 0 on fail
 */
int parse_line(char *line, command_t *cmd)
{
	cmd->opcode = NULL;
	cmd->arg = NULL;
	cmd->value = 0;
	if (!line)
		return (0);

	cmd->opcode = strtok(line, " ");
	if (cmd->opcode)
		cmd->arg = strtok(NULL, " ");
	if (cmd->arg && is_digit(cmd->arg))
	{
		if (cmd->arg[0] == '-')
			cmd->value = -(atoi(cmd->arg + 1));
		else
			cmd->value = atoi(cmd->arg);
	}
	else
		cmd->arg = NULL;
	return (1);
}

/**
 * is_digit - check if the cstring is a digit written in ascii form
 * @arg: the cstring
 * Return: 1 if true else 0
 */
int is_digit(char *arg)
{
	if (!arg)
		return (0);
	if (*arg == '-')
		arg++;
	for (; *arg; arg++)
		if (!isdigit(*arg))
			return (0);
	return (1);
}
