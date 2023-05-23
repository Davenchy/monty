#ifndef __READER_H__
#define __READER_H__

#include <stdio.h>
#include <sys/types.h>

#define BUFFER_SIZE 20
#define T_EMPTY 0
#define T_EOF -1
#define T_ERR -2
#define T_HAS_DATA(state) ((state) > 0)

/**
 * struct command_s - the command line sections
 * @opcode: the opcode value
 * @arg: the opcode argument value if exist
 */
typedef struct command_s
{
	char *opcode, *arg;
} command_t;

ssize_t readline(FILE *file, char **line);
int parse_line(char *line, command_t *cmd);

#endif
