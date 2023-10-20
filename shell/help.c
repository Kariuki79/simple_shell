#include "shell.h"

/**
 * aux_help_env - Help info for the builtin env
 */

void aux_help_env(void)
{
	char *help_e = "env: env [option] [name=value] [command [args]]\n\t";

	write(STDOUT_FILENO, help_e, _strlen(help_e));
	help_e = "Print the enviroment of the shell.\n";
	write(STDOUT_FILENO, help_e, _strlen(help_e));

}
/**
 * aux_help_setenv - Help info for the builtin setenv
 */

void aux_help_setenv(void)
{

	char *helps = "setenv: setenv (const char *name, const char *value,";

	write(STDOUT_FILENO, helps, _strlen(helps));
	helps = "int replace)\n\t";
	write(STDOUT_FILENO, helps, _strlen(helps));
	helps = "Add a new definition to the environment\n";
	write(STDOUT_FILENO, helps, _strlen(helps));
}
/**
 * aux_help_unsetenv - Help info for the builtin unsetenv
 */

void aux_help_unsetenv(void)
{
	char *help = "unsetenv: unsetenv (const char *name)\n\t";

	write(STDOUT_FILENO, help, _strlen(help));
	help = "Remove an entry completely from the environment\n";
	write(STDOUT_FILENO, help, _strlen(help));
}


/**
 * aux_help_general - Entry point for help information for help builtin
 */

void aux_help_general(void)
{
	char *help_gen = "^-^ bash, version 1.0(1)-release\n";

	write(STDOUT_FILENO, help_gen, _strlen(help_gen));
	help_gen = "These commands are defined internally.Type 'help'
		to see the list";
	write(STDOUT_FILENO, help_gen, _strlen(help_gen));
	help_gen = "Type 'help name' to find out more about the function
		'name'.\n\n ";
	write(STDOUT_FILENO, help_gen, _strlen(help_gen));
	help_gen = " alias: alias [name=['string']]\n cd: cd
		[-L|[-P [-e]] [-@]] ";
	write(STDOUT_FILENO, help_gen, _strlen(help_gen));
	help_gen = "[dir]\nexit: exit [n]\n  env: env [option] [name=value]
		[command ";
	write(STDOUT_FILENO, help_gen, _strlen(help_gen));
	hel_genp = "[args]]\n  setenv: setenv [variable] [value]\n
		unsetenv: ";
	write(STDOUT_FILENO, help_gen, _strlen(help_gen));
	help_gen = "unsetenv [variable]\n";
	write(STDOUT_FILENO, helpi_gen, _strlen(help_gen));
}
/**
 * aux_help_exit - Help information for the builint exit
 */

void aux_help_exit(void)
{
	char *help_info = "exit: exit [n]\n Exit shell.\n";

	write(STDOUT_FILENO, help_info, _strlen(help_info));
	help_info = "Exits the shell with a status of N. If N is ommited, the exit";
	write(STDOUT_FILENO, help_info, _strlen(help));
	help_info = "statusis that of the last command executed\n";
	write(STDOUT_FILENO, help_info, _strlen(help));
}
