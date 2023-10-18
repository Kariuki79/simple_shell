#include "shell.h"

/**
 * fetch_history_file - retrieves the history file
 * @info: Parameter struct
 *
 * Return: Allocated string containing the history file
 */
char *fetch_history_file(info_t *info)
{
    char *directory, *buffer;

    directory = custom_get_environment_variable(info, "HOME=");
    if (!directory)
        return NULL;
    buffer = malloc(sizeof(char) * (custom_strlen(directory) + custom_strlen(HISTORY_FILE) + 2));
    if (!buffer)
        return NULL;
    buffer[0] = 0;
    custom_strcpy(buffer, directory);
    custom_strcat(buffer, "/");
    custom_strcat(buffer, HISTORY_FILE);
    return buffer;
}

/**
 * create_or_append_history - creates a new file or appends to an existing one
 * @info: Parameter struct
 *
 * Return: 1 on success, -1 on failure
 */
int create_or_append_history(info_t *info)
{
    ssize_t file_descriptor;
    char *filename = fetch_history_file(info);
    list_t *node = NULL;

    if (!filename)
        return -1;

    file_descriptor = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
    free(filename);
    if (file_descriptor == -1)
        return -1;

    for (node = info->history; node; node = node->next)
    {
        custom_puts_to_fd(node->str, file_descriptor);
        custom_putchar_to_fd('\n', file_descriptor);
    }
    custom_putchar_to_fd(BUF_FLUSH, file_descriptor);
    close(file_descriptor);

    return 1;
}

/**
 * load_history - reads history from a file
 * @info: Parameter struct
 *
 * Return: The updated history line count on success, 0 on failure
 */
int load_history(info_t *info)
{
    int i, last = 0, linecount = 0;
    ssize_t file_descriptor, read_length, file_size = 0;
    struct stat file_stat;
    char *buffer = NULL, *filename = fetch_history_file(info);

    if (!filename)
        return 0;

    file_descriptor = open(filename, O_RDONLY);
    free(filename);
    if (file_descriptor == -1)
        return 0;

    if (!fstat(file_descriptor, &file_stat))
        file_size = file_stat.st_size;

    if (file_size < 2)
        return 0;

    buffer = malloc(sizeof(char) * (file_size + 1));
    if (!buffer)
        return 0;

    read_length = read(file_descriptor, buffer, file_size);
    buffer[file_size] = 0;

    if (read_length <= 0)
        return free(buffer), 0;

    close(file_descriptor);

    for (i = 0; i < file_size; i++)
        if (buffer[i] == '\n')
        {
            buffer[i] = 0;
            custom_build_history_list(info, buffer + last, linecount++);
            last = i + 1;
        }

    if (last != i)
        custom_build_history_list(info, buffer + last, linecount++);
    free(buffer);
    info->histcount = linecount;

    while (info->histcount-- >= HISTORY_MAX)
        custom_delete_node_at_index(&(info->history), 0);

    custom_renumber_history(info);

    return info->histcount;
}

/**
 * append_to_history - adds an entry to the history linked list
 * @info: Parameter struct
 * @buffer: Buffer to add
 * @linecount: The history line count (histcount)
 *
 * Return: Always 0
 */
int append_to_history(info_t *info, char *buffer, int linecount)
{
    list_t *node = NULL;

    if (info->history)
        node = info->history;

    custom_add_node_end(&node, buffer, linecount);

    if (!info->history)
        info->history = node;

    return 0;
}

/**
 * renumber_history - renumbers the history linked list after changes
 * @info: Parameter struct
 *
 * Return: The updated history line count
 */
int renumber_history(info_t *info)
{
    list_t *node = info->history;
    int i = 0;

    while (node)
    {
        node->num = i++;
        node = node->next;
    }
    return (info->histcount = i);
}

