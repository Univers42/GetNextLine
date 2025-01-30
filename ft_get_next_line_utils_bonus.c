#include "get_next_line.h"

static char *get_remainder_for_fd(int fd)
{
    static char *remainder[1024];  // Array to hold the remainder for each fd

    // If remainder[fd] is NULL, initialize it
    if (!remainder[fd])
        remainder[fd] = ft_strdup("");
    
    return remainder[fd];
}

char *get_next_line(int fd)
{
    char *buffer;
    char *line;
    int bytes_read;
    size_t i;
    static char *remainder[1024]; // Array for tracking remainder of each fd

    // Allocate memory for the buffer
    buffer = malloc(250 + 1);  // Adjust to the buffer size you want
    if (!buffer)
        return NULL;

    bytes_read = 1;  // Initialize to 1 to enter the loop
    while (bytes_read > 0)
    {
        bytes_read = read(fd, buffer, 250);  // Read up to 250 bytes
        if (bytes_read < 0)  // Check for read error
        {
            free(buffer);
            return NULL;
        }
        buffer[bytes_read] = '\0';  // Null-terminate the buffer

        // Get the static remainder for the current fd
        char *remainder_fd = get_remainder_for_fd(fd);

        // Append the contents of buffer to remainder_fd
        char *new_remainder = ft_strjoin(remainder_fd, buffer);
        free(remainder_fd);  // Free old remainder
        remainder_fd = new_remainder;  // Update remainder_fd

        // Find the newline character in the remainder_fd
        i = 0;
        while (remainder_fd[i] != '\n' && remainder_fd[i] != '\0')
            i++;

        // If there's a newline, return the line
        if (remainder_fd[i] == '\n')
        {
            line = ft_substr(remainder_fd, 0, i + 1);  // Include newline in the line
            char *new_remainder = ft_strdup(&remainder_fd[i + 1]);  // Keep the rest as remainder_fd
            free(remainder_fd);  // Free the old remainder
            remainder_fd = new_remainder;  // Update remainder_fd
            free(buffer);  // Free the buffer
            return line;
        }
    }

    // If no newline was found, return the last portion of remainder_fd
    if (remainder_fd && *remainder_fd)
    {
        line = ft_strdup(remainder_fd);
        free(remainder_fd);
        remainder_fd = NULL;
        free(buffer);  // Free the buffer
        return line;
    }

    free(buffer);  // Free the buffer
    return NULL;  // Return NULL if no data was read
}
