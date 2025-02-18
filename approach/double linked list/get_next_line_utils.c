#include "get_next_line.h"
#include <string.h>

// ...existing code...

t_list *create_node(char *content)
{
    t_list *new_node;

    new_node = (t_list *)malloc(sizeof(t_list));
    if (!new_node)
        return (NULL);
    new_node->content = strdup(content);
    new_node->prev = NULL;
    new_node->next = NULL;
    return (new_node);
}

void append_node(t_list **head, t_list *new_node)
{
    t_list *temp;

    if (!head || !new_node)
        return ;
    if (!*head)
    {
        *head = new_node;
        return ;
    }
    temp = *head;
    while (temp->next)
        temp = temp->next;
    temp->next = new_node;
    new_node->prev = temp;
}

void free_list(t_list **head)
{
    t_list *temp;

    while (*head)
    {
        temp = (*head)->next;
        free((*head)->content);
        free(*head);
        *head = temp;
    }
}

// ...existing code...
