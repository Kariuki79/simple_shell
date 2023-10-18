#include "shell.h"

/**
 * hsh - The main shell loop
 * @config: the parameter and return info struct
 * @value: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or an error in code
 */
int hsh(info_t *config, char **value)
{
	ssize_t iterator = 0;
	int builtin_ret = 0;

	while (iterator != -1 && builtin_ret != -2)
	{
		clear_info(config);

		if (interactive(config))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		iterator = get_input(config);

		if (iterator != -1)
		{
			set_info(config, value);
			builtin_ret = find_builtin(config);
			if (builtin_ret == -1)
				find_cmd(config);
		}

		else if (interactive(config))
			_putchar('\n');
		free_info(config, 0);
	}

	write_history(config);
	free_info(config, 1);

	if (!interactive(config) && config->status)
		exit(config->status);

	if (builtin_ret == -2)
	{
		if (config->err_num == -1)
			exit(config->status);
		exit(config->err_num);
	}

	return (builtin_ret);
}

/**
 * find_builtin - searches for a builtin command
 * @config: the parameter & return config struct
 * Return: -1 if builtin not found,
 * 0 if builtin executed successfully,
 * 1 if builtin found but not successful,
 * -2 if builtin signals exit()
 */
int find_builtin(info_t *config)
{
	int index, built_in_ret = -1;
	builtin_table builtintbl[] =
	{
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (index = 0; builtintbl[index].type; index++)
		if (_strcmp(info->argv[0], builtintbl[index].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[index].func(config);
			break;
		}
	return (built_in_ret);
}

/**
 * find_cmd - searches for a command in PATH
 * @config: the parameter & return info struct
 *
 * Return: void
 */
void find_cmd(info_t *config)
{
	char *path = NULL;
	int index, key;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}

	for (index = 0, key = 0; config->arg[index]; index++)
		if (!is_delim(config->arg[index], " \t\n"))
			key++;
	if (!key)
		return;

	path = find_path(config, _getenv(config, "PATH="), config->argv[0]);

	if (path)
	{
		config->path = path;
		fork_cmd(config);
	}
	else
	{
		if ((interactive(config) || _getenv(info, "PATH=")
					|| config->argv[0][0] == '/') && is_cmd(config, config->argv[0]))
			fork_cmd(config);
		else if (*(config->arg) != '\n')
		{
			config->status = 127;
			print_error(config, "not found\n");
		}
	}
}

/**
 * fork_cmd - forks out an exec thread to run cmd
 * @config: the parameter & return info struct
 *
 * Return: void
 */
void fork_cmd(info_t *config)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{

	}

	if (child_pid == 0)
	{
		if (execve(config->path, config->argv, get_environ(config)) == -1)
		{
			free_info(config, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			config->status = WEXITSTATUS(config->status);
			if (config->status == 126)
				print_error(config, "Permission denied\n");
		}
	}
}
