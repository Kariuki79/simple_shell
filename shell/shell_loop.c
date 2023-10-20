#include "shell.h"

/**
 * hsh - main shell loop
 * @value: the parameter & return info struct
 * @arg_v: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(info_t *value, char **arg_v)
{
	ssize_t array = 0;
	int builtin_ret = 0;

	while (array != -1 && builtin_ret != -2)
	{
		clear_info(value);
		if (interactive(value))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		array = get_input(value);
		if (array != -1)
		{
			set_info(value, arg_v);
			builtin_ret = find_builtin(value);
			if (builtin_ret == -1)
				find_cmd(value);
		}
		else if (interactive(value))
			_putchar('\n');
		free_info(value, 0);
	}
	write_history(value);
	free_info(value, 1);
	if (!interactive(value) && value->status)
		exit(value->status);
	if (builtin_ret == -2)
	{
		if (value->err_num == -1)
			exit(value->status);
		exit(value->err_num);
	}
	return (builtin_ret);
}

/**
 * find_builtin - finds a builtin command
 * @value: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 * 0 if builtin executed successfully,
 * 1 if builtin found but not successful,
 *-2 if builtin signals exit()
 */
int find_builtin(info_t *value)
{
	int index, built_in_ret = -1;
	builtin_table builtintbl[] = {
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
		if (_strcmp(value->argv[0], builtintbl[index].type) == 0)
		{
			value->line_count++;
			built_in_ret = builtintbl[index].func(value);
			break;
		}
	return (built_in_ret);
}

/**
 * find_cmd - finds a command in PATH
 * @value: the parameter & return info struct
 *
 * Return: void
 */
void find_cmd(info_t *value)
{
	char *path = NULL;
	int index, key;

	value->path = value->argv[0];
	if (value->linecount_flag == 1)
	{
		value->line_count++;
		value->linecount_flag = 0;
	}
	for (index = 0, key = 0; value->arg[index]; index++)
		if (!is_delim(value->arg[index], " \t\n"))
			key++;
	if (!key)
		return;

	path = find_path(value, _getenv(value, "PATH="), value->argv[0]);
	if (path)
	{
		value->path = path;
		fork_cmd(value);
	}
	else
	{
		if ((interactive(value) || _getenv(value, "PATH=")
			|| value->argv[0][0] == '/') && is_cmd(value, value->argv[0]))
			fork_cmd(value);
		else if (*(value->arg) != '\n')
		{
			value->status = 127;
			print_error(value, "not found\n");
		}
	}
}

/**
 * fork_cmd - forks a an exec thread to run cmd
 * @value: the parameter & return info struct
 *
 * Return: void
 */
void fork_cmd(info_t *value)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(value->path, value->argv, get_environ(value)) == -1)
		{
			free_info(value, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(value->status));
		if (WIFEXITED(value->status))
		{
			value->status = WEXITSTATUS(value->status);
			if (value->status == 126)
				print_error(value, "Permission denied\n");
		}
	}
}
