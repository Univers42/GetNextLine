#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

// Struct for tracking file descriptors dynamically
typedef struct s_fd_list {
    int fd;
    char *memory;
    struct s_fd_list *next;
} t_fd_list;

// Helper function to find newline position
static int find_newline(char *str)
{
    if (!str)
        return -1;
    char *ptr = str;
    while (*ptr)
    {
        if (*ptr == '\n')
            return ptr - str;
        ptr++;
    }
    return -1;
}

// Reads from fd and stores data in memory
static char *store_chunks(int fd, char *memory)
{
    char *buffer;
    int bytes_read;

    buffer = malloc(BUFFER_SIZE + 1);
    if (!buffer)
        return NULL;

    while (find_newline(memory) == -1)
    {
        bytes_read = read(fd, buffer, BUFFER_SIZE);
        if (bytes_read <= 0)
        {
            free(buffer);
            return (bytes_read == 0) ? memory : NULL;
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

    line = malloc(newline_idx + 2);
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

// Finds or creates a node for the given file descriptor
static t_fd_list *get_fd_node(t_fd_list **fd_list, int fd)
{
    t_fd_list *current = *fd_list;

    while (current)
    {
        if (current->fd == fd)
            return current;
        current = current->next;
    }

    // Create a new node if fd is not found
    t_fd_list *new_node = malloc(sizeof(t_fd_list));
    if (!new_node)
        return NULL;
    new_node->fd = fd;
    new_node->memory = NULL;
    new_node->next = *fd_list;
    *fd_list = new_node;
    return new_node;
}

// Removes a node from the linked list
static void remove_fd_node(t_fd_list **fd_list, int fd)
{
    t_fd_list *prev = NULL, *current = *fd_list;

    while (current)
    {
        if (current->fd == fd)
        {
            if (prev)
                prev->next = current->next;
            else
                *fd_list = current->next;
            free(current->memory);
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}

// Main function to read lines
char *get_next_line(int fd)
{
    static t_fd_list *fd_list = NULL;
    t_fd_list *fd_node;
    char *line;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return NULL;

    fd_node = get_fd_node(&fd_list, fd);
    if (!fd_node)
        return NULL;

    fd_node->memory = store_chunks(fd, fd_node->memory);
    if (!fd_node->memory)
    {
        remove_fd_node(&fd_list, fd);
        return NULL;
    }

    line = get_line(fd_node->memory);
    fd_node->memory = get_leftover(fd_node->memory);

    if (!line)
        remove_fd_node(&fd_list, fd);

    return line;
}
