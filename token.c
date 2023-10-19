#include "shell.h"

/**
 * **strtow - splits a string into words. Repeat delimiters are ignored
 * @strng: the input string
 * @delimiter: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **strtow(char *string, char *delimiter)
{
	int index, array, key, m, numwords = 0;
	char **source;

	if (string == NULL || string[0] == 0)
		return (NULL);
	if (!delimiter)
		delimiter = " ";

	for (index = 0; string[index] != '\0'; index++)
		if (!is_delim(string[index], delimiter) &&
				(is_delim(string[index + 1], delimiter) || !string[index + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	source = malloc((1 + numwords) * sizeof(char *));
	if (!source)
		return (NULL);
	for (index = 0, array = 0; array < numwords; array++)
	{
		while (is_delim(string[index], delimiter))
			index++;
		key = 0;
		while (!is_delim(string[index + key], delimiter) && string[index + key])
			key++;
		s[array] = malloc((key + 1) * sizeof(char));
		if (!s[array])
		{
			for (key = 0; key < array; key++)
				free(s[key]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < key; m++)
			s[array][m] = string[index++];
		s[array][m] = 0;
	}
	s[array] = NULL;
	return (s);
}

/**
 * **strtow2 - splits a string into words
 * @string: the input string
 * @delimiter: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtow2(char *string, char delimiter)
{
	int index, array, key, m, numwords = 0;
	char **s;

	if (string == NULL || string[0] == 0)
		return (NULL);
	for (index = 0; str[index] != '\0'; index++)
		if ((string[index] != delimiter && string[index + 1] == delimiter) ||
		    (string[index] != delimiter && !string[index + 1]) || string[index + 1] == delimiter)
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (index = 0, array = 0; array < numwords; array++)
	{
		while (string[index] == delimiter && string[index] != delimiter)
			index++;
		k = 0;
		while (string[index + key] != delimiter && string[index + key] && string[index + key] != delimiter)
			key++;
		s[array] = malloc((key + 1) * sizeof(char));
		if (!s[array])
		{
			for (key = 0; k < array; key++)
				free(s[key]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < key; m++)
			s[array][m] = string[index++];
		s[array][m] = 0;
	}
	s[array] = NULL;
	return (s);
}
