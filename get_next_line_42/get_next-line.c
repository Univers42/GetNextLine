#include  "get_next_line.h"


t_list *lstaddback(t_list **head)
{
    t_list *new_node;
    
    new_node = malloc(sizeof());
    if(!head)
        new_node = head;
    else
    {
        
    }
}
void clear_lst(t_list **head)
{
    t_list *curr;
    t_list *temp;

    curr = *head;
    while(curr)
    {
        temp = curr->next;
        free(curr->content);
        free(curr);
        curr = temp;
    }
    return (0);
}
char *get_next_line(int fd)
{
    char memoria[BUFFER_SIZE];
    char *line;
    
    if(!memoria)
        store_memory_chunks(fd);
    if(!memoria)
        return NULL;
    line = get_line(fd);
    return (1);
}