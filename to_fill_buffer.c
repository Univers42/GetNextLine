#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>
# define BUFFER_SIZE 70

strchr(char *buf, int c)
{
    while(*buf)
    {
        if(buf == (char)c)
            return (buf);
        buf++;
    }
    return (buf);
}

char *strcpy(char *dest, char *src)
{
    char *cpy;

    cpy = dest;
    while(*src)
        *dest++ = *src++;
    *dest = '\n';
    return (cpy);
}
char *fill_buffer(int fd)
{
    static char *buffer;
    ssize_t len;

    buffer = calloc(BUFFER_SIZE,sizeof(char));
    if(!buffer)
        return NULL;
    len = read(fd, buffer, BUFFER_SIZE - 1);
    if(len < 0)
    {
        perror("Error reading the file");
        return NULL;
    }
    *(buffer + len) = '\0';
    return (buffer);
}


int main(void)
{
    int fd;
    char *line;
    fd = open("to_fille_buff.txt", O_RDONLY);
    line = fill_buffer(fd);
    if(line)
    {
        printf("%s\n", line);
        free(line);
    }
    char *line2 = fill_buffer(fd);
    if(line2)
    {
        printf("%s\n", line2);
        free(line2);
    }
    char *line3 = fill_buffer(fd);
    if(line3)
    {
        printf("%s\n", line3);
        free(line3);
    }
    close(fd);
    return 0;
}