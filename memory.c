#include "shell.h"

/**
 * custom_bfree - frees a pointer and sets it to NULL
 * @ptr: Address of the pointer to free
 *
 * Return: 1 if freed, otherwise 0.
 */
int custom_bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		custom_bfree(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
