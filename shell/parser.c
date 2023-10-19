#include "shell.h"

/**
 * is_cmd - determines if a file is an executable command
 * @custom_info: the info struct
 * @custom_path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_cmd(info_t *custom_info, char *custom_path)
{
	struct stat custom_stat;

	(void)custom_info;
	if (!custom_path || stat(custom_path, &custom_stat))
		return (0);

	if (custom_stat.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - duplicates characters
 * @custom_path_str: the PATH string
 * @custom_start: starting index
 * @custom_stop: stopping index
 *
 * Return: pointer to new buffer
 */
char *dup_chars(char *custom_path_str, int custom_start, int custom_stop)
{
	static char buf[1024];
	int index = 0, key = 0;

	for (key = 0, index = custom_start; index < custom_stop; index++)
		if (custom_path_str[index] != ':')
			buf[key++] = custom_path_str[index];
	buf[key] = 0;
	return (buf);
}

/**
 * find_path - finds the command in the PATH string
 * @custom_info: the info struct
 * @custom_path_str: the PATH string
 * @custom_cmd: the command to find
 *
 * Return: full path of cmd if found or NULL
 */
char *find_path(info_t *custom_info, char *custom_path_str, char *custom_cmd)
{
	int index = 0, curr_pos = 0;
	char *custom_path;

	if (!custom_path_str)
		return (NULL);
	if ((_strlen(custom_cmd) > 2) && starts_with(custom_cmd, "./"))
	{
		if (is_cmd(custom_info, custom_cmd))
			return (custom_cmd);
	}
	while (1)
	{
		if (!custom_path_str[index] || custom_path_str[index] == ':')
		{
			custom_path = dup_chars(custom_path_str, curr_pos, index);
			if (!*custom_path)
				_strcat(custom_path, custom_cmd);
			else
			{
				_strcat(custom_path, "/");
				_strcat(custom_path, custom_cmd);
			}
			if (is_cmd(custom_info, custom_path))
				return (custom_path);
			if (!custom_path_str[index])
				break;
			curr_pos = index;
		}
		index++;
	}
	return (NULL);
}
