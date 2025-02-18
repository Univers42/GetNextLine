#include "get_next_line.h"

char *get_next_line(int fd) {
    static t_hash_table ht;
    static char buffer[BUFFER_SIZE];
    int bytes_read;
    char *line = malloc(1);
    int line_len = 0;

    if (!line) return NULL;
    line[0] = '\0';

    while ((bytes_read = read(fd, buffer, BUFFER_SIZE - 1)) > 0) {
        buffer[bytes_read] = '\0';

                if (insert_hash(&ht, buffer) == 0) {
            continue;
        }

                for (int i = 0; i < bytes_read; i++) {
            line_len++;
            line = realloc(line, line_len + 1);
            if (!line) return NULL;
            line[line_len - 1] = buffer[i];
            line[line_len] = '\0';

            if (buffer[i] == '\n') {
                return line;
            }
        }
    }

    if (bytes_read == 0 && line_len > 0) {
        return line;
    }

    free(line);
    return NULL;
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
