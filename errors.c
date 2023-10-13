#include "shell.h"
/***
 * eputs - prints a string to stderr
 * @str: the string to be printed
 */

void eputs(char *str)
{
	int m = 0;

	if (!str)

		return;
	while (str[m] != '\0')
	{
		eputchar(str[m]);
		m++;
	}
}
/**
 * eputchar - writes a character to stderr
 * @c: the character to print
 * @return: On success, 1 is returned. On error, -1 is returned,
 * and errno is set appropriately.
 */
int eputchar(char c)
{
	static int m;
	static char buffer[WRITE_BUFFER_SIZE];

	if (c == BUFFER_FLUSH || i >= WRITE_BUFFER_SIZE)
	{
		write(2, buffer, m);
		m = 0;
	}
	if (c != BUFFER_FLUSH)
		buffer[m++] = c;
	return (1);
}

/**
 * putfd - writes a character to a given file descriptor
 * @c: The character to print
 * @fd: The file descriptor to write to
 * @return: On success, 1 is returned. On error, -1 is returned,
 * and errno is set appropriately.
 */
int putfd(char c, int fd)
{
	static int m;
	static char buffer[WRITE_BUFFER_SIZE];

	if (c == BUFFER_FLUSH || m >= WRITE_BUFFER_SIZE)
	{
		write(fd, buffer, m);
		m = 0;
	}
	if (c != BUFFER_FLUSH)
		buffer[m++] = c;
	return (1);
}

/**
 * putsfd - prints a string to a specified file descriptor
 * @str: the string to be printed
 * @fd: the file descriptor to write to
 * @return: the number of characters written
 */
int putsfd(char *str, int fd)
{
	int m = 0;

	if (!str)
		return (0);
	while (*str)
	{
		m += putfd(*str++, fd);
	}
	return (m);
}
