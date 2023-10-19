#include "shell.h"

/**
 * _strlen - returns the length of a string
 * @string: the string whose length to check
 *
 * Return: integer length of string
 */
int _strlen(char *string)
{
	int index = 0;

	if (!string)
		return (0);

	while (*string++)
		index++;
	return (index);
}

/**
 * _strcmp - performs lexicogarphic comparison of two strangs.
 * @size_string1: the first string
 * @size_string2: the second string
 *
 * Return: negative if size_string1 < size_string2,
 * positive if size_string1 > size_stirng2,
 * zero if size_string1 == size_string2
 */
int _strcmp(char *size_string1, char *size_string2)
{
	while (*size_string1 && *size_string2)
	{
		if (*size_string1 != *size_string2)
			return (*size_string1 - *size_string2);
		size_string1++;
		size_string2++;
	}
	if (*size_string1 == *size_string2)
		return (0);
	else
		return (*size_string1 < *size_string2 ? -1 : 1);
}

/**
 * starts_with - checks if needle starts with haystack
 * @current: string to search
 * @substring: the substring to find
 *
 * Return: address of next char of haystack or NULL
 */
char *starts_with(const char *current, const char *substring)
{
	while (*substring)
		if (*substring++ != *current++)
			return (NULL);
	return ((char *)current);
}

/**
 * _strcat - concatenates two strings
 * @dexterity: the destination buffer
 * @source_code: the source buffer
 *
 * Return: pointer to destination buffer
 */
char *_strcat(char *dexterity, char *source_code)
{
	char *ret = dexterity;

	while (*dexterity)
		dexterity++;
	while (*source_code)
		*dexterity++ = *source_code++;
	*dexterity = *source_code;
	return (ret);
}
