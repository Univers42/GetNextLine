#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 1024  // Define the buffer size

char *get_next_line(int fd) {
    static char *buffer = NULL;  // Single static variable
    char *line;
    char *newline_pos;
    ssize_t bytes_read;

    // Allocate the buffer if it's the first call
    if (!buffer) {
        buffer = malloc(BUFFER_SIZE + 1);
        if (!buffer) return NULL;
        bytes_read = read(fd, buffer, BUFFER_SIZE);
        if (bytes_read <= 0) {
            free(buffer);
            buffer = NULL;
            return NULL;
        }
        buffer[bytes_read] = '\0';
    }

    // Find newline in the buffer
    newline_pos = strchr(buffer, '\n');
    if (newline_pos) {
        *newline_pos = '\0';  // Replace '\n' with null terminator
        line = strdup(buffer); // Copy line to return
        buffer = newline_pos + 1; // Move buffer start past newline
        return line;
    }

    // If no newline, return everything and reset buffer
    if (*buffer) {
        line = strdup(buffer);
        free(buffer);
        buffer = NULL;
        return line;
    }
    return NULL; // EOF
}

int main() {
    int fd = open("test.txt", O_RDONLY);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    char *line;
    while ((line = get_next_line(fd))) {
        printf("Read: %s\n", line);
        free(line);
    }

    close(fd);
    return 0;
}
