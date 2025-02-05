#ifndef GNL_H
#define GNL_H

typedef struct s_list
{
    char            *new_line;
    struct s_list   *next;
}                   t_list;


static t_list *find_last_node(t_list *list);
static void free_list(t_list **list);
static int found_newline(t_list *list);
static int len_to_newline(t_list *list);
static void copy_str(t_list *list, char *dest);
#endif