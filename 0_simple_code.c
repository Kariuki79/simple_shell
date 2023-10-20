#include <stdio.h>
#include "shell.h"

/**
* main - Entry point
* Return: 0 if successful
*/

int main(void)
{
	char *buffer = NULL;
	size_t bufsize = 0;
	ssize_t chars;
	char full_path[256];

	while (1)
	{
		printf("$ ");
		chars = getline(&buffer, &bufsize, stdin);

		if (chars == -1)
		{
			if (isatty(STDIN_FILENO))
				printf("\n");
			free(buffer);
			exit(EXIT_SUCCESS);
		}

		buffer[chars - 1] = '\0';

		if (find_executable_in_path(buffer, full_path, sizeof(full_path)))
		{
			printf("Executable found at: %s\n", full_path);

			handle_command(buffer);
		}
		else
		{
			fprintf(stderr, "%s: command not found\n", buffer);
		}
	}
	return (0);
}
