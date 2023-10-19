#include "shell.h"

/**
 *_eputs - prints an input string
 * @string: the string that will be printed
 *
 * Return: Nothing
 */
void _eputs(char *string)
{
	int index = 0;

	if (!string)
		return;
	while (string[index] != '\0')
	{
		_eputchar(string[index]);
		index++;
	}
}

/**
 * _eputchar - writes the character c to stderr
 * @count: The count character to be printed
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _eputchar(char count)
{
	static int index;
	static char buf[WRITE_BUF_SIZE];

	if (count == BUF_FLUSH || index >= WRITE_BUF_SIZE)
	{
		write(2, buf, index);
		index = 0;
	}
	if (count != BUF_FLUSH)
		buf[index++] = count;
	return (1);
}

/**
 * _putfd - writes the character c to given fd
 * @count: The count character to be printed
 * @file_d: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putfd(char count, int file_d)
{
	static int index;
	static char buf[WRITE_BUF_SIZE];

	if (count == BUF_FLUSH || index >= WRITE_BUF_SIZE)
	{
		write(file_d, buf, index);
		index = 0;
	}
	if (count != BUF_FLUSH)
		buf[index++] = count;
	return (1);
}

/**
 *_putsfd - prints an input string
 * @string: the string to be printed
 * @file_d: the filedescriptor to write to
 *
 * Return: the number of chars put
 */
int _putsfd(char *string, int file_d)
{
	int index = 0;

	if (!string)
		return (0);
	while (*string)
	{
		index += _putfd(*string++, file_d);
	}
	return (index);
}
