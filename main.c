#include <stdio.h>
#include <stdlib.h>

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

	puts("Hello World");
	fclose(file);
	return (EXIT_SUCCESS);
}
