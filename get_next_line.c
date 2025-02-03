#include "get_next_line.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

typedef struct s_list
{
    char            *content;
    struct s_list   *next;
}   t_list;

// Append a new chunk to the linked list
static void append_chunk(t_list **head, char *chunk)
{
    t_list *new_node;
    t_list *temp;

    new_node = (t_list *)malloc(sizeof(t_list));
    if (!new_node)
        return;
    new_node->content = chunk;
    new_node->next = NULL;
    if (!(*head))
        *head = new_node;
    else
    {
        temp = *head;
        while (temp->next)
            temp = temp->next;
        temp->next = new_node;
    }
}

// Convert linked list to a single string
static char *list_to_string(t_list *head)
{
    size_t len = 0;
    t_list *temp = head;
    char *result;
    char *ptr;

    while (temp)
    {
        len += ft_strclen(temp->content, '\0');
        temp = temp->next;
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

// Free linked list
static void free_list(t_list **head)
{
    t_list *temp;
    t_list *next;

    temp = *head;
    while (temp)
    {
        next = temp->next;
        free(temp->content);
        free(temp);
        temp = next;
    }
    *head = NULL;
}

// Read and store data into linked list
static t_list *store_chunks(int fd)
{
    t_list *head = NULL;
    char *chunk;
    ssize_t bytes;

    chunk = (char *)malloc(BUFFER_SIZE + 1);
    if (!chunk)
        return (NULL);
    while ((bytes = read(fd, chunk, BUFFER_SIZE)) > 0)
    {
        chunk[bytes] = '\0';
        append_chunk(&head, ft_strndup(chunk, bytes));
        if (ft_strchr(chunk, '\n'))
            break;
    }
    free(chunk);
    return (head);
}

// Extract line from stored chunks
static char *get_line(t_list **head)
{
    char *full_str;
    char *line;
    size_t len;

    if (!(*head))
        return (NULL);
    full_str = list_to_string(*head);
    len = ft_strclen(full_str, '\n');
    if (full_str[len] == '\n')
        len++;
    line = ft_strndup(full_str, len);
    free(full_str);
    return (line);
}

// Store leftover after extracting line
static void get_leftover(t_list **head)
{
    char *full_str;
    char *leftover;
    size_t jump;
    size_t len;

    full_str = list_to_string(*head);
    jump = ft_strclen(full_str, '\n');
    if (full_str[jump] == '\n')
        jump++;
    len = ft_strclen(full_str, '\0') - jump;
    leftover = ft_strndup(full_str + jump, len);
    free(full_str);
    free_list(head);
    if (len > 0)
        append_chunk(head, leftover);
    else
        free(leftover);
}

// Main get_next_line function
char *get_next_line(int fd)
{
    static t_list *memory = NULL;
    char *line;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    if (!memory)
        memory = store_chunks(fd);
    if (!memory)
        return (NULL);
    line = get_line(&memory);
    get_leftover(&memory);
    return (line);
}

int main(void)
{
    char *file_name = "text.txt";
    int fd;
    char *line;

    // Open the file
    fd = open(file_name, O_RDONLY);
    if (fd == -1)
    {
        perror("Error opening file");
        return (1);
    }

    // Loop to read lines until the end of the file
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);  // Output the read line
        free(line);          // Free the allocated memory for the line
    }

    // Close the file descriptor
    close(fd);
    return (0);
}
