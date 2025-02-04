#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
/**
 * 
 */
typedef struct s_file_map {
    char *buffer;     // File content in memory
    size_t size;      // Total file size
    size_t offset;    // Current reading position
} t_file_map;

// Reads the entire file into memory
t_file_map *custom_mmap(int fd) {
    if (fd < 0) return NULL;

    size_t capacity = 4096; // Initial buffer size
    size_t size = 0;
    char *buffer = malloc(capacity);
    if (!buffer) return NULL;

    ssize_t bytes_read;
    while ((bytes_read = read(fd, buffer + size, 1024)) > 0) {
        size += bytes_read;
        if (size + 1024 > capacity) {  // Expand buffer if needed
            capacity *= 2;
            char *new_buffer = realloc(buffer, capacity);
            if (!new_buffer) {
                free(buffer);
                return NULL;
            }
            buffer = new_buffer;
        }
    }
    if (bytes_read == -1) { free(buffer); return NULL; } // Read error

    t_file_map *file_map = malloc(sizeof(t_file_map));
    if (!file_map) {
        free(buffer);
        return NULL;
    }

    file_map->buffer = buffer;
    file_map->size = size;
    file_map->offset = 0;

    return file_map;
}

// Frees allocated memory
void custom_munmap(t_file_map *file_map) {
    if (file_map) {
        free(file_map->buffer);
        free(file_map);
    }
}

// Fetches the next line from the file
char *get_next_line(int fd) {
    static t_file_map *file_map = NULL;

    if (fd < 0) return NULL;

    // Load file into memory on first call
    if (!file_map) {
        file_map = custom_mmap(fd);
        if (!file_map) return NULL;
    }

    // Check if EOF is reached
    if (file_map->offset >= file_map->size) {
        custom_munmap(file_map);
        file_map = NULL;
        return NULL;
    }

    // Locate next newline
    size_t start = file_map->offset;
    while (file_map->offset < file_map->size && file_map->buffer[file_map->offset] != '\n') {
        file_map->offset++;
    }

    // Determine length and allocate memory for the line
    size_t len = file_map->offset - start;
    if (file_map->offset < file_map->size) file_map->offset++;  // Skip '\n'

    char *line = malloc(len + 2); // +1 for '\n', +1 for '\0'
    if (!line) return NULL;

    memcpy(line, file_map->buffer + start, len);
    line[len] = '\n';
    line[len + 1] = '\0';

    return line;
}

// Main function to demonstrate get_next_line
int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        return 1;
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    char *line;
    while ((line = get_next_line(fd))) {
        printf("%s", line);
        free(line);
    }

    close(fd);
    return 0;
}
