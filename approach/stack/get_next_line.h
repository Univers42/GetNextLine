#ifndef GNL_H
#define GNL_h
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#ifndef BUFFER_SIZE
    #define BUFFER_SIZE 100
#endif


// Circular Stack Node
typedef struct s_node {
    char *data;
    struct s_node *next;
} t_node;

// Circular Stack Structure
typedef struct s_stack {
    t_node *top;
    size_t size;
} t_stack;

char *pop(t_stack *stack);
void push(t_stack *stack, char *data);
t_stack *create_stack();
void free_stack(t_stack *stack);
char *get_next_line(int fd);
#endif