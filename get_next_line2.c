#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 1024  // Define buffer size

char *get_next_line(int fd) {
    static char *buffer = NULL;  // Single static variable
    static ssize_t buf_len = 0;  // Track remaining data length
    char *line, *newline_pos;
    ssize_t bytes_read;

    if (fd < 0 || BUFFER_SIZE <= 0) return NULL;  // Error check

    // Allocate the buffer if it's the first call
    if (!buffer) {
        buffer = malloc(BUFFER_SIZE + 1);
        if (!buffer) return NULL;
        buf_len = read(fd, buffer, BUFFER_SIZE);
        if (buf_len <= 0) { // Handle EOF or error
            free(buffer);
            buffer = NULL;
            return NULL;
        }
        buffer[buf_len] = '\0';
    }

    // Find the newline character
    newline_pos = strchr(buffer, '\n');
    if (newline_pos) {
        size_t line_len = newline_pos - buffer + 1; // Length including '\n'
        line = strndup(buffer, line_len); // Copy the line
        memmove(buffer, newline_pos + 1, buf_len - line_len); // Shift buffer
        buf_len -= line_len; // Reduce buffer size
        return line;
    }

    // If no newline, return everything and reset buffer
    if (buf_len > 0) {
        line = strndup(buffer, buf_len);
        free(buffer);
        buffer = NULL;
        buf_len = 0;
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
        printf("Read: %s", line);
        free(line);
    }

    close(fd);
    return 0;
}
