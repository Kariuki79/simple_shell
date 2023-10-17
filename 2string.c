#include "shell.h"

/**
 * custom_copy_string - copies a string
 * @dest: The destination
 * @src: The source
 *
 * Return: Pointer to the destination
 */
char *custom_copy_string(char *dest, char *src)
{
	int index = 0;

	if (dest == src || src == 0)
		return (dest);

	while (src[index])
	{
		dest[index] = src[index];
		index++;
	}
	dest[index] = 0;
	return (dest);
}

/**
 * custom_duplicate_string - duplicates a string
 * @str: The string to duplicate
 *
 * Return: Pointer to the duplicated string
 */
char *custom_duplicate_string(const char *str)
{
	int length = 0;
	char *ret;

	if (str == NULL)
		return (NULL);

	while (*str++)
		length++;

	ret = malloc(sizeof(char) * (length + 1));

	if (!ret)
		return (NULL);

	for (length++; length--;)
		ret[length] = *--str;

	return (ret);
}
/**
 * custom_print_string - prints an input string
 * @str: The string to be printed
 *
 * Return: Nothing
 */
void custom_print_string(char *str)
{
	int index = 0;

	if (!str)
		return;
	while (str[index] != '\0')
	{
		custom_put_character(str[index]);
		index++;
	}
}

/**
 * custom_put_character - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int custom_put_character(char c)
{
	static int index;
	static char buffer[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || index >= WRITE_BUF_SIZE)
	{
		write(1, buffer, index);
		index = 0;
	}

	if (c != BUF_FLUSH)
		buffer[index++] = c;

	return (1);
}

