#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#ifndef MAX_FD
    #define MAX_FD 1024  // Define a maximum number of file descriptors to track
#endif

// Helper function to find newline position
static int find_newline(char *str)
{
    if (!str)
        return -1;
    
    char *ptr = str;
    while (*ptr)
    {
        if (*ptr == '\n')
            return (ptr - str);  // Return the index of the newline
        ptr++;
    }
    return -1;
}

// Reads from fd and stores data in memory efficiently
static char *store_chunks(int fd, char *memory)
{
    char *buffer;
    int bytes_read;

    bytes_read = 1;
    buffer = malloc(BUFFER_SIZE + 1);
    if (!buffer)
        return NULL;

    while (find_newline(memory) == -1 && bytes_read > 0)
    {
        bytes_read = read(fd, buffer, BUFFER_SIZE);
        if (bytes_read < 0)
        {
            free(buffer);
            return NULL;
        }
        
        buffer[bytes_read] = '\0';
        memory = ft_strjoin(memory, buffer);
        if (!memory)
        {
            free(buffer);
            return NULL;
        }
    }
    free(buffer);
    return memory;
}

// Extracts the line from memory
static char *get_line(char *memory)
{
    char *line;
    int newline_idx;

    if (!memory || !*memory)
        return NULL;

    newline_idx = find_newline(memory);
    if (newline_idx == -1)
        newline_idx = strlen(memory);

    line = malloc(newline_idx + 2);  // +2 for newline and null-terminator
    if (!line)
        return NULL;

    memmove(line, memory, newline_idx + 1);
    line[newline_idx + 1] = '\0';

    return (line);
}

// Keeps only the leftover part of memory after '\n'
static char *get_leftover(char *memory)
{
    char *ptr;
    char *leftover;

    ptr = memory;
    while (*ptr && *ptr != '\n')
        ptr++;

    if (!*ptr)
    {
        free(memory);
        return NULL;
    }

    leftover = strdup(ptr + 1);
    free(memory);
    return leftover;
}

// Main function to read lines
char *get_next_line(int fd)
{
    static char *memory[MAX_FD];
    char *line;

    if (fd < 0 || fd >= MAX_FD || BUFFER_SIZE <= 0)
        return NULL;

    *(memory + fd) = store_chunks(fd, *(memory + fd));
    if (!*(memory + fd))
        return NULL;

    line = get_line(*(memory + fd));
    *(memory + fd) = get_leftover(*(memory + fd));
    return line;
}

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include "get_next_line.h"

int main(void)
{
    char *line;
    int fd1, fd2;
    int i;

    // Test 1: Reading from a regular file
    printf("Test 1: Reading from regular file\n");
    fd1 = open("test.txt", O_RDONLY);
    if (fd1 == -1)
    {
        printf("Error opening test.txt\n");
        return (1);
    }

    i = 1;
    while ((line = get_next_line(fd1)) != NULL)
    {
        printf("Line %d: %s", i, line);
        free(line);
        i++;
    }
    printf("End of file reached\n");
    close(fd1);

    // Test 2: Multiple file descriptors (bonus part)
    printf("\nTest 2: Multiple file descriptors\n");
    fd1 = open("test1.txt", O_RDONLY);
    fd2 = open("test2.txt", O_RDONLY);
    if (fd1 == -1 || fd2 == -1)
    {
        printf("Error opening test files\n");
        return (1);
    }

    i = 1;
    while ((line = get_next_line(fd1)) != NULL || 
           (line = get_next_line(fd2)) != NULL)
    {
        if (line != NULL)
        {
            printf("Line %d: %s", i, line);
            free(line);
            i++;
        }
    }
    printf("End of both files reached\n");
    close(fd1);
    close(fd2);

    // Test 3: Empty file
    printf("\nTest 3: Empty file\n");
    fd1 = open("empty.txt", O_RDONLY);
    if (fd1 == -1)
    {
        printf("Error opening empty.txt\n");
        return (1);
    }

    line = get_next_line(fd1);
    if (line == NULL)
        printf("Successfully handled empty file\n");
    else
        printf("Error: Empty file test failed\n");
    close(fd1);

    return (0);
}