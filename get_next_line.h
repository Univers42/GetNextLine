#ifndef GNL_H
#define GNL_H
#include <stddef.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#define BUFFER_SIZE 1024
void *ft_calloc(size_t count, size_t size);
void *ft_memmove(void *dest, const void *src, size_t n);
char *ft_strndup(const char *s, size_t n);
char *ft_strchr(const char *s, int c);
#endif