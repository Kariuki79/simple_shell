#include "shell.h"

/**
 * custom_is_cmd - determines if a file is an executable command
 * @custom_info: The custom info struct
 * @custom_path: Path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int custom_is_cmd(custom_info_t *custom_info, char *custom_path)
{
    struct stat custom_stat;

    (void)custom_info;
    if (!custom_path || stat(custom_path, &custom_stat))
        return 0;

    if (custom_stat.st_mode & S_IFREG)
    {
        return 1;
    }
    return 0;
}

/**
 * custom_dup_chars - duplicates characters
 * @custom_path_str: The custom PATH string
 * @custom_start: Starting index
 * @custom_stop: Stopping index
 *
 * Return: Pointer to a new buffer
 */
char *custom_dup_chars(char *custom_path_str, int custom_start, int custom_stop)
{
    static char custom_buf[1024];
    int i = 0, k = 0;

    for (k = 0, i = custom_start; i < custom_stop; i++)
        if (custom_path_str[i] != ':')
            custom_buf[k++] = custom_path_str[i];
    custom_buf[k] = 0;
    return custom_buf;
}

/**
 * custom_find_path - finds the command in the custom PATH string
 * @custom_info: The custom info struct
 * @custom_path_str: The custom PATH string
 * @custom_cmd: The command to find
 *
 * Return: Full path of the command if found or NULL
 */
char *custom_find_path(custom_info_t *custom_info, char *custom_path_str, char *custom_cmd)
{
    int i = 0, custom_curr_pos = 0;
    char *custom_path;

    if (!custom_path_str)
        return NULL;
    if ((custom_strlen(custom_cmd) > 2) && custom_starts_with(custom_cmd, "./"))
    {
        if (custom_is_cmd(custom_info, custom_cmd))
            return custom_cmd;
    }
    while (1)
    {
        if (!custom_path_str[i] || custom_path_str[i] == ':')
        {
            custom_path = custom_dup_chars(custom_path_str, custom_curr_pos, i);
            if (!*custom_path)
                custom_strcat(custom_path, custom_cmd);
            else
            {
                custom_strcat(custom_path, "/");
                custom_strcat(custom_path, custom_cmd);
            }
            if (custom_is_cmd(custom_info, custom_path))
                return custom_path;
            if (!custom_path_str[i])
                break;
            custom_curr_pos = i;
        }
        i++;
    }
    return NULL;
}

