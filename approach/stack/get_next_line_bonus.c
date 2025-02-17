#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>

// Struct for managing FD buffers using a stack (linked list)
typedef struct s_fd_stack {
    int fd;
    char *buffer;
    struct s_fd_stack *next;
} t_fd_stack;

// Find or create an FD node in the stack
t_fd_stack *get_fd_node(t_fd_stack **stack, int fd) {
    t_fd_stack *temp = *stack;

    while (temp) {
        if (temp->fd == fd)
            return temp;
        temp = temp->next;
    }

    t_fd_stack *new_node = malloc(sizeof(t_fd_stack));
    if (!new_node)
        return NULL;
    new_node->fd = fd;
    new_node->buffer = NULL;
    new_node->next = *stack;
    *stack = new_node;
    return new_node;
}

// Removes an FD node from the stack when EOF is reached
void remove_fd_node(t_fd_stack **stack, int fd) {
    t_fd_stack *temp = *stack, *prev = NULL;

    while (temp) {
        if (temp->fd == fd) {
            if (prev)
                prev->next = temp->next;
            else
                *stack = temp->next;
            free(temp->buffer);
            free(temp);
            return;
        }
        prev = temp;
        temp = temp->next;
    }
}

// Reads from FD and stores data
char *read_fd_data(int fd, char *buffer) {
    char *temp_buffer = malloc(BUFFER_SIZE + 1);
    int bytes_read;

    if (!temp_buffer)
        return NULL;
    while ((bytes_read = read(fd, temp_buffer, BUFFER_SIZE)) > 0) {
        temp_buffer[bytes_read] = '\0';
        buffer = ft_strjoin(buffer, temp_buffer);
        if (!buffer)
            break;
        if (ft_strchr(buffer, '\n'))  // Stop when newline is found
            break;
    }
    free(temp_buffer);
    return buffer;
}

// Extracts a line from the buffer
char *extract_line(char **buffer) {
    char *line;
    int i = 0;

    if (!*buffer || !**buffer)
        return NULL;

    while ((*buffer)[i] && (*buffer)[i] != '\n')
        i++;

    line = malloc(i + 2);
    if (!line)
        return NULL;

    ft_strncpy(line, *buffer, i + 1);
    line[i + 1] = '\0';

    char *new_buffer = ft_strdup(*buffer + i + 1);
    free(*buffer);
    *buffer = new_buffer;

    return line;
}

// Main function to retrieve next line
char *get_next_line(int fd) {
    static t_fd_stack *fd_stack;
    t_fd_stack *fd_node;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return NULL;

    fd_node = get_fd_node(&fd_stack, fd);
    if (!fd_node)
        return NULL;

    fd_node->buffer = read_fd_data(fd, fd_node->buffer);
    if (!fd_node->buffer)
        return NULL;

    char *line = extract_line(&fd_node->buffer);
    if (!line)
        remove_fd_node(&fd_stack, fd);
    
    return line;
}
