#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

typedef struct s_file_map {
    char *buffer;     // Entire file stored in memory
    size_t size;      // Total file size
    size_t offset;    // Current position in buffer
} t_file_map;

// Custom "mmap" function: Reads the entire file into memory
t_file_map *custom_mmap(int fd) {
    size_t capacity = 4096; // Start with a small buffer
    size_t size = 0;
    char *buffer = malloc(capacity);
    if (!buffer) return NULL;

    ssize_t bytes_read;
    while ((bytes_read = read(fd, buffer + size, 1024)) > 0) {
        size += bytes_read;
        if (size + 1024 > capacity) { // Expand buffer if needed
            capacity *= 2;
            buffer = realloc(buffer, capacity);
            if (!buffer) return NULL;
        }
    }
    if (bytes_read == -1) { free(buffer); return NULL; } // Read error

    t_file_map *file_map = malloc(sizeof(t_file_map));
    if (!file_map) { free(buffer); return NULL; }
    
    file_map->buffer = buffer;
    file_map->size = size;
    file_map->offset = 0;

    return file_map;
}

// Free function for our simulated mmap
void custom_munmap(t_file_map *file_map) {
    if (file_map) {
        free(file_map->buffer);
        free(file_map);
    }
}

// Efficiently fetches the next line from the "mapped" file
char *get_next_line(int fd) {
    static t_file_map *file_map = NULL;
    
    if (fd < 0) return NULL;

    // Simulate mmap on first call
    if (!file_map) {
        file_map = custom_mmap(fd);
        if (!file_map) return NULL;
    }

    if (file_map->offset >= file_map->size) {
        custom_munmap(file_map);
        file_map = NULL;
        return NULL;  // End of file
    }

    // Find the next newline character
    size_t start = file_map->offset;
    while (file_map->offset < file_map->size && file_map->buffer[file_map->offset] != '\n') {
        file_map->offset++;
    }

    // Allocate and copy line
    size_t len = file_map->offset - start + 1;
    char *line = malloc(len + 1);
    if (!line) return NULL;

    strncpy(line, file_map->buffer + start, len);
    line[len] = '\0'; // Null-terminate

    file_map->offset++; // Move past '\n'
    return line;
}
