#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "get_next_line.h"

#define BUFFER 255

typedef struct s_list
{
    void *content;
    struct s_list *next;
}t_list;

static void ft_append_chunk(t_list **head, char *chunk)
{
    t_list *new_node;
    t_list *curr;

    new_node = (t_list *)malloc(sizeof(t_list));
    if(!new_node)
        return NULL;
    new_node->content = chunk;
    new_node->next = NULL;
    if (!(*head))
        *head = new_node;
    else
    {
        curr = *head;
        while(curr->next)
            curr = curr->next;
        curr->next = new_node;
    }
}
static char *ft_lst_to_str(t_list *head)
{
    size_t len;
    t_list *curr;
    char *result;
    char *ptr;

    len = 0;
    curr = head;
    while (curr)
    {
        len += ft_strclen(curr->content, '\0');
        curr = curr->next;
    }
    result = (char *)malloc(len + 1);
    if (!result)
        return (NULL);
    ptr = result;
    while (head)
    {
        ft_memmove(ptr, head->content, ft_strclen(head->content, '\0'));
        ptr += ft_strclen(head->content, '\0');
        head = head->next;
    }
    *ptr = '\0';
    return (result);
}
static t_list *ft_store_chunks(int fd)
{
    t_list *head;
    char *chunk;
    ssize_t bytes;

    head = NULL;
    chunk = (char *)malloc(BUFFER + 1);
    if (!chunk)
        return (NULL);
    while((bytes = read(fd, chunk, BUFFER)) > 0)
    {
        *(chunk + bytes) = '\0';
        append_chunk(&head, ft_strndup(chunk, bytes));
        if(ft_strchr(chunk, '\n'))
            break;
        free(chunk);
        return (head);
    }
}
static void ft_lstdelone(t_list *head)
{
    free(head->content);
    free(head);
}
static void ft_clearlst(t_list *head, void (*fn)(void *))
{
    t_list *curr;
    t_list *temp;

    curr = head;
    while(curr != NULL)
    {
        temp = curr->next;
        ft_lstdelone(curr->content);
        curr = temp;
    }
}

static char *get_line(t_list **head)
{
    char **full_str;
    char *line;
    size_t len;

    if (!(*head))
        return (NULL);
    full_str = list_to_string(*head);
    len = ft_strclen(full_str, '\n');
    if (*(full_str + len) == '\n')
        len++;
    line = ft_strndup(full_str, len);
    free(full_str);
    return (line);
}

char *get_next_line(int fd)
{
    static t_list *memory;
    char *line;

    memory = NULL;
    if(!memory)
        memory = store_chunks(fd);
    if(!memory)
        return (NULL);
    line = get_line(&memory);
    get_leftover(&memory);
    return (line);
}
int main(void)
{
    char *file_name = "text.txt";
    char buffer[BUFFER + 1];
    ssize_t bytes;
    int fd;
    char *line;
    
    fd = open(file_name, O_RDONLY);
    if(!fd)
    {
        perror("Error opening file");
        return (1);
    }
    printf("Read %zd:", BUFFER);
    while((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        return (1);
    }
    close(fd);
    return (0);
}