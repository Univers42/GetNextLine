#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char    *get_next_line(int fd);

#endif

// get_next_line_utils.c
#include "get_next_line.h"

size_t  ft_strlen(char *str)
{
    size_t len = 0;
    while (str && str[len])
        len++;
    return (len);
}

char    *ft_strchr(char *s, int c)
{
    if (!s)
        return (NULL);
    while (*s)
    {
        if (*s == (char)c)
            return (s);
        s++;
    }
    return (NULL);
}

char    *ft_strjoin(char *s1, char *s2)
{
    size_t  len1 = ft_strlen(s1);
    size_t  len2 = ft_strlen(s2);
    char    *new_str = malloc(len1 + len2 + 1);
    size_t  i = -1, j = -1;

    if (!new_str)
        return (NULL);
    while (++i < len1)
        new_str[i] = s1[i];
    while (++j < len2)
        new_str[i + j] = s2[j];
    new_str[i + j] = '\0';
    free(s1);
    return (new_str);
}

// get_next_line.c
#include "get_next_line.h"

char    *extract_line(char **stack)
{
    char    *line;
    char    *new_stack;
    size_t  i = 0;

    while ((*stack)[i] && (*stack)[i] != '\n')
        i++;
    line = malloc(i + 2);
    if (!line)
        return (NULL);
    line[i + 1] = '\0';
    while (i-- > 0)
        line[i] = (*stack)[i];
    if ((*stack)[i + 1] == '\n')
        line[i + 1] = '\n';
    new_stack = ft_strjoin(NULL, *stack + i + 2);
    free(*stack);
    *stack = new_stack;
    return (line);
}

char    *get_next_line(int fd)
{
    static char *stack;
    char        *buffer;
    ssize_t     bytes_read;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    buffer = malloc(BUFFER_SIZE + 1);
    if (!buffer)
        return (NULL);
    bytes_read = 1;
    while (!ft_strchr(stack, '\n') && bytes_read > 0)
    {
        bytes_read = read(fd, buffer, BUFFER_SIZE);
        if (bytes_read < 0)
        {
            free(buffer);
            return (NULL);
        }
        buffer[bytes_read] = '\0';
        stack = ft_strjoin(stack, buffer);
    }
    free(buffer);
    if (!stack || !*stack)
    {
        free(stack);
        stack = NULL;
        return (NULL);
    }
    return (extract_line(&stack));
}
