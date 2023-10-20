#include "shell.h"

/**
 * _erratoi - converts a string to an integer
 * @string: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 * -1 on error
 */
int _erratoi(char *string)
{
	int index = 0;
	unsigned long int iterator = 0;

	if (*string == '+')
		string++;

	for (index = 0;  string[index] != '\0'; index++)
	{
		if (string[index] >= '0' && string[index] <= '9')
		{
			iterator *= 10;
			iterator += (string[index] - '0');
			if (iterator > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (iterator);
}

/**
 * print_error - prints an error message
 * @value: the parameter & return info struct
 * @estring: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 * -1 on error
 */
void print_error(info_t *value, char *estring)
{
	_eputs(value->fname);
	_eputs(": ");
	print_d(value->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(value->argv[0]);
	_eputs(": ");
	_eputs(estring);
}

/**
 * print_d - function prints a decimal (integer) number (base 10)
 * @element: the input
 * @flag: the filedescriptor to write to
 *
 * Return: number of characters printed
 */
int print_d(int element, int flag)
{
	int (*__putchar)(char) = _putchar;
	int index, count = 0;
	unsigned int _abs_, current;

	if (flag == STDERR_FILENO)
		__putchar = _eputchar;
	if (element < 0)
	{
		_abs_ = -element;
		__putchar('-');
		count++;
	}
	else
		_abs_ = element;
	current = _abs_;
	for (index = 1000000000; index > 1; index /= 10)
	{
		if (_abs_ / index)
		{
			__putchar('0' + current / index);
			count++;
		}
		current %= index;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * convert_number - converter function, a clone of itoa
 * @number: the number value
 * @base: base value
 * @flags_ag: argument flags
 *
 * Return: string
 */
char *convert_number(long int number, int base, int flags_ag)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = number;

	if (!(flags_ag & CONVERT_UNSIGNED) && number < 0)
	{
		n = -number;
		sign = '-';

	}
	array = flags_ag & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[number % base];
		number /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * remove_comments - function replaces first instance of '#' with '\0'
 * @buffer: address of the string to modify
 *
 * Return: Always 0;
 */
void remove_comments(char *buffer)
{
	int index;

	for (index = 0; buffer[index] != '\0'; index++)
		if (buffer[index] == '#' && (!index || buffer[index - 1] == ' '))
		{
			buffer[index] = '\0';
			break;
		}
}
