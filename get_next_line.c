#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 1024

typedef struct s_queue_node {
    char *data;
    struct s_queue_node *next;
} t_queue_node;

typedef struct s_queue {
    t_queue_node *head;
    t_queue_node *tail;
} t_queue;

t_queue *queue_init(void) {
    t_queue *queue = malloc(sizeof(t_queue));
    if (!queue)
        return NULL;
    queue->head = NULL;
    queue->tail = NULL;
    return queue;
}

void enqueue(t_queue *queue, const char *data) {
    t_queue_node *node = malloc(sizeof(t_queue_node));
    if (!node)
        return;
    node->data = strdup(data);
    node->next = NULL;
    
    if (!queue->head)
        queue->head = node;
    else
        queue->tail->next = node;
    queue->tail = node;
}

char *dequeue(t_queue *queue) {
    if (!queue->head)
        return NULL;
    
    t_queue_node *temp = queue->head;
    char *data = temp->data;
    queue->head = queue->head->next;
    if (!queue->head)
        queue->tail = NULL;
    
    free(temp);
    return data;
}

char *join_and_free(char *s1, const char *s2) {
    size_t len1 = s1 ? strlen(s1) : 0;
    size_t len2 = s2 ? strlen(s2) : 0;
    char *new = malloc(len1 + len2 + 1);
    if (!new)
        return NULL;
    
    if (s1) {
        strcpy(new, s1);
        free(s1);
    }
    strcpy(new + len1, s2);
    
    return new;
}

char *find_newline(char **stash) {
    if (!*stash)
        return NULL;
    
    char *newline_pos = strchr(*stash, '\n');
    if (!newline_pos)
        return NULL;
    
    size_t line_length = newline_pos - *stash + 1;
    char *line = strndup(*stash, line_length);
    
    char *new_stash = strdup(newline_pos + 1);
    free(*stash);
    *stash = new_stash;
    
    return line;
}

void process_buffer(char **stash, const char *buffer, int bytes_read) {
    buffer[bytes_read] = '\0';
    *stash = join_and_free(*stash, buffer);
}

char *get_next_line(int fd) {
    static char *stash[1024] = {NULL};
    char buffer[BUFFER_SIZE + 1];
    int bytes_read;
    
    if (fd < 0 || BUFFER_SIZE <= 0)
        return NULL;
    
    while (1) {
        bytes_read = read(fd, buffer, BUFFER_SIZE);
        if (bytes_read == -1)
            return NULL;
        if (bytes_read == 0 && (!stash[fd] || !*stash[fd]))
            return NULL;
        
        process_buffer(&stash[fd], buffer, bytes_read);
        char *line = find_newline(&stash[fd]);
        if (line)
            return line;
    }
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }
    
    int fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        perror("Error opening file");
        return 1;
    }
    
    char *line;
    while ((line = get_next_line(fd))) {
        printf("%s", line);
        free(line);
    }
    
    close(fd);
    return 0;
}
