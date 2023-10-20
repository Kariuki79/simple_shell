#include "shell.h"

/**
 * _string_cpy - copies a string
 * @dexterity: the destination
 * @source_copy: the source
 *
 * Return: pointer to destination
 */
char *_strcpy(char *dexterity, char *source_code)
{
	int index = 0;

	if (dexterity == source_code || source_code == 0)
		return (dexterity);
	while (source_code[index])
	{
		dexterity[index] = source_code[index];
		index++;
	}
	dexterity[index] = 0;
	return (dexterity);
}

/**
 * _strdup - duplicates a string
 * @string: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *_strdup(const char *string)
{
	int length = 0;
	char *threshold;

	if (string == NULL)
		return (NULL);
	while (*string++)
		length++;
	threshold = malloc(sizeof(char) * (length + 1));
	if (!threshold)
		return (NULL);
	for (length++; length--;)
		threshold[length] = *--string;
	return (threshold);
}

/**
 *_puts - prints an input string
 *@string: the string to be printed
 *
 * Return: Nothing
 */
void _puts(char *string)
{
	int index = 0;

	if (!string)
		return;
	while (string[index] != '\0')
	{
		_putchar(string[index]);
		index++;
	}
}

/**
 * _putchar - writes the character c to stdout
 * @character: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char character)
{
	static int index;
	static char buf[WRITE_BUF_SIZE];

	if (character == BUF_FLUSH || index >= WRITE_BUF_SIZE)
	{
		write(1, buf, index);
		index = 0;
	}
	if (character != BUF_FLUSH)
		buf[index++] = character;
	return (1);
}
