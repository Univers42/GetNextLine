#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define BUFFER_SIZE 250

typedef struct s_list
{
    char            *new_line;
    struct s_list   *next;
}                   t_list;

static t_list *find_last_node(t_list *list)
{
    while (list && list->next)
        list = list->next;
    return list;
}

static void free_list(t_list **list)
{
    t_list *temp;
    
    while (*list)
    {
        temp = (*list)->next;
        free((*list)->new_line);
        free(*list);
        *list = temp;
    }
}

static int found_newline(t_list *list)
{
    while (list)
    {
        if (list->new_line && strchr(list->new_line, '\n'))
            return 1;
        list = list->next;
    }
    return 0;
}

static void append(t_list **list, char *buf)
{
    t_list *new_node = malloc(sizeof(t_list));
    t_list *last_node;
    if (!new_node)
        return;
    new_node->new_line = buf;
    new_node->next = NULL;
    if (!*list)
        *list = new_node;
    else
    {
        last_node = find_last_node(*list);
        last_node->next = new_node;
    }
}

static void create_list(t_list **list, int fd)
{
    char *buf;
    ssize_t bytes_read;
    
    while (!found_newline(*list))
    {
        buf = malloc(BUFFER_SIZE + 1);
        if (!buf)
            return;
        bytes_read = read(fd, buf, BUFFER_SIZE);
        if (bytes_read <= 0)
        {
            free(buf);
            return;
        }
        buf[bytes_read] = '\0';
        append(list, buf);
    }
}

static int len_to_newline(t_list *list)
{
    int len = 0;
    while (list)
    {
        for (int i = 0; list->new_line[i]; i++)
        {
            if (list->new_line[i] == '\n')
                return len + 1;
            len++;
        }
        list = list->next;
    }
    return len;
}

static void copy_str(t_list *list, char *dest)
{
    int i = 0;
    while (list)
    {
        for (int j = 0; list->new_line[j]; j++)
        {
            dest[i++] = list->new_line[j];
            if (list->new_line[j] == '\n')
            {
                dest[i] = '\0';
                return;
            }
        }
        list = list->next;
    }
    dest[i] = '\0';
}

static void polish_list(t_list **list)
{
    t_list *last = find_last_node(*list);
    if (!last)
    {
        free_list(list);
        return;
    }
    char *new_buf = strdup(strchr(last->new_line, '\n') + 1);
    if (!new_buf)
    {
        free_list(list);
        return;
    }
    free_list(list);
    append(list, new_buf);
}

char *get_next_line(int fd)
{
    static t_list *list = NULL;
    char *next_line;
    
    if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
        return NULL;
    create_list(&list, fd);
    if (!list)
        return NULL;
    next_line = malloc(len_to_newline(list) + 1);
    if (!next_line)
        return NULL;
    copy_str(list, next_line);
    polish_list(&list);
    return next_line;
}

int main(int  argc, char *argv)
{
    if(argc != 2)
        return  1;
    int fd;
    char buffer[BUFFER_SIZE];
    int nbytes;
    fd = open(argv[1], O_RDONLY);
    while(nbytes = read(fd, buffer ,BUFFER_SIZE))
    {
        
    }
}