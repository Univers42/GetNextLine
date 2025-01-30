#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "get_next_line.h"  // Include your header where `get_next_line` is declared

int main()
{
    int fd1, fd2;
    char *line;

    // Open multiple files
    fd1 = open("file1.txt", O_RDONLY);
    if (fd1 < 0) {
        perror("Error opening file1.txt");
        return 1;
    }

    fd2 = open("file2.txt", O_RDONLY);
    if (fd2 < 0) {
        perror("Error opening file2.txt");
        return 1;
    }

    // Read lines from file1.txt
    printf("Reading from file1.txt:\n");
    while ((line = get_next_line(fd1)) != NULL) {
        printf("file1: %s", line);  // Print the line
        free(line);  // Free the memory allocated by get_next_line
    }

    // Read lines from file2.txt
    printf("\nReading from file2.txt:\n");
    while ((line = get_next_line(fd2)) != NULL) {
        printf("file2: %s", line);  // Print the line
        free(line);  // Free the memory allocated by get_next_line
    }

    // Close the files
    close(fd1);
    close(fd2);

    return 0;
}
