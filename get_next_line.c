#include "get_next_line.h"

char *get_next_line(int fd)
{
    static char *remainder;
    char *buffer;
    char *line;
    int bytes_read;
    size_t i;

    buffer = malloc(250 + 1);
    if (!buffer)
        return NULL;

    bytes_read = 1;
    while (bytes_read > 0)
    {
        bytes_read = read(fd, buffer, 250);
        if (bytes_read < 0)
        {
            free(buffer);
            return NULL;
        }
        buffer[bytes_read] = '\0';

        if (!remainder)
            remainder = ft_strdup("");

        char *new_remainder = ft_strjoin(remainder, buffer);
        free(remainder);
        remainder = new_remainder;

        i = 0;
        while (remainder[i] != '\n' && remainder[i] != '\0')
            i++;

        if (remainder[i] == '\n')
        {
            line = ft_substr(remainder, 0, i + 1);
            char *new_remainder = ft_strdup(&remainder[i + 1]);
            free(remainder);
            remainder = new_remainder;
            free(buffer);
            return line;
        }
        if (bytes_read == 0)
            break;
    }
    if (remainder && *remainder)
    {
        line = ft_strdup(remainder);
        free(remainder);
        remainder = NULL;
        free(buffer);
        return line;
    }

    free(buffer);
    return (NULL);
}
