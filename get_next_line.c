#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#define BUFFER_SIZE 42

char *ft_strjoin(char *s1, char *s2)
{
    int len1 = 0;
    int len2 = 0;
    char *new;

    if (!s1)
        len1 = 0;
    else
        while (s1[len1])
            len1++;
    
    if (!s2)
        len2 = 0;
    else
        while (s2[len2])
            len2++;

    new = malloc(sizeof(char) * (len1 + len2 + 1));
    if (!new)
        return NULL;

    for (int i = 0; i < len1; i++)
        new[i] = s1[i];
    for (int i = 0; i < len2; i++)
        new[i + len1] = s2[i];
    new[len1 + len2] = '\0';

    free(s1);
    return new;
}

static char *ft_strchr(const char *str, int c)
{
    while (*str && *str != c)
        str++;
    if (*str == c)
        return (char *)str;
    return NULL;
}

int get_next_line(int fd, char **line)
{
    static char *stash[1024] = {NULL};
    char buffer[BUFFER_SIZE + 1];
    char *tmp;
    int bytes_read;

    if (fd < 0 || !line || BUFFER_SIZE <= 0)
        return (-1);

    buffer[0] = '\0';
    if (stash[fd])
    {
        tmp = stash[fd];
        stash[fd] = ft_strchr(tmp, '\n');
        if (stash[fd])
        {
            *(stash[fd]) = '\0';
            *line = tmp;
            stash[fd]++;
            return (1);
        }
        *line = tmp;
        free(tmp);
        stash[fd] = NULL;
        return (1);
    }

    bytes_read = read(fd, buffer, BUFFER_SIZE);
    while (bytes_read > 0)
    {
        buffer[bytes_read] = '\0';
        tmp = stash[fd];
        stash[fd] = ft_strjoin(tmp, buffer);

        if (!stash[fd])
            return (-1);

        if (ft_strchr(buffer, '\n'))
            break;
        bytes_read = read(fd, buffer, BUFFER_SIZE);
    }

    if (bytes_read == -1)
        return (-1);
    if (bytes_read == 0 && !stash[fd])
        return (0);

    *line = stash[fd];
    stash[fd] = ft_strchr(*line, '\n');
    if (stash[fd])
    {
        *(stash[fd]) = '\0';
        stash[fd]++;
    }
    else
        stash[fd] = NULL;

    return (1);
}

int main(int argc, char **argv)
{
    int fd;
    char *line;

    if (argc != 2)
        return 1;

    fd = open(argv[1], O_RDONLY);
    if (fd == -1)
        return 1;

    while (get_next_line(fd, &line) == 1)
    {
        printf("%s\n", line);
        free(line);
    }

    close(fd);
    return 0;
}