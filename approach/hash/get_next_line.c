#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 4
#define HASH_TABLE_SIZE 1000

// A simple djb2 hash function
unsigned int hash(const char *str) {
    unsigned int hash = 5381;
    int c;

    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;  // hash * 33 + c
    }
    return hash % HASH_TABLE_SIZE;
}

// Hash table to store data chunks (avoid duplicates)
typedef struct s_node {
    char *data;
    struct s_node *next;
} t_node;

typedef struct s_hash_table {
    t_node *table[HASH_TABLE_SIZE];
} t_hash_table;

// Insert data into hash table if not already present
int insert_hash(t_hash_table *ht, const char *data) {
    unsigned int index = hash(data);
    t_node *current = ht->table[index];
    while (current) {
        if (strcmp(current->data, data) == 0) {
            return 0;  // Data is already in the hash table
        }
        current = current->next;
    }

    // Add new node
    t_node *new_node = malloc(sizeof(t_node));
    if (!new_node) return -1;  // Memory allocation failed
    new_node->data = strdup(data);
    new_node->next = ht->table[index];
    ht->table[index] = new_node;
    return 1;  // Successfully inserted
}

// Function to free the hash table
void free_hash_table(t_hash_table *ht) {
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        t_node *current = ht->table[i];
        while (current) {
            t_node *temp = current;
            current = current->next;
            free(temp->data);
            free(temp);
        }
    }
    free(ht);
}

// Function to get the next line with hashing (avoiding duplicates)
char *get_next_line(int fd, t_hash_table *ht) {
    static char buffer[BUFFER_SIZE];
    int bytes_read;
    char *line = malloc(1);
    int line_len = 0;

    if (!line) return NULL;
    line[0] = '\0';

    while ((bytes_read = read(fd, buffer, BUFFER_SIZE - 1)) > 0) {
        buffer[bytes_read] = '\0';  // Null-terminate buffer

        // Check if this chunk has already been processed (hash deduplication)
        if (insert_hash(ht, buffer) == 0) {
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

int main(void) {
    int fd = open("text.txt", O_RDONLY);
    if (fd == -1) {
        printf("Error opening file\n");
        return 1;
    }

    t_hash_table *ht = malloc(sizeof(t_hash_table));
    if (!ht) {
        close(fd);
        return 1;
    }
    memset(ht->table, 0, sizeof(ht->table));

    int count = 0;
    char *next_line;
    while ((next_line = get_next_line(fd, ht)) != NULL) {
        count++;
        printf("[%d]: %s\n", count, next_line);
        free(next_line);
    }

    free_hash_table(ht);  // Free hash table
    close(fd);
    return 0;
}
