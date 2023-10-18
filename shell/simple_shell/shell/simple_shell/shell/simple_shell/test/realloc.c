#include "custom_shell.h"

/**
 * custom_memset - fills memory with a constant byte
 * @custom_s: The pointer to the memory area
 * @custom_b: The byte to fill *s with
 * @custom_n: The amount of bytes to be filled
 *
 * Return: A pointer to the memory area s
 */
char *custom_memset(char *custom_s, char custom_b, unsigned int custom_n)
{
    unsigned int custom_i;

    for (custom_i = 0; custom_i < custom_n; custom_i++)
        custom_s[custom_i] = custom_b;
    return custom_s;
}

/**
 * custom_ffree - frees a string of strings
 * @custom_pp: String of strings
 */
void custom_ffree(char **custom_pp)
{
    char **custom_a = custom_pp;

    if (!custom_pp)
        return;
    while (*custom_pp)
        free(*custom_pp++);
    free(custom_a);
}

/**
 * custom_realloc - reallocates a block of memory
 * @custom_ptr: Pointer to the previous malloc'ated block
 * @custom_old_size: Byte size of the previous block
 * @custom_new_size: Byte size of the new block
 *
 * Return: Pointer to the old block
 */
void *custom_realloc(void *custom_ptr, unsigned int custom_old_size, unsigned int custom_new_size)
{
    char *custom_p;

    if (!custom_ptr)
        return malloc(custom_new_size);
    if (!custom_new_size)
        return free(custom_ptr), NULL;
    if (custom_new_size == custom_old_size)
        return custom_ptr;

    custom_p = malloc(custom_new_size);
    if (!custom_p)
        return NULL;

    custom_old_size = custom_old_size < custom_new_size ? custom_old_size : custom_new_size;
    while (custom_old_size--)
        custom_p[custom_old_size] = ((char *)custom_ptr)[custom_old_size];
    free(custom_ptr);
    return custom_p;
}

