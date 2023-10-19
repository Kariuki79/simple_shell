#include "shell.h"
/**
 * initialize_info - sets initial values for info_t struct
 * @info: Address of the info_t struct
 */
void initialize_info(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * configure_info - configures the info_t struct with user input
 * @info: Address of the info_t struct
 * @arguments: Argument vector
 */
void configure_info(info_t *info, char **arguments)
{
	int index = 0;

	info->fname = arguments[0];

	if (info->arguments)
	{
		info->argv = strtow(info->arg, " \t");

		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = duplicate_string(info->arguments);
				info->argv[1] = NULL;
			}
		}
		for (index = 0; info->argv && info->argv[index]; index++)
			;
		info->argc = index;
		replace_alias(info);
		replace_vars(info);
	}
}

/**
 * deallocate_info - frees allocated memory in the info_t struct
 * @info: Address of the info_t struct
 * @release_all: True if all fields should be freed
 */
void deallocate_info(info_t *info, int release_all)
{
	ffree(info->argv);
	info->argv = NULL;
	info->path = NULL;

	if (release_all)
	{
		if (!info->cmd_buf)
			free(info->arg);

		if (info->environ)
			free_list(&(info->environ));

		if (info->history)
			free_list(&(info->history));

		if (info->alias)
			free_list(&(info->alias));
		free_string_array(info->environment_variables);
		info->environ = NULL;
		bfree((void **)info->cmd_buf);

		if (info->read_file_descriptor > 2)
			close(info->readfd);
		write(2, BUF_FLUSH, 1);
	}
}

