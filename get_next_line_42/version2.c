#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 42  // Default if not defined
#endif

/**
 * Read progressively (Buffer size bytes at a time)
 * Uses static storage per `fd` (supports multiple files)
 * handles \n correctly (returns exactly one line at a time)
 * Manages memory properly (avoids leaks and frees bufferes)
 * Works for multiple file descriptor (store content separately per fd)
 */
// Helper function to find a newline in the buffer

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 42  // Default if not defined
#endif

// Helper function to find a newline in the buffer
static int find_newline(char *str)
{
    int i = 0;
    if (!str)
        return -1;
    while (str[i])
    {
        if (str[i] == '\n')
            return i;
        i++;
    }
    return -1;
}

// Helper function to join two strings and free the first one
static char *ft_strjoin(char *s1, char *s2)
{
    int len1 = s1 ? 0 : strlen(s1);
    int len2 = s2 ? strlen(s2) : 0;
    char *new_str = malloc(len1 + len2 + 1);
    if (!new_str)
        return NULL;
    if (s1)
        strcpy(new_str, s1);
    if (s2)
        strcpy(new_str + len1, s2);
    free(s1);
    return new_str;
}

// Helper function to duplicate a string up to `len`
static char *ft_substr(char *s, int start, int len)
{
    if (start >= len || len <= 0)
        return NULL;
    char *sub = malloc(len + 1);
    if (!sub)
        return NULL;
    for (int i = 0; i < len; i++)
        sub[i] = s[start + i];
    sub[len] = '\0';
    return sub;
}

// Main get_next_line function
char *get_next_line(int fd)
{
    static char *buffer[1024]; // Supports multiple file descriptors
    char temp[BUFFER_SIZE + 1];
    char *line;
    int bytes_read, newline_pos;
    
    if (fd < 0 || BUFFER_SIZE <= 0)
        return NULL;

    // Read the file in chunks
    while ((newline_pos = find_newline(buffer[fd])) == -1)
    {
        bytes_read = read(fd, temp, BUFFER_SIZE);
        if (bytes_read <= 0) // EOF or error
            break;
        temp[bytes_read] = '\0';
        buffer[fd] = ft_strjoin(buffer[fd], temp);
    }

    // If buffer is empty and no bytes were read, return NULL
    if (!buffer[fd] || !buffer[fd][0])
        return (free(buffer[fd]), buffer[fd] = NULL, NULL);

    // Extract the line (including newline if present)
    newline_pos = find_newline(buffer[fd]);
    if (newline_pos == -1) // No newline found, return full buffer
        line = ft_substr(buffer[fd], 0, strlen(buffer[fd]));
    else
        line = ft_substr(buffer[fd], 0, newline_pos + 1);

    if (!line)
        return NULL;

    // Save remaining content in buffer[fd]
    char *new_buffer = buffer[fd][newline_pos + 1] ? ft_substr(buffer[fd], newline_pos + 1, strlen(buffer[fd]) - newline_pos - 1) : NULL;
    free(buffer[fd]);
    buffer[fd] = new_buffer;

    return line;
}

// Main function to test get_next_line
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        write(2, "Usage: ./a.out <filename>\n", 26);
        return 1;
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd == -1)
    {
        perror("Error opening file");
        return 1;
    }

    char *line;
    while ((line = get_next_line(fd)))
    {
        write(1, line, strlen(line));
        free(line);
    }

    close(fd);
    return 0;
}
