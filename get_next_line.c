/**
 * 
 * STATIC ARRAY APPROACH
 */

static char *stash[1024] = {NULL};

int get_next_line(int fd, char **line)
{
    static char buffer[BUFFER_SIZE + 1];
    int bytes_read;
    char *tmp;

    while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0)
    {
        buffer[bytes_read] = '\0';
        
        if (!stash[fd])
            stash[fd] = ft_strnew(1);
            
        tmp = stash[fd];
        stash[fd] = ft_strjoin(stash[fd], buffer);

        if (!stash[fd])
            return (-1);

        if (ft_strchr(buffer, '\n'))
            break;
    }

    // Process line extraction...
}