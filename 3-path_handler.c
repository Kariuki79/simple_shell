#include "shell.h"

/**
 * find_executable_in_path - Find the full path of the executable in the PATH
 * @command: The command to find
 * @full_path: Output parameter for the full path of the executable
 * @max_length: The maximum length of the full_path buffer
 * Return: 1 if found, 0 otherwise
 */
int find_executable_in_path(const char *command, char *full_path,
		size_t max_length)
{
	char *path = getenv("PATH");
	char *token;

	if (command[0] == '/')
	{
		snprintf(full_path, max_length, "%s", command);
		return (access(full_path, X_OK) == 0);
	}

	if (path == NULL)
	{
		fprintf(stderr, "Error: PATH environment variable not set\n");
		return (0);
	}

	token = strtok(path, ":");

	while (token != NULL)
	{
		snprintf(full_path, max_length, "%s/%s", token, command);

		if (access(full_path, X_OK) == 0)
		{
			return (1);
		}

		token = strtok(NULL, ":");
	}
	return (0);
}

