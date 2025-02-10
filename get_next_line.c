#include "get_next_line.h"

char *get_line(char *str)
{
    int i = 0;
    while (str[i] && str[i] != '\n')
        i++;
    char *line = (char *)malloc(i + 2);
    if (!line)
        return NULL;
    for (int j = 0; j <= i; j++)
        line[j] = str[j];
    line[i + 1] = '\0';
    return line;
}

char *trim_remainder(char *str)
{
    int i = 0, j = 0;
    while (str[i] && str[i] != '\n')
        i++;
    if (!str[i])
    {
        free(str);
        return NULL;
    }
    char *remainder = (char *)malloc(ft_strlen(str) - i);
    if (!remainder)
        return NULL;
    i++; // Skip '\n'
    while (str[i])
        remainder[j++] = str[i++];
    remainder[j] = '\0';
    free(str);
    return remainder;
}

char *get_next_line(int fd)
{
    static char *storage;  // Stores leftover content (allowed in bonus)
    char buffer[BUFFER_SIZE + 1];
    char *line;
    int bytes_read;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return NULL;

    while (!ft_strchr(storage, '\n') && (bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0)
    {
        buffer[bytes_read] = '\0';
        storage = ft_strjoin(storage, buffer);
    }
    if (!storage || *storage == '\0')
    {
        free(storage);
        storage = NULL;
        return NULL;
    }
    line = get_line(storage);
    storage = trim_remainder(storage);
    return line;
}
