#include "get_next_line_bonus.h"

char *extract_line(char *storage)
{
    int i = 0;
    while (storage[i] && storage[i] != '\n')
        i++;

    char *line = (char *)malloc(i + 2); // +1 for '\n', +1 for '\0'
    if (!line)
        return NULL;

    for (int j = 0; j <= i; j++)
        line[j] = storage[j];
    line[i + 1] = '\0';
    
    return line;
}

char *trim_remainder(char *storage)
{
    int i = 0, j = 0;
    while (storage[i] && storage[i] != '\n')
        i++;

    if (!storage[i])  // No newline, free storage
    {
        free(storage);
        return NULL;
    }

    char *new_storage = (char *)malloc(ft_strlen(storage) - i);
    if (!new_storage)
        return NULL;

    i++; // Skip '\n'
    while (storage[i])
        new_storage[j++] = storage[i++];
    new_storage[j] = '\0';

    free(storage);
    return new_storage;
}

char *get_next_line(int fd)
{
    static char *storage[MAX_FD];  // Array for multiple FDs
    char buffer[BUFFER_SIZE + 1];
    char *line;
    int bytes_read;

    if (fd < 0 || fd >= MAX_FD || BUFFER_SIZE <= 0)
        return NULL;

    while (!ft_strchr(storage[fd], '\n') && (bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0)
    {
        buffer[bytes_read] = '\0';
        storage[fd] = ft_strjoin(storage[fd], buffer);
    }
    if (!storage[fd] || *storage[fd] == '\0')
    {
        free(storage[fd]);
        storage[fd] = NULL;
        return NULL;
    }
    line = extract_line(storage[fd]);
    storage[fd] = trim_remainder(storage[fd]);
    return line;
}
