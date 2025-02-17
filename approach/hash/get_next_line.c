#include "get_next_line.h"
// Function to get the next line with hashing (avoiding duplicates)
char *get_next_line(int fd)
{
    static t_hash_table ht;  // Static hash table to persist across function calls
    static char buffer[BUFFER_SIZE];
    int bytes_read;
    char *line = malloc(1);
    int line_len = 0;

    if (!line) return NULL;
    line[0] = '\0';

    while ((bytes_read = read(fd, buffer, BUFFER_SIZE - 1)) > 0) {
        buffer[bytes_read] = '\0';  // Null-terminate buffer

        // Check if this chunk has already been processed (hash deduplication)
        if (insert_hash(&ht, buffer) == 0) {
            continue;  // Skip this chunk if it's a duplicate
        }

        // Append the chunk to the line
        for (int i = 0; i < bytes_read; i++) {
            line_len++;
            line = realloc(line, line_len + 1);
            if (!line) return NULL;
            line[line_len - 1] = buffer[i];
            line[line_len] = '\0';

            if (buffer[i] == '\n') {
                return line;  // Return the line when newline is encountered
            }
        }
    }

    if (bytes_read == 0 && line_len > 0) {
        return line;  // Return the line if no more data and some data exists
    }

    free(line);
    return NULL;  // Return NULL if no line found
}


//int main(void) {
//    int fd = open("text.txt", O_RDONLY);
//    if (fd == -1) {
//        printf("Error opening file\n");
//        return 1;
//    }
//
//    t_hash_table *ht = malloc(sizeof(t_hash_table));
//    if (!ht) {
//        close(fd);
//        return 1;
//    }
//    memset(ht->table, 0, sizeof(ht->table));
//
//    int count = 0;
//    char *next_line;
//    while ((next_line = get_next_line(fd, ht)) != NULL) {
//        count++;
//        printf("[%d]: %s\n", count, next_line);
//        free(next_line);
//    }
//
//    free_hash_table(ht);  // Free hash table
//    close(fd);
//    return 0;
//}
