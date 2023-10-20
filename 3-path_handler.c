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
	char *token = strtok(path, ":");
	struct stat st;

	if (path == NULL)
	{
		fprintf(stderr, "Error: PATH environment variable not set\n");
		return (0);
	}

	while (token != NULL)
	{
		snprintf(full_path, max_length, "%s/%s", token, command);

		if (stat(full_path, &st) == 0)
		{
			return (1);
		}

		token = strtok(NULL, ":");
	}
	return (0);
}

