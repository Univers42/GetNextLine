#ifndef GNL_H
#define GNL_H

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct s_node {
    char *data;
    struct s_node *next;
} t_node;

typedef struct s_queue {
    t_node *front;
    t_node *rear;
} t_queue;

t_node *new_node(char *data);
t_queue *create_queue();
void enqueue(t_queue *queue, char *data);
char *dequeue(t_queue *queue) ;
void free_queue(t_queue *queue);
char *get_next_line(int fd);

#endif