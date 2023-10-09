#include "shell.h"
#include <ctype.h> /* It include the necessary libraries */

/**
 * interactive - check if the shell is in interactive mode and
 * returns if the case
 * @info: struct address to the pointer to info_t struct
 *
 * Return: 1 if interactive mode, 0 if otherwise
 */
int interactive(info_t *info)
{
	if (isatty(STDIN_FILENO) && info->readfd <= 2)
		return (1);
	return (0);
}

/**
 * is_delim - checks if a character is a delimitor
 * @c: The character to be checked
 *
 * @delim: The delimiter string
 *
 * Return: 1 if true, 0 if false
 */
int is_delim(char c, char *delim)
{
	while (*delim)
	{
		if (*delim++ == c)
			return (1);
	}
	return (0);
}

/**
 * _isalpha - checks if character is alphabetic
 * @c: The character to check, the character to input
 *
 * Return: 1 if is alphabetic, 0 otherwise
 */
int _isalpha(int c)
{
	if (isalpha(c))
		return (1);
	return (0);
}

/**
 * _atoi - converts a string to an integer
 * @s: The string to be converted
 *
 * Return: 0 if zero numbers in the string, if otherwise converted number
 */
int _atoi(char *s)i
{
	int i, sign = 1, flag = 0;

	output = 0;

	for (i = 0; s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;
		if (isdigit(s[i]))
		{
			flag = 1;
			output = output * 10 + (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

if (sign == 1)
	return (-output);
return (output);
	}
