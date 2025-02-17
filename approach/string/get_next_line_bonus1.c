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
            return ptr - str;  // Return the index of the newline
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

    return line;
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

    memory[fd] = store_chunks(fd, memory[fd]);
    if (!memory[fd])
        return NULL;

    line = get_line(memory[fd]);
    memory[fd] = get_leftover(memory[fd]);
    return line;
}
