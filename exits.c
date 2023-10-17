#include "shell.h"
/**
 * *_strncpy - copies a string
 * @dest: the destination string to be copied to
 * @src: the source string
 * @kimba: the amount of characters to be copied
 * Return: the concatenated string
 */
char *_strncpy(char *dest, char *src, int kimba)
{
	int index, x;
	char *s = dest;

	index = 0;

	while (src[index] != '\0' && index < kimba - 1)
	{
		dest[index] = src[index];
		index++;
	}

	if (index < kimba)
	{
		x = index;
		while (x < kimba)
		{
			dest[x] = '\0';
			x++;
		}
	}
	return (s);
}

/**
 * *_strncat - concatenates two strings
 * @dest: the first string
 * @src: the second string
 * @kimba: the amount of bytes to be maximally used
 * Return: the concatenated string
 */
char *_strncat(char *dest, char *src, int kimba)
{
	int index, x;
	char *s = dest;

	index = 0;
	x = 0;

	while (dest[index] != '\0')
		index++;

	while (src[x] != '\0' && x < kimba)
	{
		dest[index] = src[x];
		index++;
		x++;
	}
	if (x < index)
		dest[index] = '\0';
	return (s);
}

/**
 * *_strchr - locates a character in a string
 * @size: the string to be parsed
 * @count: the character to look for
 * Return: (size) a pointer to the memory area s
 */
char *_strchr(char *size, char count)
{
	do {
		if (*size == count)
			return (size);
	}

	while (*size++ != '\0');

	return (NULL);
}
