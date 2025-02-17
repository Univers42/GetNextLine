#include "get_next_line.h"
// Function to create a new queue node


// Function to get the next line
char *get_next_line(int fd) {
    static t_queue queue = {NULL};  // Static queue to persist across calls
    static char buffer[4];  // buffer to hold read data (3 bytes + 1 for null terminator)
    int bytes_read;
    char *line = NULL;
    int line_len = 0;
    char *new_data;

    // Initialize line as an empty string
    line = malloc(1);  // Allocate space for the initial null terminator
    if (line == NULL) {
        return NULL;  // Return NULL if malloc fails
    }
    line[0] = '\0';  // Initialize the string as empty

    // Read file in chunks and enqueue the data
    while ((bytes_read = read(fd, buffer, 3)) > 0) {
        buffer[bytes_read] = '\0';  // Null-terminate the read data
        new_data = malloc(bytes_read + 1);
        if (new_data == NULL) {
            free(line);
            return NULL;  // Return NULL if malloc fails
        }
        for (int i = 0; i < bytes_read; i++) {
            new_data[i] = buffer[i];
        }
        new_data[bytes_read] = '\0';  // Ensure null termination of new_data
        enqueue(&queue, new_data);  // Assuming enqueue works with queue pointer
    }
    
    // If no data was read and the queue is empty, we are at the end of file
    if (bytes_read == 0 && queue.front == NULL) {
        free(line);
        return NULL;  // No more data, EOF
    }

    // Dequeue data to form a line
    while (queue.front != NULL) {
        char *data = dequeue(&queue);  // Assuming dequeue works with queue pointer
        int i = 0;
        while (data[i] != '\0') {
            line_len++; // Increment line length
            line = realloc(line, line_len + 1); // Reallocate space for the next character
            if (line == NULL) {
                free(data);
                return NULL;  // Return NULL if realloc fails
            }
            line[line_len - 1] = data[i];
            line[line_len] = '\0'; // Null-terminate the string

            // If we encounter a newline, return the line
            if (data[i] == '\n') {
                free(data);  // Free the node data here
                return line;
            }
            i++;
        }
        free(data);  // Free the data after processing it
    }

    // If no line was found (end of file), return the line we have so far
    return line;
}


//int main(void) {
//    int fd = open("text.txt", O_RDONLY);
//    if (fd == -1) {
//        printf("Error opening file\n");
//        return 1;
//    }
//
//    t_queue *queue = create_queue();
//    if (queue == NULL) {
//        close(fd);
//        return 1;
//    }
//
//    int count = 0;
//    char *next_line;
//    while ((next_line = get_next_line(fd, queu)) != NULL) {
//        count++;
//        printf("[%d]: %s\n", count, next_line);
//        free(next_line);  // Free the allocated memory for the line
//    }
//
//    free_queue(queue);  // Free the queue nodes
//    close(fd);
//    return 0;
//}
