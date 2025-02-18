#ifndef GNL_H
#define GNL_H

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_node
{
    char            *data;
    struct s_node   *next;
}   t_node;

typedef struct s_queue
{
    t_node  *head;
    t_node  *tail;
}   t_queue;

t_node *new_node(char *data);
void enqueue(t_queue *queue, char *data);
char *dequeue(t_queue *queue);
void clear_queue(t_queue *queue);
char *get_next_line(int fd);
char *extract_line_from_queue(t_queue *queue);

#endif