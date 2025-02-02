#include "get_next_line.h"

char *get_next_line_bonus(int fd)
{
    static char *remainders[1024];  // Static array to handle multiple file descriptors
    char *buffer, *line, *newline_pos, *new_remainder;
    int bytes_read;

    if (fd < 0 || !(buffer = malloc(BUFFER_SIZE + 1)))
        return NULL;

    // Read data into the buffer
    while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0)
    {
        buffer[bytes_read] = '\0';
        // Append the buffer content to the remainder
        remainders[fd] = remainders[fd] ? ft_strjoin(remainders[fd], buffer) : ft_strdup(buffer);

        // Look for the newline character in the remainder
        if ((newline_pos = ft_strchr(remainders[fd], '\n')))
        {
            // Extract the line up to the newline character
            line = ft_substr(remainders[fd], 0, newline_pos - remainders[fd] + 1);
            // Create a new remainder from the content after the newline
            new_remainder = ft_strdup(newline_pos + 1);
            free(remainders[fd]);
            remainders[fd] = new_remainder;
            free(buffer);
            return line;
        }
    }

    // If no newline found, return the remaining content
    free(buffer);
    if (remainders[fd] && *remainders[fd])
    {
        line = ft_strdup(remainders[fd]);
        free(remainders[fd]);
        remainders[fd] = NULL;
        return line;
    }

    return NULL;
}

void read_file(int fd, const char *filename)
{
    char *line;

    printf("\nReading from %s:\n", filename);
    while ((line = get_next_line_bonus(fd)) != NULL)
    {
        printf("%s", line);  // Print the line
        free(line);  // Free the memory allocated by get_next_line_bonus
    }
}

int main()
{
    int fd1, fd2;

    // Open two files for reading
    fd1 = open("file1.txt", O_RDONLY);
    if (fd1 < 0)
    {
        perror("Error opening file1.txt");
        return 1;
    }

    fd2 = open("file2.txt", O_RDONLY);
    if (fd2 < 0)
    {
        perror("Error opening file2.txt");
        close(fd1);
        return 1;
    }

    // Read and print lines from the first file
    read_file(fd1, "file1.txt");

    // Read and print lines from the second file
    read_file(fd2, "file2.txt");

    // Close both files
    close(fd1);
    close(fd2);

    return 0;
}