#include "shell.h"

/**
 * initialize_info - sets initial values for info_t struct
 * @info: Address of the info_t struct
 */
void initialize_info(info_t *info)
{
    info->arguments = NULL;
    info->argument_vector = NULL;
    info->path = NULL;
    info->argument_count = 0;
}

/**
 * configure_info - configures the info_t struct with user input
 * @info: Address of the info_t struct
 * @arguments: Argument vector
 */
void configure_info(info_t *info, char **arguments)
{
    int index = 0;

    info->program_name = arguments[0];
    if (info->arguments)
    {
        info->argument_vector = split_string(info->arguments, " \t");
        if (!info->argument_vector)
        {
            info->argument_vector = malloc(sizeof(char *) * 2);
            if (info->argument_vector)
            {
                info->argument_vector[0] = duplicate_string(info->arguments);
                info->argument_vector[1] = NULL;
            }
        }
        for (index = 0; info->argument_vector && info->argument_vector[index]; index++)
            ;
        info->argument_count = index;

        replace_aliases(info);
        replace_variables(info);
    }
}

/**
 * deallocate_info - frees allocated memory in the info_t struct
 * @info: Address of the info_t struct
 * @release_all: True if all fields should be freed
 */
void deallocate_info(info_t *info, int release_all)
{
    free_string_array(info->argument_vector);
    info->argument_vector = NULL;
    info->path = NULL;
    if (release_all)
    {
        if (!info->command_buffer)
            free(info->arguments);
        if (info->environment)
            free_list(&(info->environment));
        if (info->history)
            free_list(&(info->history));
        if (info->aliases)
            free_list(&(info->aliases));
        free_string_array(info->environment_variables);
        info->environment_variables = NULL;
        batch_free((void **)info->command_buffer);
        if (info->read_file_descriptor > 2)
            close(info->read_file_descriptor);
        write(2, BUF_FLUSH, 1);
    }
}

