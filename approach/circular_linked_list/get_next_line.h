#ifndef GNL_H
#define GNL_H

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#ifndef BUFFER_SIZE
    #define BUFFER_SIZE 100
#endif

typedef struct s_node {
    char *data;
    struct s_node *next;
} t_node;

typedef struct s_circular_list {
    t_node *head;
    t_node *tail;
} t_circular_list;

t_node *new_node(char *data);
t_circular_list *create_circular_list();
void append_to_circular_list(t_circular_list *list, char *data);
char *dequeue_from_circular_list(t_circular_list *list);
void free_circular_list(t_circular_list *list);
char *get_next_line(int fd);

#endif
