#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "get_next_line_bonus.h"

#define TEST_LINES 500000  // Number of lines to read per file

int main()
{
    int fd1 = open("file1.txt", O_RDONLY);
    int fd2 = open("file2.txt", O_RDONLY);
    int fd3 = open("file3.txt", O_RDONLY);

    if (fd1 < 0 || fd2 < 0 || fd3 < 0)
    {
        perror("Error opening files");
        return (1);
    }

    clock_t start_time = clock();
    char *line;
    int i = 0;

    while (i < TEST_LINES)
    {
        if ((line = get_next_line(fd1)))
        {
            free(line);
        }
        if ((line = get_next_line(fd2)))
        {
            free(line);
        }
        if ((line = get_next_line(fd3)))
        {
            free(line);
        }
        i++;
    }

    clock_t end_time = clock();
    double elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    printf("Read %d lines per file in %.2f seconds.\n", TEST_LINES, elapsed_time);
    
    close(fd1);
    close(fd2);
    close(fd3);
    
    return (0);
}
