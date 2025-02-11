#include "get_next_line.h"

char *get_line(char *buffer)
{
    ssize_t len;
    char *new_line;

    len = 0;
    if(!buffer)
    {
        fprintf(stderr, "the buffer is empty, nothing to copy");
        return NULL;
    }
    len = ft_strclen(buffer, '\n');
    if (buffer[len] == '\n')
        len++;
    new_line =  ft_strndup(buffer, len);
    if (!new_line)
        return (NULL);
    return (new_line);     
}
/**
 * question that rise !
 * wha
 * 
 */
char *fill_chunks(int fd, char *buffer)
{

    char *new_line;
    ssize_t bytes;

    new_line = malloc(BUFFER_SIZE + 1);
    if(fd < 0)
    {
        fprintf(stderr, "Error with the file fd");
        return (NULL);
    }
    if(!buffer)
    {
        fprintf(stderr, "");
        return 1;
    }
    while(bytes > 0 && ft_strchr(buffer, '\n'))
    {
        bytes = read(fd, buffer, BUFFER_SIZE - 1);
        if(bytes == 0)
            break;
        if (bytes < 0)
        {
            free(new_line);
            return  (NULL);
        }
        *(buffer + bytes) = '\0';
        buffer = ft_strjoin(buffer, new_line);
    }
    free(buffer);
    if (ft_strclen(buffer, '\0') > 0)
        return (buffer);
    return (NULL);
}

/**
 * [] fill the buffer
 * [] duplicate it
 * [] liberate the memory
 */
char *get_next_line(int fd)
{
    static char *buffer;
    char *line;
    
    if(fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    buffer = fill_chunks(fd, buffer);
    if(!buffer)
        return (NULL);
    //we liberate the buffer duplicating it safely
    buffer = get_line(buffer);

    if(!line)
}

int main(int argc, char **argv)
{
    static char *line;
    ssize_t size;
    int fd;
    
    if(argc !=  2)
    {
        fprintf(stderr, "./usage file.txt");
        return (1);
    }
    fd = open(argv[1], O_RDONLY);
    

    while(size = get_next_line(fd))
    {
               
    }
    return (0);
}