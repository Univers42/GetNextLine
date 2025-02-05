#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 45
#endif

typedef struct s_node
{
    char data[BUFFER_SIZE];
    struct s_node *next;
} t_node;

static t_node *nodes[1024] = {NULL};

static char *extract_line(t_node **head, int *line_length);
static void shift_buffer(t_node **head, int *line_length);
static int find_newline(t_node *head);

int get_next_line(int fd, char **line)
{
    t_node *current = nodes[fd];
    t_node *new_node;
    int bytes_read;
    int line_length = 0;
    
    // If no nodes exist for this file descriptor, initialize the first node
    if (!current)
    {
        current = malloc(sizeof(t_node));
        if (!current)
            return (-1);
        current->next = NULL;
        nodes[fd] = current;
    }

    // Read and store data in the linked list until a newline is found or EOF is reached
    while ((bytes_read = read(fd, current->data, BUFFER_SIZE)) > 0)
    {
        current->data[bytes_read] = '\0';
        
        if (find_newline(current))
            break;

        // Allocate a new node for the next chunk of data
        new_node = malloc(sizeof(t_node));
        if (!new_node)
            return (-1);
        new_node->next = NULL;
        current->next = new_node;
        current = new_node;
    }

    // If nothing was read, return NULL (EOF or error)
    if (bytes_read <= 0 && !current->data[0])
        return (0);

    // Extract the line
    *line = extract_line(&nodes[fd], &line_length);
    if (!*line)
        return (-1);

    // Shift the buffer (advance to the next chunk)
    shift_buffer(&nodes[fd], &line_length);

    return (1);
}

// Function to check if a newline exists in the current node data
static int find_newline(t_node *head)
{
    int i = 0;
    while (head && head->data[i])
    {
        if (head->data[i] == '\n')
            return (1);
        i++;
    }
    return (0);
}

// Function to concatenate the chunks into a single line
static char *extract_line(t_node **head, int *line_length)
{
    t_node *current = *head;
    int len = 0;
    char *line;
    int i, j;

    // Calculate the length of the line by traversing the nodes
    while (current)
    {
        i = 0;
        while (current->data[i] && current->data[i] != '\n')
        {
            len++;
            i++;
        }
        if (current->data[i] == '\n')
        {
            len++;  // Include the newline
            break;
        }
        current = current->next;
    }

    // Allocate memory for the line
    line = malloc(len + 1);
    if (!line)
        return (NULL);

    // Fill the line with data
    current = *head;
    i = 0;
    while (current)
    {
        j = 0;
        while (current->data[j] && current->data[j] != '\n')
        {
            line[i++] = current->data[j++];
        }
        if (current->data[j] == '\n')
        {
            line[i++] = current->data[j];
            break;
        }
        current = current->next;
    }
    line[i] = '\0';
    *line_length = len;
    return (line);
}

// Function to shift the buffer forward (removes the processed data)
static void shift_buffer(t_node **head, int *line_length)
{
    t_node *current = *head;
    t_node *next_node;
    int i = *line_length;
    
    // Traverse the linked list and remove the used data
    while (current && i > 0)
    {
        int j = 0;
        while (current->data[j] && i > 0)
        {
            if (current->data[j] == '\n')
                return;  // Stop if newline is found
            i--;
            j++;
        }
        next_node = current->next;
        free(current);
        current = next_node;
    }
    *head = current;
}

#include <stdio.h>
#include <fcntl.h>

int get_next_line(int fd, char **line);

int main()
{
    int fd = open("text.txt", O_RDONLY);
    char *line;

    if (fd < 0)
        return (1);

    while (get_next_line(fd, &line) > 0)
    {
        printf("Line: %s\n", line);
        free(line);  // Don't forget to free the line!
    }

    close(fd);
    return (0);
}
