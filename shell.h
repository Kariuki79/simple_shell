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

/* For 2-handle_arguments */
void handle_command(char *buffer);

/* declaring environ in 2-handle file */
extern char **environ;
int find_executable_in_path(const char *command, char *full_path, size_t max_length);

/* toem_realloc.c */
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* toem_memory.c */
int bfree(void **);

/* toem_getinfo.c */
void initialize_info(info_t *);
void configure_info(info_t *, char **);
void deallocate_info(info_t *, int);

/* toem_parser.c */
int is_cmd(info_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(info_t *, char *, char *);

#endif
