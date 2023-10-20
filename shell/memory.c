#include "shell.h"

/**
 * custom_bfree - frees a pointer and sets it to NULL
 * @pointer: Address of the pointer to free
 *
 * Return: 1 if freed, otherwise 0.
 */
int custom_bfree(void **pointer)
{
	if (pointer && *pointer)
	{
		custom_bfree(*pointer);
		*pointer = NULL;
		return (1);
	}
	return (0);
}
