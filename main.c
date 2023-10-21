#include <stdio.h>
#include "shell.h"

/**
 * free_data - frees data structure
 *
 * @datash: data structure
 * Return: no return
 */
void free_data(data_shell *datash)
{
	unsigned int i;

	for (i = 0; datash->_environ[i]; i++)
	{
		free(datash->_environ[i]);
	}

	free(datash->_environ);
	free(datash->pid);
}

/**
 * set_data - Initialize data structure
 *
 * @datash: data structure
 * @av: argument vector
 * Return: no return
 */
void set_data(data_shell *datash, char **av)
{
	unsigned int i;

	datash->av = av;
	datash->input = NULL;
	datash->args = NULL;
	datash->status = 0;
	datash->counter = 1;

	for (i = 0; environ[i]; i++)
		;

	datash->_environ = malloc(sizeof(char *) * (i + 1));

	for (i = 0; environ[i]; i++)
	{
		datash->_environ[i] = _strdup(environ[i]);
	}

	datash->_environ[i] = NULL;
	datash->pid = aux_itoa(getpid());
}

/**
* main - Entry point
* Return: datash.status
* @ac: Arg count
* @av: Arguments
*/

int main(int ac, char **av)
{
	char *buffer = NULL;
	size_t bufsize = 0;
	ssize_t chars;
	char full_path[256];
	data_shell datash;
	(void) ac;

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
	signal(SIGINT, get_sigint);
	set_data(&datash, av);
	shell_loop(&datash);
	free_data(&datash);
	if (datash.status < 0)
		return (255);
	return (datash.status);
g
