#include "shell.h"
/**
 * copy_string - copies part of a source string to a destination string
 * @destination: the string to which the content is copied
 * @source: the string from which content is copied
 * @max_length: the maximum number of characters to copy
 * Returns: a pointer to the destination string
 */
char *copy_string(char *destination, char *source, int max_length)
{
	int idx_dest = 0, idx_src = 0;
	char *result = destination;

	idx_dest = 0;
	while (source[idx_src] != '\0' && idx_dest < max_length - 1)
	{
		destination[idx_dest] = source[idx_src];
		idx_dest++;
		idx_src++;
	}
	if (idx_dest < max_length)
	{
		int j = idx_dest;
		while (j < max_length)
		{
			destination[j] = '\0';
			j++;
		}
	}
	return result;
}

/**
 * concatenate_strings - concatenates two strings up to a specified maximum length
 * @dest_string: the first string (base) to which the second string is appended
 * @src_string: the second string to be appended
 * @max_length: the maximum number of characters to append
 * Returns: a pointer to the concatenated string
 */
char *concatenate_strings(char *dest_string, char *src_string, int max_length)
{
	int idx_dest = 0, idx_src = 0;
	char *result = dest_string;

	idx_dest = 0;
	idx_src = 0;

	while (dest_string[idx_dest] != '\0')
		idx_dest++;

	while (src_string[idx_src] != '\0' && idx_src < max_length)
	{
		dest_string[idx_dest] = src_string[idx_src];
		idx_dest++;
		idx_src++;
	}
	if (idx_src < max_length)
		dest_string[idx_dest] = '\0';
	return (result);
}

/**
 * find_character - searches for a character within a string
 * @input_string: the string to be searched
 * @target_char: the character to be located
 * Returns: a pointer to the first occurrence of the target character in the input string, or NULL if not found
 */
char *find_character(char *input_string, char target_char)
{
	do
	{
		if (*input_string == target_char)
			return input_string;
	}
	while (*input_string++ != '\0');
	return (NULL);
}

