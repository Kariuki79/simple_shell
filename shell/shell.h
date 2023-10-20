#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* declaring environ in 2-handle file */
extern char **environ;

void handle_command(char *buffer);
int find_executable_in_path(const char *command, char *full_path, size_t max_length);

int bfree(void **);

#endif

