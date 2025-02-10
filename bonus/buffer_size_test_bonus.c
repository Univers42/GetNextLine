#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "get_next_line_bonus.h"

#define TEST_LINES 200000

int main()
{
    int fd = open("large_file.txt", O_RDONLY);
    if (fd < 0)
    {
        perror("Error opening file");
        return (1);
    }

    int buffer_sizes[] = {8, 32, 128, 512, 1024, 4096};
    int num_sizes = sizeof(buffer_sizes) / sizeof(buffer_sizes[0]);

    for (int i = 0; i < num_sizes; i++)
    {
        printf("\nTesting BUFFER_SIZE = %d\n", buffer_sizes[i]);

        // Redefine BUFFER_SIZE and recompile dynamically
        char command[256];
        sprintf(command, "gcc -D BUFFER_SIZE=%d -Wall -Wextra -Werror get_next_line_bonus.c get_next_line_utils_bonus.c buffer_size_test_bonus.c -o gnl_buffer_test", buffer_sizes[i]);
        system(command);

        clock_t start_time = clock();
        char *line;
        int line_count = 0;

        while ((line = get_next_line(fd)) && line_count < TEST_LINES)
        {
            free(line);
            line_count++;
        }

        clock_t end_time = clock();
        double elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

        printf("BUFFER_SIZE %d: Read %d lines in %.2f seconds.\n", buffer_sizes[i], TEST_LINES, elapsed_time);
        
        // Reset file position
        lseek(fd, 0, SEEK_SET);
    }

    close(fd);
    return (0);
}
