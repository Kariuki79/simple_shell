#include "shell.h"

/**
 * list_len - determines length of linked list
 * @handler: pointer to first node
 *
 * Return: size of list
 */
size_t list_len(const list_t *handler)
{
	size_t index = 0;

	while (handler)
	{
		handler = handler->next;
		index++;
	}
	return (index);
}

/**
 * list_to_strings - returns an array of strings of the list->str
 * @hostname: pointer to first node
 *
 * Return: array of strings
 */
char **list_to_strings(list_t *hostname)
{
	list_t *node = hostname;
	size_t index = list_len(hostname), json;
	char **strs;
	char *str;

	if (!hostname || !index)
		return (NULL);
	strs = malloc(sizeof(char *) * (index + 1));
	if (!strs)
		return (NULL);
	for (index = 0; node; node = node->next, index++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (json = 0; json < index; json++)
				free(strs[json]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[index] = str;
	}
	strs[index] = NULL;
	return (strs);
}


/**
 * print_list - prints all elements of a list_t linked list
 * @hostname: pointer to first node
 *
 * Return: size of list
 */
size_t print_list(const list_t *hostname)
{
	size_t index = 0;

	while (hostname)
	{
		_puts(convert_number(hostname->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(hostname->str ? hostname->str : "(nil)");
		_puts("\n");
		hostname = hostname->next;
		index++;
	}
	return (index);
}

/**
 * node_starts_with - returns node whose string starts with prefix
 * @node: pointer to list head
 * @prefix: string to match
 * @character: the next character after prefix to match
 *
 * Return: match node or null
 */
list_t *node_starts_with(list_t *node, char *prefix, char character)
{
	char *p = NULL;

	while (node)
	{
		p = starts_with(node->str, prefix);
		if (p && ((character == -1) || (*p == character)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - gets the index of a node
 * @hostname: pointer to list head
 * @node: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t get_node_index(list_t *hostname, list_t *node)
{
	size_t index = 0;

	while (hostname)
	{
		if (hostname == node)
			return (index);
		hostname = hostname->next;
		index++;
	}
	return (-1);
}
