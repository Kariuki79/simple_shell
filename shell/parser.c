#include "shell.h"

/**
 **_memset - fills memory with a constant byte
 *@size: the pointer to the memory area
 *@buffer: the byte to fill *s with
 *@numerator: the amount of bytes to be filled
 *Return: (size) a pointer to the memory area size
 */
char *_memset(char *size, char buffer, unsigned int numerator)
{
	unsigned int index;

	for (index = 0; index < numerator; index++)
		size[index] = buffer;
	return (size);
}

/**
 * ffree - frees a string of strings
 * @str_str: string of strings
 */
void ffree(char **str_str)
{
	char **a = str_str;

	if (!str_str)
		return;
	while (*str_str)
		free(*str_str++);
	free(a);
}

/**
 * _realloc - reallocates a block of memory
 * @ptr: pointer to previous malloc'ated block
 * @pre_size: byte size of previous block
 * @current_size: byte size of new block
 *
 * Return: pointer to da ol'block nameen.
 */
void *_realloc(void *ptr, unsigned int pre_size, unsigned int current_size)
{
	char *p;

	if (!ptr)
		return (malloc(current_size));
	if (!current_size)
		return (free(ptr), NULL);
	if (current_size == pre_size)
		return (ptr);

	p = malloc(current_size);
	if (!p)
		return (NULL);

	pre_size = pre_size < current_size ? pre_size : current_size;
	while (pre_size--)
		p[pre_size] = ((char *)ptr)[pre_size];
	free(ptr);
	return (p);
}
