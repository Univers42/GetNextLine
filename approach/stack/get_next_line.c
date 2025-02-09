#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define BUFFER_SIZE 4  // Set the buffer size (3 bytes + 1 for null terminator)

// Circular Stack Node
typedef struct s_node {
    char *data;
    struct s_node *next;
} t_node;

// Circular Stack Structure
typedef struct s_stack {
    t_node *top;
    size_t size;
} t_stack;

// Function to create a new stack
t_stack *create_stack() {
    t_stack *stack = malloc(sizeof(t_stack));
    if (!stack) return NULL;
    stack->top = NULL;
    stack->size = 0;
    return stack;
}

// Function to push data onto the stack
void push(t_stack *stack, char *data) {
    t_node *node = malloc(sizeof(t_node));
    if (!node) return;
    node->data = data;
    node->next = stack->top;
    stack->top = node;
    stack->size++;
}

// Function to pop data from the stack
char *pop(t_stack *stack) {
    if (stack->top == NULL) return NULL;
    t_node *node = stack->top;
    char *data = node->data;
    stack->top = node->next;
    free(node);
    stack->size--;
    return data;
}

// Function to free the stack
void free_stack(t_stack *stack) {
    while (stack->top != NULL) {
        char *data = pop(stack);
        free(data);
    }
    free(stack);
}

// Function to read the next line using a circular stack
char *get_next_line(int fd, t_stack *stack) {
    static char buffer[BUFFER_SIZE];  // Buffer to hold data
    int bytes_read;
    char *line = malloc(1);  // Allocate initial space for line
    int line_len = 0;
    if (!line) return NULL;
    line[0] = '\0';  // Initialize as empty string

    while ((bytes_read = read(fd, buffer, BUFFER_SIZE - 1)) > 0) {
        buffer[bytes_read] = '\0';  // Null-terminate the buffer

        // Push the read data into the stack
        char *new_data = malloc(bytes_read + 1);
        if (!new_data) {
            free(line);
            return NULL;
        }
        for (int i = 0; i < bytes_read; i++) {
            new_data[i] = buffer[i];
        }
        new_data[bytes_read] = '\0';
        push(stack, new_data);

        // Process the stack and check for a newline
        while (stack->top != NULL) {
            char *data = pop(stack);
            for (int i = 0; data[i] != '\0'; i++) {
                line_len++;
                line = realloc(line, line_len + 1);
                if (!line) {
                    free(data);
                    return NULL;
                }
                line[line_len - 1] = data[i];
                line[line_len] = '\0';

                if (data[i] == '\n') {
                    free(data);
                    return line;  // Return the line when newline is encountered
                }
            }
            free(data);  // Free data after processing it
        }
    }

    // If we reach the end of file (EOF) and no line was found, return NULL
    if (bytes_read == 0 && line_len == 0) {
        free(line);
        return NULL;
    }

    return line;
}

int main(void) {
    int fd = open("text.txt", O_RDONLY);
    if (fd == -1) {
        printf("Error opening file\n");
        return 1;
    }

    t_stack *stack = create_stack();
    if (!stack) {
        close(fd);
        return 1;
    }

    int count = 0;
    char *next_line;
    while ((next_line = get_next_line(fd, stack)) != NULL) {
        count++;
        printf("[%d]: %s\n", count, next_line);
        free(next_line);  // Free the allocated memory for the line
    }

    free_stack(stack);  // Free the stack nodes
    close(fd);
    return 0;
}
