#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "get_next_line.h"

int main(void)
{
    int fd = open("test_file.txt", O_RDONLY);
    char *l;

    if (fd < 0)
        return (perror("Error opening file"), 1);

    while ((l = get_next_line(fd)))
        printf("Line: %s", l), free(l);

    close(fd);
    return 0;
}