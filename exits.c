#include "shell.h"
<<<<<<< HEAD

/**
 **_strncpy - copies a string
 *@dexterity: the destination the string can be copied to
 *@source_code: the source string
 *@config: the amount of characters to be copied
 *Return: the concatenated string
 */
char *_strncpy(char *dexterity, char *source_code, int config)
{
	int index, array;
	char *s = dexterity;

	index = 0;
	while (source_code[index] != '\0' && index < config - 1)
	{
		dexterity[index] = source_code[index];
		index++;
	}
	if (index < config)
	{
		array = index;
		while (array < config)
		{
			dexterity[array] = '\0';
			array++;
=======
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
>>>>>>> 84ddf4ff1ea3706a2021dfea8bb16be8aac57619
		}
	}
	return (s);
}

/**
<<<<<<< HEAD
 **_strncat - concatenates two strings
 *@dexterity: the first string
 *@source_code: the second string
 *@config: the amount of bytes to be maximally used
 *Return: the concatenated string
 */
char *_strncat(char *dexterity, char *source_code, int config)
{
	int index, array;
	char *s = dexterity;

	index = 0;
	array = 0;
	while (dexterity[index] != '\0')
		index++;
	while (source_code[array] != '\0' && array < config)
	{
		dexterity[index] = source_code[array];
		index++;
		array++;
	}
	if (array < config)
		dexterity[index] = '\0';
=======
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
>>>>>>> 84ddf4ff1ea3706a2021dfea8bb16be8aac57619
	return (s);
}

/**
<<<<<<< HEAD
 **_strchr - locates a character in a string
 *@string: the string to be parsed
 *@character: the character to look for
 *Return: (string) a pointer to the memory area s
 */
char *_strchr(char *string, char character)
{
	do {
		if (*string == character)
			return (string);
	} while (*string++ != '\0');
=======
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
>>>>>>> 84ddf4ff1ea3706a2021dfea8bb16be8aac57619

	return (NULL);
}
