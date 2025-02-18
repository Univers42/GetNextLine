#include "get_next_line.h"

unsigned int hash(const char *str) {
    unsigned int hash = 5381;
    int c;

    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;  // hash * 33 + c
    }
    return hash % HASH_TABLE_SIZE;
}

// Insert data into hash table if not already present
int insert_hash(t_hash_table *ht, const char *data) {
    if (!data) return -1;  // Check if data is NULL
    if (!ht) return -1;  // Check if hash table is NULL

    unsigned int index = hash(data);
    t_node *current = ht->table[index];
    while (current) {
        if (current->data && strcmp(current->data, data) == 0) {
            return 0;  // Data is already in the hash table
        }
        current = current->next;
    }

    // Add new node
    t_node *new_node = malloc(sizeof(t_node));
    if (!new_node) return -1;  // Memory allocation failed
    new_node->data = strdup(data);
    if (!new_node->data) {
        free(new_node);
        return -1;
    }
    new_node->next = ht->table[index];
    ht->table[index] = new_node;
    return 1;  // Successfully inserted
}

// Function to free the hash table
void free_hash_table(t_hash_table *ht) {
    if (!ht) return;  // Check if hash table is NULL

    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        t_node *current = ht->table[i];
        while (current) {
            t_node *temp = current;
            current = current->next;
            free(temp->data);
            free(temp);
        }
    }
}