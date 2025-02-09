#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define BUFFER_SIZE 4  // Size of each read chunk (3 bytes + 1 for '\0')

// Function to read the next line from a file descriptor
char *get_next_line(int fd) {
    static char buffer[BUFFER_SIZE];  // Buffer to hold file data
    static int start = 0, end = 0;    // "Start" and "end" pointers (indices)
    int line_len = 0;
    char *line = NULL;

    while (1) {
        // If we've read all data in the buffer, refill it
        if (start == end) {
            end = read(fd, buffer, BUFFER_SIZE - 1);
            start = 0;

            // If we reached the end of the file or an error, return what we have
            if (end <= 0) {
                if (line_len > 0) {
                    if (line == NULL) {
                        line = malloc(line_len + 1);
                        if (line == NULL) return NULL;
                    }
                    line[line_len] = '\0';
                }
                return line;
            }

            // Ensure buffer is null-terminated
            buffer[end] = '\0';
        }

        // Process the current character from the buffer
        char current_char = buffer[start++];
        
        // If a newline is encountered, finalize the line
        if (current_char == '\n') {
            if (line == NULL) {
                line = malloc(line_len + 1);
                if (line == NULL) return NULL;
            }
            line[line_len] = '\0';
            return line;
        }

        // If we are accumulating a line, append to it
        if (line == NULL) {
            line = malloc(2);  // Allocate space for the first character + '\0'
            if (line == NULL) return NULL;
            line[0] = current_char;
            line_len = 1;
        } else {
            line_len++;
            line = realloc(line, line_len + 1);  // Add space for the new character
            if (line == NULL) return NULL;
            line[line_len - 1] = current_char;
        }
    }
}

int main(void) {
    int fd = open("text.txt", O_RDONLY);
    if (fd == -1) {
        printf("Error opening file\n");
        return 1;
    }

    char *next_line;
    int count = 0;
    while ((next_line = get_next_line(fd)) != NULL) {
        count++;
        printf("[%d]: %s\n", count, next_line);
        free(next_line);  // Free the allocated memory for the line
    }

    close(fd);
    return 0;
}
