#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdarg.h>
#include <fcntl.h>
#include <stdarg.h>
#include <unistd.h>

int main(void)
{
    int fd;
    char buf[256];
    int chars_read;

    fd = open("text.txt", O_RDONLY);
    if (fd == -1)
    {
        perror("Error opening file");
        return 1;
    }

    // Read in chunks of 5 characters
    while ((chars_read = read(fd, buf, 15)) > 0)
    {
        buf[chars_read] = '\0';  // Null-terminate the string
        printf("buf : %s\n", buf);  // Print the buffer content
    }

    if (chars_read == -1)
    {
        perror("Error reading file");
    }

    close(fd);  // Don't forget to close the file descriptor
    return 0;
}
