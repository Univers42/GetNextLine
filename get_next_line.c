#include <stdlib.h>
#include <unistd.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 42  // Default buffer size
#endif

// Helper function to find newline position
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

// Helper function to join two strings and free the old memory
static char *str_join(char *s1, char *s2)
{
    int i = 0, j = 0, len1 = 0, len2 = 0;
    char *new_str;

    if (s1)
        while (s1[len1]) len1++;
    while (s2[len2]) len2++;

    new_str = malloc(len1 + len2 + 1);
    if (!new_str)
        return NULL;

    while (i < len1)
    {
        new_str[i] = s1[i];
        i++;
    }
    while (j < len2)
    {
        new_str[i++] = s2[j++];
    }
    new_str[i] = '\0';

    free(s1);
    return new_str;
}

// Reads from fd and stores data in memory
static char *store_chunks(int fd, char *memory)
{
    char buffer[BUFFER_SIZE + 1];
    int bytes_read;
    
    while (find_newline(memory) == -1)
    {
        bytes_read = read(fd, buffer, BUFFER_SIZE);
        if (bytes_read <= 0)
            return memory; 

        buffer[bytes_read] = '\0';
        memory = str_join(memory, buffer);
        if (!memory)
            return NULL;
    }
    return memory;
}

// Extracts the next line from memory
static char *get_line(char *memory)
{
    int i = 0;
    char *line;
    
    if (!memory || !memory[0])
        return NULL;

    while (memory[i] && memory[i] != '\n')
        i++;
    
    line = malloc(i + 2);
    if (!line)
        return NULL;

    for (int j = 0; j <= i; j++)
        line[j] = memory[j];
    line[i + 1] = '\0';

    return line;
}

// Keeps only the leftover part of memory after '\n'
static char *get_leftover(char *memory)
{
    int i = 0, j = 0;
    char *leftover;

    while (memory[i] && memory[i] != '\n')
        i++;
    if (!memory[i])
    {
        free(memory);
        return NULL;
    }

    leftover = malloc(sizeof(char) * (strlen(memory) - i));
    if (!leftover)
        return NULL;

    i++;  // Skip past '\n'
    while (memory[i])
        leftover[j++] = memory[i++];
    leftover[j] = '\0';

    free(memory);
    return leftover;
}

// Main get_next_line function
char *get_next_line(int fd)
{
    static char *memory;
    char *line;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return NULL;

    memory = store_chunks(fd, memory);
    if (!memory)
        return NULL;

    line = get_line(memory);
    memory = get_leftover(memory);

    return line;
}