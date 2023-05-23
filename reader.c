#include "includes/reader.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

/**
 * skip_whitespaces - a util function to skip whitespaces while reading line
 * @file: pointer to the script file object
 * @c: the last character value
 * Return: the last modified character value
 */
char skip_whitespaces(FILE *file, char c)
{
	for (; c != -1 && c != 10 && isspace(c); c = fgetc(file))
		continue;
	return (c);
}

/**
 * readtoken - read the next token
 * @file: pointer to the script file object
 * @buffer: the temp buffer to read characters into
 * @c: the last character value
 * @size: pointer to the temp buffer size
 * @tsize: pointer to the token size
 * Return: the last modified character value
 */
char readtoken(FILE *file, char *buffer, char c, size_t *size, size_t *tsize)
{
loop:
	if (c == -1 || *size > BUFFER_SIZE || isspace(c))
		return (c);
	buffer[(*size)++] = c;
	c = fgetc(file);
	(*tsize)++;
	goto loop;
}

/**
 * readline - read the next script line from the script file
 * @file: pointer to the script file object
 * @line: pointer to the line variable
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
ssize_t readline(FILE *file, char **line)
{
	char buffer[BUFFER_SIZE], c = 0;
	size_t size = 0, opsize = 0, argsize = 0;

	if (!line)
		return (T_ERR);
	*line = NULL;

	c = fgetc(file);
	c = skip_whitespaces(file, c);
	c = readtoken(file, buffer, c, &size, &opsize);
	/* is empty line */
	if (!opsize && c != -1)
		return (T_EMPTY);

	/* EOF */
	if (c == -1)
		return (T_EOF);

	c = skip_whitespaces(file, c);
	c = readtoken(file, buffer, c, &size, &argsize);

	/* allocate token */
	size = opsize + argsize + (argsize ? 2 : 1);
	*line = malloc(sizeof(char) * size);
	if (!*line)
		return (T_ERR);
	(*line)[size] = 0;

	/* copy bytes */
	memcpy(*line, buffer, opsize);
	if (argsize)
	{
		(*line)[opsize] = ' ';
		memcpy((*line) + opsize + 1, buffer + opsize, argsize);
	}

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
	if (!line)
		return (0);
	cmd->opcode = strtok(line, " ");
	if (cmd->opcode)
		cmd->arg = strtok(NULL, " ");
	return (1);
}
