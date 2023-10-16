#include "custom_shell.h"

/**
 * custom_main - entry point
 * @arg_count: Argument count
 * @arg_vector: Argument vector
 *
 * Return: 0 on success, 1 on error
 */
int custom_main(int arg_count, char **arg_vector)
{
    info_t custom_info[] = { CUSTOM_INFO_INIT };
    int custom_fd = 2;

    asm ("mov %1, %0\n\t"
        "add $3, %0"
        : "=r" (custom_fd)
        : "r" (custom_fd));

    if (arg_count == 2)
    {
        custom_fd = custom_open(arg_vector[1], O_RDONLY);
        if (custom_fd == -1)
        {
            if (errno == EACCES)
                exit(126);
            if (errno == ENOENT)
            {
                custom_eputs(arg_vector[0]);
                custom_eputs(": 0: Can't open ");
                custom_eputs(arg_vector[1]);
                custom_eputchar('\n');
                custom_eputchar(CUSTOM_BUF_FLUSH);
                exit(127);
            }
            return EXIT_FAILURE;
        }
        custom_info->read_fd = custom_fd;
    }

    custom_populate_env_list(custom_info);
    custom_read_history(custom_info);
    custom_hsh(custom_info, arg_vector);
    return EXIT_SUCCESS;
}

