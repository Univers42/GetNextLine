#include "get_next_line.h"

char *get_next_line(int fd)
{
    static char *remainder;
    char *buffer;
    char *line;
    int bytes_read;
    size_t i;

    // Allocate memory for buffer
    buffer = malloc(250 + 1);  // Use buffer size of 250
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

        // If remainder is NULL, initialize it as an empty string
        if (!remainder)
            remainder = ft_strdup("");

        // Append the contents of buffer to remainder
        char *new_remainder = ft_strjoin(remainder, buffer);
        free(remainder);  // Free old remainder
        remainder = new_remainder;  // Update remainder

        // Find the newline character in the remainder
        i = 0;
        while (remainder[i] != '\n' && remainder[i] != '\0')
            i++;

        // If there's a newline, return the line
        if (remainder[i] == '\n')
        {
            line = ft_substr(remainder, 0, i + 1);  // Include newline in the line
            char *new_remainder = ft_strdup(&remainder[i + 1]);  // Keep the rest as remainder
            free(remainder);  // Free the old remainder
            remainder = new_remainder;  // Update remainder
            free(buffer);  // Free the buffer
            return line;
        }

        // If no newline is found, continue reading more data
        if (bytes_read == 0)  // If EOF is reached, break out of loop
            break;
    }

    // If no newline was found, return the last portion of remainder
    if (remainder && *remainder)
    {
        line = ft_strdup(remainder);
        free(remainder);
        remainder = NULL;
        free(buffer);  // Free the buffer
        return line;
    }

    free(buffer);  // Free the buffer
    return NULL;  // Return NULL if no data was read
}
