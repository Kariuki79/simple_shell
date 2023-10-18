#include "shell.h"
/**
 * buffer_input - buffers chained commands for processing
 * @info: Parameter struct
 * @command_buffer: Address of the command buffer
 * @command_length: Address of the command length
 * Return: Number of bytes read
 */
ssize_t buffer_input(info_t *info, char **command_buffer, size_t *command_length)
{
	ssize_t bytes_read = 0;
	size_t buffer_length = 0;

	if (!*command_length)
	{
		free(*command_buffer);
		*command_buffer = NULL;
		signal(SIGINT, custom_sigintHandler);
		bytes_read = custom_getline(command_buffer, &buffer_length, stdin);

		if (bytes_read > 0)
		{
			if ((*command_buffer)[bytes_read - 1] == '\n')
			{
				(*command_buffer)[bytes_read - 1] = '\0';
				bytes_read--;
			}
			info->linecount_flag = 1;
			remove_comments(*command_buffer);
			build_custom_history(info, *command_buffer, info->histcount++)
				*command_length = bytes_read;
			info->cmd_buf = command_buffer;
		}
	}
}
return (bytes_read);
}

/**
 * get_input_line - retrieves a line without the newline character
 * @info: Parameter struct
 * Return: Number of bytes read
 */
ssize_t get_input_line(info_t *info)
{
    static char *command_buffer; // Command chain buffer
    static size_t current_position, chain_position, buffer_length;
    ssize_t bytes_read = 0;
    char **command_pointer = &(info->arg);
    char *command;

    custom_putchar(BUF_FLUSH);
    bytes_read = buffer_input(info, &command_buffer, &buffer_length);
    if (bytes_read == -1)
    {
        return -1; // EOF
    }
    if (buffer_length)
    {
        chain_position = current_position;
        command = command_buffer + current_position;

        custom_check_command_chain(info, command_buffer, &chain_position, current_position, buffer_length);
        while (chain_position < buffer_length)
        {
            if (custom_is_command_chain(info, command_buffer, &chain_position))
            {
                break;
            }
            chain_position++;
        }
        current_position = chain_position + 1;

        if (current_position >= buffer_length)
        {
            current_position = buffer_length = 0;
            info->cmd_buf_type = CMD_NORMAL;
        }

        *command_pointer = command;
        return custom_strlen(command);
    }

    *command_pointer = command_buffer;
    return bytes_read;
}

/**
 * read_buffer - reads from a buffer
 * @info: Parameter struct
 * @buffer: Buffer
 * @buffer_size: Size
 * Return: Number of bytes read
 */
ssize_t read_buffer(info_t *info, char *buffer, size_t *buffer_size)
{
    ssize_t bytes_read = 0;

    if (*buffer_size)
    {
        return 0;
    }
    bytes_read = read(info->readfd, buffer, READ_BUFFER_SIZE);
    if (bytes_read >= 0)
    {
        *buffer_size = bytes_read;
    }
    return bytes_read;
}

/**
 * custom_getline - fetches the next line from STDIN
 * @info: Parameter struct
 * @ptr: Address of pointer to buffer (preallocated or NULL)
 * @length: Size of the preallocated ptr buffer (if not NULL)
 * Return: Number of bytes read
 */
int custom_getline(info_t *info, char **ptr, size_t *length)
{
    static char buffer[READ_BUFFER_SIZE];
    static size_t current_position, buffer_length;
    size_t k;
    ssize_t bytes_read = 0, total_bytes_read = 0;
    char *p = NULL, *new_p = NULL, *c;

    p = *ptr;
    if (p && length)
    {
        total_bytes_read = *length;
    }
    if (current_position == buffer_length)
    {
        current_position = buffer_length = 0;
    }

    bytes_read = read_buffer(info, buffer, &buffer_length);
    if (bytes_read == -1 || (bytes_read == 0 && buffer_length == 0))
    {
        return -1; // EOF
    }

    c = _strchr(buffer + current_position, '\n');
    k = c ? 1 + (unsigned int)(c - buffer) : buffer_length;
    new_p = _realloc(p, total_bytes_read, total_bytes_read ? total_bytes_read + k : k + 1);
    if (!new_p)
    {
        return (p ? free(p), -1 : -1); // MALLOC FAILURE
   

