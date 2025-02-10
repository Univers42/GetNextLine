#include <fcntl.h>
#include <stdio.h>
#include "get_next_line_bonus.h"

int main()
{
    int fd1 = open("file1.txt", O_RDONLY);
    int fd2 = open("file2.txt", O_RDONLY);
    int fd3 = open("file3.txt", O_RDONLY);
    
    char *line1, *line2, *line3;

    for (int i = 0; i < 3; i++) // Read 3 lines from each file
    {
        line1 = get_next_line(fd1);
        printf("FD1: %s", line1);
        free(line1);

        line2 = get_next_line(fd2);
        printf("FD2: %s", line2);
        free(line2);

        line3 = get_next_line(fd3);
        printf("FD3: %s", line3);
        free(line3);
    }

    close(fd1);
    close(fd2);
    close(fd3);

    return 0;
}
