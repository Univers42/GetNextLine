#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "get_next_line.h"  // Include your header where `get_next_line` is declared
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "get_next_line.h"

void read_file(int fd, const char *filename)
{
    char *line;

    printf("\nReading from %s:\n", filename);
    while ((line = get_next_line(fd)))
    {
        printf("%s", line);
        free(line);
    }
}

int main()
{
    int fd1 = open("file1.txt", O_RDONLY);
    int fd2 = open("file2.txt", O_RDONLY);

    if (fd1 < 0 || fd2 < 0)
    {
        perror("Error opening file");
        return (fd1 > 0) ? (close(fd1), 1) : 1;
    }

    read_file(fd1, "file1.txt");
    read_file(fd2, "file2.txt");

    close(fd1);
    close(fd2);
    return 0;
}
