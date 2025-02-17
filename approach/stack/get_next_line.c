#include "get_next_line.h"

// Function to read the next line using a circular stack
char *get_next_line(int fd) {
    static t_stack stack = {NULL};  // Static stack to keep track of data
    static char buffer[BUFFER_SIZE];
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
        push(&stack, new_data);  // Assuming push function uses stack as a pointer

        // Process the stack and check for a newline
        while (stack.top != NULL) {
            char *data = pop(&stack);  // Assuming pop function uses stack as a pointer
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


//int main(void) {
//    int fd = open("text.txt", O_RDONLY);
//    if (fd == -1) {
//        printf("Error opening file\n");
//        return 1;
//    }
//
//    t_stack *stack = create_stack();
//    if (!stack) {
//        close(fd);
//        return 1;
//    }
//
//    int count = 0;
//    char *next_line;
//    while ((next_line = get_next_line(fd, stack)) != NULL) {
//        count++;
//        printf("[%d]: %s\n", count, next_line);
//        free(next_line);  // Free the allocated memory for the line
//    }
//
//    free_stack(stack);  // Free the stack nodes
//    close(fd);
//    return 0;
//}
