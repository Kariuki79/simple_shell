#include "shell.h"

/**
 * _myenv - Display the current environment
 * @info: A structure containing potential arguments.
 * Return: Always 0
 */
int _myenv(info_t *info)
{
	print_environment(info->env);
	return (0);
}

/**
 * getenv_value - Get the value of an environment variable
 * @info: A structure containing potential arguments
 * @name: The name of the environment variable
 * Return: The value of the environment variable, or NULL
 * if not found
 */
char *getenv_value(info_t *info, const char *name)
{
	list_t *node = info->env;
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
 * mysetnv - set or modify an environment.
 * @info: A structure containing potential arguments.
 * Return: 1 on sucess, 0 on failure
 */
int mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("incorrect number of arguments.\n");
		return (0);
	}

/**
 * myunsetenv - Remove an environment variable.
 * @info: A structure containing potential arguments.
 * Return: 1 on success, 0 on failure.
 */
int myunsetenv(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_eputs("Too few arguments.\n");
		return (0);
	}
	for (i = 1; i <= info->argc; i++)
		unset_environment_variable(info, info->argv[i]);

	return (i);
}

/**
 * initialize_environment - Populate the environment linked list.
 * @info: A structure containing potential arguments.
 * Return: Always 0.
 */
int initialize_environment(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)

		add_node_end(&node, new_node, 0);
	info->env = node;

	return (0);
}
