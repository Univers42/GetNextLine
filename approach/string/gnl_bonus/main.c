#include "get_next_line_bonus.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define BLUE    "\x1b[34m"
#define RESET   "\x1b[0m"

int main(void)
{
    int fd1, fd2, fd3;
    char *line;
    char *line2;
    char *line3;

    fd1 = open("/home/dyl-syzygy/Universe42/Milestone1/GetNextLine/approach/string/gnl_bonus/file1.txt", O_RDONLY);
    fd2 = open("/home/dyl-syzygy/Universe42/Milestone1/GetNextLine/approach/string/gnl_bonus/file2.txt", O_RDONLY);
    fd3 = open("/home/dyl-syzygy/Universe42/Milestone1/GetNextLine/approach/string/gnl_bonus/file3.txt", O_RDONLY);

    if (fd1 < 0 || fd2 < 0 || fd3 < 0)
    {
        perror("Error opening file");
        return (1);
    }

    line = get_next_line(fd1);
    line2 = get_next_line(fd2);
    line3 = get_next_line(fd3);
    while (line || line2 || line3)
    {
        if (line)
        {
            printf(RED "File1: %s" RESET, line);
            free(line);
            line = get_next_line(fd1);
        }
        if (line2)
        {
            printf(GREEN "File2: %s" RESET, line2);
            free(line2);
            line2 = get_next_line(fd2);
        }
        if (line3)
        {
            printf(BLUE "File3: %s" RESET, line3);
            free(line3);
            line3 = get_next_line(fd3);
        }
    }
    close(fd1);
    close(fd2);
    close(fd3);
    return (0);
}
