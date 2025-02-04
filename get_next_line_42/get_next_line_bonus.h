#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#define BUFFER_SIZE 1024
typedef struct s_list
{
     char *content;
     struct s_list *next;
}t_list;

char *get_next_line(int fd)
{
    static t_list *buffer_list;
    char buf[BUFFER_SIZE + 1];
    int bytes_read;
    t_list *current;
    char *line;

    line = NULL;
    if (fd < 0)
        return (NULL);
    while((bytes_read = read(fd, buf, BUFFER_SIZE)) > 0)
        buf[bytes_read] = '\0';
    return (line);
}
