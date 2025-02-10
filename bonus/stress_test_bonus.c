#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "get_next_line_bonus.h"

#define TEST_LINES 1000000  // Number of lines to read

int main()
{
    int fd = open("large_file.txt", O_RDONLY);
    if (fd < 0)
    {
        perror("Error opening file");
        return (1);
    }

    clock_t start_time = clock();  // Start timer
    char *line;
    int line_count = 0;

    while ((line = get_next_line(fd)) && line_count < TEST_LINES)
    {
        free(line);  // Free each line after use
        line_count++;
    }

    clock_t end_time = clock();  // End timer
    double elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    printf("Read %d lines in %.2f seconds.\n", line_count, elapsed_time);
    close(fd);
    return (0);
}
