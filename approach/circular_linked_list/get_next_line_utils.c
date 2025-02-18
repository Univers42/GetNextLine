#include "get_next_line.h"

t_node *new_node(char *data) {
    t_node *node = malloc(sizeof(t_node));
    if (!node) {
        return NULL;
    }
    node->data = data;
    node->next = NULL;
    return node;
}

t_circular_list *create_circular_list() {
    t_circular_list *list = malloc(sizeof(t_circular_list));
    if (!list) {
        return NULL;
    }
    list->head = NULL;
    list->tail = NULL;
    return list;
}

void append_to_circular_list(t_circular_list *list, char *data) {
    t_node *node = new_node(data);
    if (!node) {
        return;
    }
    if (list->head == NULL) {
        list->head = node;
        list->tail = node;
        node->next = node;
    } else {
        list->tail->next = node;
        list->tail = node;
        node->next = list->head;
    }
}

char *dequeue_from_circular_list(t_circular_list *list) {
    if (list->head == NULL) {
        return NULL;
    }

    t_node *first_node = list->head;
    char *data = first_node->data;

    if (list->head == list->tail) {
        list->head = NULL;
        list->tail = NULL;
    } else {
        list->head = first_node->next;
        list->tail->next = list->head;
    }
    
    free(first_node);
    return data;
}

void free_circular_list(t_circular_list *list) {
    while (list->head != NULL) {
        char *data = dequeue_from_circular_list(list);
        free(data);
    }
    free(list);
}
