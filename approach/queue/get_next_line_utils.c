#include "get_next_line.h"

t_node *new_node(char *data) {
    t_node *node = malloc(sizeof(t_node));
    if (node == NULL) {
        return NULL;
    }
    node->data = data;
    node->next = NULL;
    return node;
}

// Function to initialize the queue
t_queue *create_queue() {
    t_queue *queue = malloc(sizeof(t_queue));
    if (queue == NULL) {
        return NULL;
    }
    queue->front = NULL;
    queue->rear = NULL;
    return queue;
}

// Function to enqueue data into the queue
void enqueue(t_queue *queue, char *data) {
    t_node *node = new_node(data);
    if (node == NULL) {
        return;
    }
    if (queue->rear == NULL) {
        queue->front = node;
        queue->rear = node;
    } else {
        queue->rear->next = node;
        queue->rear = node;
    }
}

// Function to dequeue data from the queue
char *dequeue(t_queue *queue) {
    if (queue->front == NULL) {
        return NULL;
    }
    t_node *temp = queue->front;
    char *data = temp->data;
    queue->front = queue->front->next;
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    free(temp);
    return data;
}

// Function to free all queue nodes
void free_queue(t_queue *queue) {
    while (queue->front != NULL) {
        char *data = dequeue(queue);
        free(data);
    }
    free(queue);
}