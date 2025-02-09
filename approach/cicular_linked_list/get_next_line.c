#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 4

typedef struct s_node {
    char *data;
    struct s_node *next;
} t_node;

typedef struct s_circular_list {
    t_node *head;
    t_node *tail;
} t_circular_list;

// Function to create a new node with the given data
t_node *new_node(char *data) {
    t_node *node = malloc(sizeof(t_node));
    if (!node) {
        return NULL;
    }
    node->data = data;
    node->next = NULL;
    return node;
}

// Function to create and initialize the circular linked list
t_circular_list *create_circular_list() {
    t_circular_list *list = malloc(sizeof(t_circular_list));
    if (!list) {
        return NULL;
    }
    list->head = NULL;
    list->tail = NULL;
    return list;
}

// Function to append data to the circular linked list
void append_to_circular_list(t_circular_list *list, char *data) {
    t_node *node = new_node(data);
    if (!node) {
        return;
    }
    if (list->head == NULL) {
        // First node
        list->head = node;
        list->tail = node;
        node->next = node;  // Points to itself
    } else {
        // Append to the end and make it circular
        list->tail->next = node;
        list->tail = node;
        node->next = list->head;  // Points back to the head
    }
}

// Function to dequeue and get a node's data from the circular list
char *dequeue_from_circular_list(t_circular_list *list) {
    if (list->head == NULL) {
        return NULL;
    }

    t_node *first_node = list->head;
    char *data = first_node->data;

    if (list->head == list->tail) {
        // Only one node in the list
        list->head = NULL;
        list->tail = NULL;
    } else {
        list->head = first_node->next;
        list->tail->next = list->head;  // Maintain the circular structure
    }
    
    free(first_node);
    return data;
}

// Function to free the circular linked list
void free_circular_list(t_circular_list *list) {
    while (list->head != NULL) {
        char *data = dequeue_from_circular_list(list);
        free(data);  // Free the node data
    }
    free(list);  // Free the list structure
}

// Function to get the next line with the circular linked list
char *get_next_line(int fd, t_circular_list *list) {
    static char buffer[BUFFER_SIZE];
    int bytes_read;
    char *line = malloc(1);
    int line_len = 0;

    if (!line) return NULL;
    line[0] = '\0';

    while ((bytes_read = read(fd, buffer, BUFFER_SIZE - 1)) > 0) {
        buffer[bytes_read] = '\0';  // Null-terminate buffer

        // Append this chunk of data to the circular list
        char *chunk = strdup(buffer);  // Copy the buffer into heap memory
        if (!chunk) {
            free(line);
            return NULL;  // Memory allocation failed
        }
        append_to_circular_list(list, chunk);

        // Process the circular list for a complete line
        while (list->head != NULL) {
            char *data = dequeue_from_circular_list(list);

            for (int i = 0; data[i] != '\0'; i++) {
                line_len++;
                line = realloc(line, line_len + 1);  // Reallocate space for next char
                if (!line) return NULL;

                line[line_len - 1] = data[i];
                line[line_len] = '\0';  // Null-terminate the string

                if (data[i] == '\n') {
                    free(data);  // Free the node data
                    return line;  // Return the line when newline is encountered
                }
            }
            free(data);  // Free the data after processing
        }
    }

    // If no more data and some data has been read, return the line so far
    if (bytes_read == 0 && line_len > 0) {
        return line;
    }

    free(line);  // Free memory if no line was found
    return NULL;
}

int main(void) {
    int fd = open("text.txt", O_RDONLY);
    if (fd == -1) {
        printf("Error opening file\n");
        return 1;
    }

    t_circular_list *list = create_circular_list();
    if (!list) {
        close(fd);
        return 1;
    }

    int count = 0;
    char *next_line;
    while ((next_line = get_next_line(fd, list)) != NULL) {
        count++;
        printf("[%d]: %s\n", count, next_line);
        free(next_line);  // Free the allocated memory for the line
    }

    free_circular_list(list);  // Free the circular linked list
    close(fd);
    return 0;
}
