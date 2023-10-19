#include "shell.h"

/**
 *_memset - fills memory with a constant byte
 *@custom_s: the pointer to the memory area
 *@custom_b: the byte to fill *s with
 *@numb: unsigned int
 *Return: (custom_s) a pointer to the memory area s
 */
char *_memset(char *custom_s, char custom_b, unsigned int numb)
{
	unsigned int index;

	for (index = 0; index < numb; index++)
		custom_s[index] = custom_b;
	return (custom_s);
}

/**
 * ffree - frees a string of strings
 * @custom_pp: string of strings
 */
void ffree(char **custom_pp)
{
	char **custom_a = custom_pp;

	if (!custom_pp)
		return;
	while (*custom_pp)
		free(*custom_pp++);
	free(custom_a);
}

/**
 * _realloc - reallocates a block of memory
 * @custom_ptr: pointer to previous malloc'ated block
 * @custom_old_size: byte size of previous block
 * @custom_new_size: byte size of new block
 *
 * Return: pointer to da ol'block nameen.
 */
void *_realloc(void *custom_ptr, unsigned int custom_old_size,
		unsigned int custom_new_size)
{
	char *prev;

	if (!custom_ptr)
		return (malloc(custom_new_size));
	if (!custom_new_size)
		return (free(custom_ptr), NULL);
	if (custom_new_size == custom_old_size)
		return (custom_ptr);

	prev = malloc(custom_new_size);
	if (!prev)
		return (NULL);

	custom_old_size = custom_old_size < custom_new_size ?
		custom_old_size : custom_new_size;
	while (custom_old_size--)
		prev[custom_old_size] = ((char *)custom_ptr)[custom_old_size];
	free(custom_ptr);
	return (prev);
}
