#include "get_next_line.h"
#include <string.h>

char *get_next_line(int fd)
{
    static t_list *head;
    char buffer[BUFFER_SIZE + 1];
    int bytes_read;
    char *line;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0)
    {
        buffer[bytes_read] = '\0';
        append_node(&head, create_node(buffer));
        if (strchr(buffer, '\n'))
            break ;
    }
    if (bytes_read < 0 || (bytes_read == 0 && !head))
        return (NULL);
    line = extract_line(&head);
    if (line && line[0] == '\0')
    {
        free(line);
        return (NULL);
    }
    return (line);
}

char *extract_line(t_list **head)
{
    if (!head || !*head)
        return (NULL);

    t_list *temp;
    char *line;
    size_t len = 0;
    size_t total_len = 0;

    temp = *head;
    while (temp)
    {
        while (temp->content[len] != '\n' && temp->content[len] != '\0')
            len++;
        total_len += len;
        if (temp->content[len] == '\n')
        {
            total_len++;
            break;
        }
        temp = temp->next;
        len = 0;
    }
    line = (char *)malloc(total_len + 1);
    if (!line)
        return (NULL);
    temp = *head;
    total_len = 0;
    while (temp)
    {
        len = 0;
        while (temp->content[len] != '\n' && temp->content[len] != '\0')
            len++;
        strncpy(line + total_len, temp->content, len);
        total_len += len;
        if (temp->content[len] == '\n')
        {
            line[total_len] = '\n';
            total_len++;
            break;
        }
        temp = temp->next;
    }
    line[total_len] = '\0';
    t_list *to_free = *head;
    *head = temp ? temp->next : NULL;
    if (*head)
        (*head)->prev = NULL;
    while (to_free && to_free != temp)
    {
        t_list *next = to_free->next;
        free(to_free->content);
        free(to_free);
        to_free = next;
    }
    if (temp)
    {
        free(temp->content);
        free(temp);
    }
    return (line);
}
