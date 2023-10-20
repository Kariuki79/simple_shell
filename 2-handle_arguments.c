#include "shell.h"

/**
 * handle_command - Function that handles command line arguments
 * @buffer: char to a ptr
 */

void handle_command(char *buffer)
{
	char *token;
	char *args[101];
	int arg_count = 0;
	char full_path[256];

	token = strtok(buffer, " ");
	while (token != NULL)
	{
		args[arg_count] = token;
		arg_count++;
		token = strtok(NULL, " ");
	}

	args[arg_count] = NULL;

	if (find_executable_in_path(args[0], full_path, sizeof(full_path)))
	{
		args[0] = full_path;
		if (fork() == 0)
		{
			if (execve(args[0], args, NULL) == -1)
			{
				perror("Error");
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			wait(NULL);
		}
	}
	else
	{
		fprintf(stderr, "%s: No such file or directory\n", args[0]);
	}
}
