#include "shell.h"
/**
 * _erratoi - converts a string to an integer
 * @str: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 * -1 on error
 */
int _erratoi(char *str)
{
	int index = 0;
	unsigned long int result = 0;

	if (*str == '+')
		str++;

	for (index = 0; str[index] != '\0'; index++)
	{
		if (str[index] >= '0' && str[index] <= '9')
		{
			result *= 10;
			result += (str[index] - '0');

			if (result > INT_MAX)
				return (-1);
	}

		else
			return (-1);
	}
	return (result);
}


/**
 * print_error - prints an error message
 * @iterator: the parameter and return info struct
 * @error_string: string containing specified error type
 * Return: void
 */
void print_error_message(info_t *iterator, char *error_string)
{
	_eputs(iterator->fname);
	_eputs(": ");
	print_error_message(iterator->line_number, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(error_string);
}

/**
 * print_integer - function prints an integer
 * @number: the integer to print
 * @fd: the file descriptor to write to
 *
 * Return: number of characters printed
 */
int print_integer(int number, int fd)
{
	int (*write_character)(char) = eputchar;
	int index, count = 0;
	unsigned int absolute_value, current;

	if (fd == STDERR_FILENO)
		write_character = eputchar;
	if (number < 0)
	{
		absolute_value = -number;
		write_character('-');
		count++;
	}

	else
		absolute_value = number;
	current = absolute_value;

	for (index = 1000000000; index > 1; index /= 10)
	{
		if (absolute_value / index)
		{
			write_character('0' + current / index);
			count++;
		}
		current %= index;
	}
	write_character('0' + current);
	count++;
	return (count);
}

/**
 * integer_to_string - converter function, similar to itoa
 * @num: number
 * @base: base
 * @flags: argument flags
 * Return: string
 */
char *integer_to_string(long int num, int base, int flags)
{
	static char *character_set;
	static char string_buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';
	}
	character_set = flags & CONVERT_LOWERCASE ?
		"0123456789abcdef" : "0123456789ABCDEF";
	ptr = &string_buffer[49];
	*ptr = '\0';

	do {
		*--ptr = character_set[n % base];
		n /= base;
	}

	while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * remove_hash_comments - function replaces the first instance of '#' with '\0'
 * @buffer: address of the string to modify
 * Return: Always 0;
 */
void remove_hash_comments(char *buffer)
{
	int index;

	for (index = 0; buffer[index] != '\0'; index++)
	{
		if (buffer[index] == '#' && (!index || buffer[index - 1] == ' '))
		{
			buffer[index] = '\0';
			break;
		}
	}
}
