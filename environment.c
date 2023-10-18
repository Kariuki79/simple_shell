#include "shell.h"

/**
 * _myenv - Display the current environment
 * @threshold: A structure containing potential arguments.
 * Return: Always 0
 */
int _myenv(info_t *threshold)
{
	print_list_str(threshold->env);
	return (0);
}

/**
 * getenv_value - Get the value of an environment variable by its name
 * @threshold: A structure containing potential arguments
 * and environment information
 * @name: The name of the environment variable to retrieve
 * Return: The value of the environment variable, or NULL
 * if not found
 */
char *getenv(info_t *threshold, const char *name)
{
	list_t *node = threshold->env;
	char *value;

	while (node)
	{
		value = starts_with(node->str, name);
		if (value && *value)
			return (value);
		node = node->next;
	}
	return (NULL);
}

/**
 * mysetenv - set or modify an environment.
 * @threshold: A structure containing potential
 * arguments and environment information.
 * Return: 1 on sucess, 0 on failure
 */
int mysetenv(info_t *threshold)
{
	if (threshold->argc != 3)
	{
		_eputs("incorrect number of arguments.\n");
		return (1);
	}
	if (_setenv(threshold, threshold->argv[1], threshold->argv[2]))
		return (0);
	return (1);

/**
 * _myunsetenv - Remove an environment variable.
 * @threshold: A structure containing potential arguments.
 * Return: 1 on success, 0 on failure.
 */
int _myunsetenv(info_t *threshold)
{
	int index;

	if (threshold->argc == 1)
	{
		_eputs("Too few arguments.\n");
		return (1);
	}
	for (index = 1; index <= threshold->argc; index++)
		_unsetenv(threshold, threshold->argv[index]);

	return (0);
}

/**
 * populate_env_list - Populate the environment linked list.
 * @threshold: A structure containing potential arguments.
 * Return: Always 0.
 */
int populate_env_list(info_t *threshold)
{
	list_t *node = NULL;
	size_t index;

	for (index = 0; environ[index]; index++)

		add_node_end(&node, environ[index], 0);
	threshold->env = node;

	return (0);
}
