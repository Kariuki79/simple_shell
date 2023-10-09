#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * main - Entry point
 * Return: 0 SUCCESS
 */

int main(void)
{
	char *buffer = NULL;
	size_t bufsize = 0;
	ssize_t chars;

	while (1)
	{
		printf("$");
		chars = getline(&buffer, &bufsize, stdin);

		if (chars == -1)
		{
			if (isatty(STDIN_FILENO))
				printf("\n");
			free(buffer);
			exit(EXIT_SUCCESS);
		}

		buffer[chars - 1] = '\0';

		if (fork() == 0)
		{
			if (execve(buffer, NULL, NULL) == -1)
			{
				perror(buffer);
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			wait(NULL);
		}
	}

	return (0);
}
