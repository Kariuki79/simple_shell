#include "holberton.h"

/**
 * free_data - frees data structure
 *
 * @data_struct: data structure
 * Return: no return
 */
void free_data(data_shell *data_struct)
{
	unsigned int index;

	for (index = 0; data_struct->_environ[index]; index++)
	{
		free(data_struct->_environ[index]);
	}

	free(data_struct->_environ);
	free(data_struct->pid);
}

/**
 * set_data - Initialize data structure
 *
 * @data_struct: data structure
 * @arg_v: argument vector
 * Return: no return
 */
void set_data(data_shell *data_struct, char **arg_v)
{
	unsigned int index;

	data_struct->arg_v = arg_v;
	data_struct->input = NULL;
	data_struct->args = NULL;
	data_struct->status = 0;
	data_struct->counter = 1;

	for (index = 0; environ[index]; index++)
		;

	datash->_environ = malloc(sizeof(char *) * (index + 1));

	for (index = 0; environ[index]; index++)
	{
		data_struct->_environ[index] = _strdup(environ[index]);
	}

	data_struct->_environ[index] = NULL;
	data_struct->pid = aux_itoa(getpid());
}

/**
 * main - Entry point
 *
 * @arg_c: argument count
 * @arg_v: argument vector
 *
 * Return: 0 on success.
 */
int main(int arg_c, char **arg_v)
{
	data_shell data_struct;
	(void) arg_c;

	signal(SIGINT, get_sigint);
	set_data(&data_struct, arg_v);
	shell_loop(&data_struct);
	free_data(&data_struct);
	if (data_struct.status < 0)
		return (255);
	return (data_struct.status);
}
