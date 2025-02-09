#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 3
#endif
char *get_next_line(int fd)
{
    int bytes_read;
    char *cup_buffer;

    // Allocate memory for 4 bytes: 3 for data + 1 for null terminator
    cup_buffer = calloc(4, sizeof(char));  // Allocates 4 bytes
    if (cup_buffer == NULL)
        return (NULL);

    // Read up to 3 bytes from the file
    bytes_read = read(fd, cup_buffer, 3);
    
    // If nothing was read or an error occurred, free the buffer and return NULL
    if (bytes_read <= 0)
    {
        free(cup_buffer);  // Free the allocated memory
        return (NULL);
    }

    // Ensure the buffer is null-terminated (only if data was actually read)
    cup_buffer[bytes_read] = '\0';  // Null-terminate the string at the correct index

    return (cup_buffer);
}

int main(void)
{
    int fd;
    char *next_line;
    int count;

    count = 0;
    fd = open("text.txt", O_RDONLY);
    if (fd == -1)
    {
        printf("Error opening file\n");
        return (1);
    }

    while (1)
    {
        next_line = get_next_line(fd);
        if (next_line == NULL)
            break;
        count++;
        printf("[%d]:%s\n", count, next_line);
        free(next_line);
    }

    close(fd);
    return (0);
}
