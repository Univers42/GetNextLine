#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define BUFFER_SIZE 4  // Set the buffer size (3 bytes + 1 for null terminator)

// Doubly Linked List Node
typedef struct s_node {
    char *data;          // The data for the node (a chunk of text)
    struct s_node *prev; // Pointer to the previous node
    struct s_node *next; // Pointer to the next node
} t_node;

// Doubly Linked List Structure
typedef struct s_list {
    t_node *head;  // The first node in the list
    t_node *tail;  // The last node in the list
    size_t size;   // Number of nodes in the list
} t_list;

// Function to create a new node
t_node *new_node(char *data) {
    t_node *node = malloc(sizeof(t_node));
    if (!node) return NULL;
    node->data = data;
    node->prev = NULL;
    node->next = NULL;
    return node;
}

// Function to create a new doubly linked list
t_list *create_list() {
    t_list *list = malloc(sizeof(t_list));
    if (!list) return NULL;
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

// Function to append a node to the doubly linked list
void append(t_list *list, char *data) {
    t_node *node = new_node(data);
    if (!node) return;
    if (list->tail) {
        list->tail->next = node;
        node->prev = list->tail;
        list->tail = node;
    } else {
        list->head = node;
        list->tail = node;
    }
    list->size++;
}

// Function to remove and free the first node from the list
char *remove_head(t_list *list) {
    if (list->head == NULL) return NULL;
    t_node *node = list->head;
    char *data = node->data;
    list->head = node->next;
    if (list->head) {
        list->head->prev = NULL;
    } else {
        list->tail = NULL;
    }
    free(node);
    list->size--;
    return data;
}

// Function to free the entire list
void free_list(t_list *list) {
    while (list->head != NULL) {
        char *data = remove_head(list);
        free(data);
    }
    free(list);
}

// Function to read the next line using a doubly linked list
char *get_next_line(int fd, t_list *list) {
    static char buffer[BUFFER_SIZE];  // Buffer to hold data from the file
    int bytes_read;
    char *line = malloc(1);  // Initial allocation for the line
    int line_len = 0;
    if (!line) return NULL;
    line[0] = '\0';  // Initialize as an empty string

    // Read data from the file and append it to the doubly linked list
    while ((bytes_read = read(fd, buffer, BUFFER_SIZE - 1)) > 0) {
        buffer[bytes_read] = '\0';  // Null-terminate the buffer
        char *new_data = malloc(bytes_read + 1);
        if (!new_data) {
            free(line);
            return NULL;
        }
        for (int i = 0; i < bytes_read; i++) {
            new_data[i] = buffer[i];
        }
        new_data[bytes_read] = '\0';  // Null-terminate the new chunk
        append(list, new_data);

        // Process the list to form the line
        while (list->head != NULL) {
            char *data = remove_head(list);  // Get the next chunk
            for (int i = 0; data[i] != '\0'; i++) {
                line_len++;
                line = realloc(line, line_len + 1);  // Reallocate for the new character
                if (!line) {
                    free(data);
                    return NULL;
                }
                line[line_len - 1] = data[i];
                line[line_len] = '\0';  // Null-terminate the string

                if (data[i] == '\n') {  // If we found a newline, return the line
                    free(data);
                    return line;
                }
            }
            free(data);  // Free the chunk after processing it
        }
    }

    // If we reach the end of the file, return the current line
    if (bytes_read == 0 && line_len > 0) {
        return line;
    }

    free(line);  // Free the line if no data was collected
    return NULL;
}

int main(void) {
    int fd = open("text.txt", O_RDONLY);
    if (fd == -1) {
        printf("Error opening file\n");
        return 1;
    }

    t_list *list = create_list();
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

    free_list(list);  // Free the list nodes
    close(fd);
    return 0;
}
