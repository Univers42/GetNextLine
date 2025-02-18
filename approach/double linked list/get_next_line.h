#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

#include <stdlib.h>
#include <unistd.h>
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 32
#endif
typedef struct s_list
{
    char            *content;
    struct s_list   *prev;
    struct s_list   *next;
}               t_list;

char    *get_next_line(int fd);
t_list  *create_node(char *content);
void    append_node(t_list **head, t_list *new_node);
void    free_list(t_list **head);
char    *extract_line(t_list **head);

#endif
