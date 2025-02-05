#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#ifndef BUFFER_SIZE
#define BUFFER_SIZE 42
#endif

static int find_newline(char *str);
static char *str_join(char *s1, char *s2, int len_s2);

/**
 * get_next_line - Reads a file line by line with a dynamic string builder.
 * @fd: The file descriptor to read from.
 * @line: The line that is read from the file.
 *
 * Return: 1 if a line is successfully read, 0 if EOF, -1 if an error occurs.
 */
int get_next_line(int fd, char **line)
{
    static char buffer[BUFFER_SIZE + 1];
    char *temp_line = NULL;
    int bytes_read;
    int total_len = 0;

    if (fd < 0 || !line || BUFFER_SIZE <= 0)
        return (-1);

    *line = malloc(1);  // Allocate memory for the line
    if (!*line)
        return (-1);
    (*line)[0] = '\0';  // Initialize it as an empty string

    while (1)
    {
        if (buffer[0] == '\0') // If the buffer is empty, we need to read more data
        {
            bytes_read = read(fd, buffer, BUFFER_SIZE);
            if (bytes_read <= 0)
                break;  // EOF or error, exit the loop
            buffer[bytes_read] = '\0'; // Null-terminate the read data
        }

        // Find the position of the newline or end of the buffer
        int i = 0;
        while (buffer[i] && buffer[i] != '\n')
            i++;

        // Allocate a temporary string to join with the previous part of the line
        temp_line = str_join(*line, buffer, i);
        if (!temp_line)
            return (-1);

        free(*line);  // Free the old line, we're using the new one now
        *line = temp_line;
        total_len += i;

        // If a newline was found, terminate the line and shift the buffer
        if (buffer[i] == '\n')
        {
            memmove(buffer, buffer + i + 1, bytes_read - i); // Shift remaining buffer
            return (1);  // Return the line (including newline character)
        }
        else
            memmove(buffer, buffer + i, bytes_read - i);
    }

    if (total_len == 0)  // If no data was read, return NULL (EOF)
    {
        free(*line);
        return (0);
    }

    return (1);  // Return the accumulated line
}

/**
 * str_join - Concatenates two strings (s1 + s2) and returns the new string.
 * @s1: The first string (destination).
 * @s2: The second string (source).
 * @len_s2: The length of s2 to join.
 *
 * Return: A new dynamically allocated string containing s1 + s2.
 */
static char *str_join(char *s1, char *s2, int len_s2)
{
    int len_s1 = 0;
    char *new_str;

    // Find the length of s1
    if (s1)
        while (s1[len_s1])
            len_s1++;

    // Allocate memory for the new string (s1 + s2 + null terminator)
    new_str = malloc(len_s1 + len_s2 + 1);
    if (!new_str)
        return (NULL);

    // Copy s1 into new_str
    int i = 0;
    for (; i < len_s1; i++)
        new_str[i] = s1[i];

    // Copy s2 into new_str
    for (int j = 0; j < len_s2; j++, i++)
        new_str[i] = s2[j];

    new_str[i] = '\0';  // Null-terminate the new string
    return (new_str);
}

int main()
{
    int fd = open("text.txt", O_RDONLY);
    char *line;

    if (fd < 0)
        return (1);

    while (get_next_line(fd, &line) > 0)
    {
        printf("Line: %s\n", line);
        free(line);  // Free the line after printing
    }

    close(fd);
    return (0);
}
