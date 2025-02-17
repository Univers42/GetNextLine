#ifndef GNL_H
#define GNL_h
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#ifndef BUFFER_SIZE
    #define BUFFER_SIZE 100
#endif

    #define HASH_TABLE_SIZE 1000
// Hash table to store data chunks (avoid duplicates)
typedef struct s_node {
    char *data;
    struct s_node *next;
} t_node;

typedef struct s_hash_table {
    t_node *table[HASH_TABLE_SIZE];
} t_hash_table;

unsigned int hash(const char *str);
int insert_hash(t_hash_table *ht, const char *data);
void free_hash_table(t_hash_table *ht);
char *get_next_line(int fd);
#endif