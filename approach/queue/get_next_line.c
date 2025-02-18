#include "get_next_line.h"
#include <stdio.h> // Include for debug statements

size_t  ft_strlen(const char *s)
{
    size_t len = 0;
    while (s[len])
        len++;
    return len;
}

char    *ft_strchr(const char *s, int c)
{
    while (*s)
    {
        if (*s == (char)c)
            return (char *)s;
        s++;
    }
    if (*s == (char)c)
        return (char *)s;
    return NULL;
}

char    *ft_strjoin(char *s1, char *s2)
{
    if (!s1 && !s2)
        return (NULL);
    if (!s1)
        return strdup(s2); // Ensure valid return when s1 is NULL
    if (!s2)
        return strdup(s1); // Ensure valid return when s2 is NULL

    size_t  len1 = ft_strlen(s1);
    size_t  len2 = ft_strlen(s2);
    char    *new_str = malloc(len1 + len2 + 1);
    if (!new_str)
        return (NULL);

    memcpy(new_str, s1, len1);
    memcpy(new_str + len1, s2, len2);
    new_str[len1 + len2] = '\0';
    return (new_str);
}

char    *get_next_line(int fd)
{
    static t_queue queue = {NULL, NULL};
    char        *buffer;
    ssize_t     bytes_read;
    char        *line;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);

    buffer = malloc(BUFFER_SIZE + 1);
    if (!buffer)
        return (NULL);

    bytes_read = 1;
    while (!queue.tail || !ft_strchr(queue.tail->data, '\n'))
    {
        bytes_read = read(fd, buffer, BUFFER_SIZE);
        if (bytes_read <= 0)
        {
            free(buffer);
            if (!queue.head)
                return (NULL);
            return extract_line_from_queue(&queue);
        }
        buffer[bytes_read] = '\0';

        char *joined = ft_strjoin(queue.tail ? queue.tail->data : NULL, buffer);
        if (!joined) // Prevent enqueuing NULL
        {
            free(buffer);
            return (NULL);
        }
        if (queue.tail)
        {
            free(queue.tail->data);
            queue.tail->data = joined;
        }
        else
        {
            enqueue(&queue, joined);
        }
    }
    free(buffer);
    line = extract_line_from_queue(&queue);
    return (line);
}

void    enqueue(t_queue *queue, char *data)
{
    if (!data)
        return;
    t_node *new_node = malloc(sizeof(t_node));
    if (!new_node)
        return;
    new_node->data = data;
    new_node->next = NULL;
    if (!queue->head)
        queue->head = new_node;
    else
        queue->tail->next = new_node;
    queue->tail = new_node;
}

char    *dequeue(t_queue *queue)
{
    if (!queue->head)
        return (NULL);
    t_node *temp = queue->head;
    char   *data = temp->data;
    queue->head = queue->head->next;
    if (!queue->head)
        queue->tail = NULL;
    free(temp);
    return (data);
}

void    clear_queue(t_queue *queue)
{
    while (queue->head)
        free(dequeue(queue));
}

char    *extract_line_from_queue(t_queue *queue)
{
    if (!queue || !queue->head)
        return (NULL);

    t_node  *current = queue->head;
    char    *line;
    size_t  total_length = 0;
    
    while (current && !ft_strchr(current->data, '\n'))
    {
        total_length += ft_strlen(current->data);
        current = current->next;
    }
    if (current)
        total_length += (ft_strchr(current->data, '\n') - current->data + 1);

    line = malloc(total_length + 1);
    if (!line)
        return (NULL);
    
    line[0] = '\0';
    while (queue->head && total_length > 0)
    {
        char *temp = dequeue(queue);
        if (temp)
        {
            strncat(line, temp, total_length);
            total_length -= ft_strlen(temp);
            free(temp);
        }
        else
        {
            break; // Avoid NULL usage
        }
    }
    return (line);
}