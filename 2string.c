#include "custom_shell.h"

/**
 * custom_copy_string - copies a string
 * @dest: The destination
 * @src: The source
 *
 * Return: Pointer to the destination
 */
char *custom_copy_string(char *dest, char *src)
{
    int i = 0;

    if (dest == src || src == 0)
        return dest;

    while (src[i])
    {
        dest[i] = src[i];
        i++;
    }

    dest[i] = 0;
    return dest;
}

/**
 * custom_duplicate_string - duplicates a string
 * @str: The string to duplicate
 *
 * Return: Pointer to the duplicated string
 */
char *custom_duplicate_string(const char *str)
{
    int length = 0;
    char *ret;

    if (str == NULL)
        return NULL;

    while (*str++)
        length++;

    ret = malloc(sizeof(char) * (length + 1));

    if (!ret)
        return NULL;

    for (length++; length--;)
        ret[length] = *--str;

    return ret;
}

/**
 * custom_print_string - prints an input string
 * @str: The string to be printed
 *
 * Return: Nothing
 */
void custom_print_string(char *str)
{
    int i = 0;

    if (!str)
        return;

    while (str[i] != '\0')
    {
        custom_put_character(str[i]);
        i++;
    }
}

/**
 * custom_put_character - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int custom_put_character(char c)
{
    static int i;
    static char buffer[WRITE_BUFFER_SIZE];

    if (c == BUFFER_FLUSH || i >= WRITE_BUFFER_SIZE)
    {
        write(1, buffer, i);
        i = 0;
    }

    if (c != BUFFER_FLUSH)
        buffer[i++] = c;

    return 1;
}

