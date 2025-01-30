#include <stdio.h>
#include <fcntl.h>  // For open()
#include <unistd.h> // For close()

#include "get_next_line.h"

int main(void)
{
    int fd = open("test_file.txt", O_RDONLY);  // Open the test file for reading
    if (fd == -1)
    {
        perror("Error opening file");
        return 1;
    }

    char *line;
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("Line: %s", line);  // Print each line read
        free(line);  // Free the memory allocated for the line
    }

    close(fd);  // Close the file when done
    return 0;
}
