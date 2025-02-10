#include "get_next_line.h"

char *fill_line(char *str)
{
    char *next_line;
    while()
}
int verif_end_line(char *str)
{
    ft_strchr(str, '\n');
    return (0);
}
// we assume that everything is correct. With this line we have already the line until \n
char *store_chunks(int fd, char *line)
{
    ssize_t bytes_read;
    char *chunk;
    
    chunk = calloc(sizeof(char), BUFFER_SIZE);
    if(!chunk)
        return NULL;
    while(bytes_read > 0 && !ft_strchr(line, '\n'))
    {
        bytes_read = read(fd, chunk, BUFFER_SIZE - 1);
        if(bytes_read < 0)
        {
            free(chunk);
            return NULL;
        }
        chunk[bytes] = '\0';
        line = ft_strjoin(line, chunk);
    }
    free(chunk);

}

char *get_line(char *line)
{
    char *line;
    size_t len;

    len = ft_strclen(memory, '\n');
    if(memory[len] == '\n')
        len++:
    
}
char *get_next_line(int fd)
{
    int bytes_read;
    char *cup_buffer;
    char *line;
    cup_buffer = calloc(4, sizeof(char));
    if (cup_buffer == NULL)
        return (NULL);
    line = get_line;
    bytes_read = read(fd, cup_buffer, BUFFER_SIZE - 1);
    if (bytes_read <= 0)
    {
        free(cup_buffer);
        return (NULL);
    }
    cup_buffer[bytes_read] = '\0';
    return (cup_buffer);
}

int main(void)
{
    int fd;
    char *next_line;
    int count;

    count = 0;
    fd = open("text.txt", O_RDONLY);
    if (fd == -1)
    {
        printf("Error opening file\n");
        return (1);
    }
    while (1)
    {
        next_line = get_next_line(fd);
        if (next_line == NULL)
            break;
        count++;
        printf("[%d]:%s\n", count, next_line);
        free(next_line);
    }
    close(fd);
    return (0);
}
