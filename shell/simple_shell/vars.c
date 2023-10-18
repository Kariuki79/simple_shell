#include "shell.h"

/**
 * is_chain - test if the current character in the buffer is a chain delimiter
 * @config: The parameter struct
 * @buffer: The character buffer
 * @previous: Address of the current position in buf
 *
 * Return: 1 if it's a chain delimiter, 0 otherwise
 */
int is_chain(info_t *config, char *buffer, size_t *previous)
{
	size_t value = *previous;

	if (buffer[value] == '|' && buffer[value + 1] == '|')
	{
		buffer[value] = 0;
		value++;
		config->cmd_buf_type = CMD_OR;
	}

	else if (buffer[value] == '&' && buffer[value + 1] == '&')
	{
		buffer[value] = 0;
		value++;
		config->cmd_buf_type = CMD_AND;
	}

	else if (buffer[value] == ';')
	{
		buffer[value] = 0;
		config->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*previous = value;
	return (1);
}
/**
 * check_chain - checks if we should continue chaining
 * based on the last status
 *
 * @config: The parameter struct
 * @buffer: The character buffer
 * @prev: Address of the current position in buffer
 * @index: Starting position in buffer
 * @length: Length of buffer
 *
 * Return: Void
 */
void check_chain(info_t *config,
		char *buffer,
		size_t *prev,
		size_t index,
		size_t length)
{
	size_t value = *prev;

	if (config->cmd_buf_type == CMD_AND)
	{
		if (config->status)
		{
			buffer[index] = 0;
			value = length;
		}
	}
	if (config->cmd_buf_type == CMD_OR)
	{
		if (!config->status)
		{
			buffer[index] = 0;
			value = length;
		}
	}

	*prev = value;
}

/**
 * replace_alias - replaces alias in the tokenized string
 * @config: The parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias(info_t *config)
{
	int index;
	list_t *node;
	char *prev;

	for (index = 0; index < 10; index++)
	{
		node = node_starts_with(config->alias, config->argv[0], '=');

		if (!node)
			return (0);
		free(config->argv[0]);
		prev = _strchr(node->str, '=');

		if (!prev)
			return (0);
		prev = _strdup(prev + 1);

		if (!prev)
			return (0);
		config->argv[0] = prev;
	}

	return (1);
}

/**
 * replace_vars - replaces variables in the tokenized string
 * @config: The parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_vars(info_t *config)
{
	int index = 0;
	list_t *node;

	for (index = 0; config->argv[index]; index++)
	{
		if (config->argv[index][0] != '$' || !config->argv[index][1])
			continue;

		if (!_strcmp(config->argv[index], "$$?"))
		{
			replace_string(&(info->argv[index]),
					_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}

		if (!_strcmp(info->argv[index], "$$"))
		{
			replace_string(&(info->argv[index]),
					_strdup(custom_convert_number(getpid(), 10, 0)));
			continue;
	}
	node = node_starts_with(config->env, &info->argv[index][1], '=');
	if (node)
	{
		replace_string(&(config->argv[index]),
				_strdup(_strchr(node->str, '=') + 1));
		continue;
	}
	replace_string(&config->argv[index], _strdup(""));
	}
	return (0);
}
/**
 * custom_replace_string - replaces a string
 * @ancient: Address of the old string
 * @modern: New string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int custom_replace_string(char **ancient, char *modern)
{
	free(*ancient);
	*ancient = modern;
	return (1);
}
