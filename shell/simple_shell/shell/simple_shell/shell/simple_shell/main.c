#include "shell.h"

/**
 * main - entry point
 * @ac: Argument count
 * @av: Argument vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int argc, char **argv)
{
	info_t info[] = { INFO_INIT };
	int custom_fd = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (custom_fd)
			: "r" (custom_fd));

	if (argc == 2)
	{
		custom_fd = open(argv[1], O_RDONLY);
		if (custom_fd == -1)
		{

			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				eputs(argv[0]);
				eputs(": 0: Can't open ");
				eputs(argv[1]);
				eputchar('\n');
				eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = custom_fd;
	}
	populate_env_list(info);
	read_history(info);
	hsh(info, argv);
	return (EXIT_SUCCESS);
}
