#include "shell.h"

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
		}
	}
	return (s);
}

/**
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
	return (s);
}

/**
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

	return (NULL);
}
