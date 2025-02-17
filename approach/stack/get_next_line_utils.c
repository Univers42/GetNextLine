#include "get_next_line.h"
// Function to free the stack
void free_stack(t_stack *stack) {
    while (stack->top != NULL) {
        char *data = pop(stack);
        free(data);
    }
    free(stack);
}

t_stack *create_stack() {
    t_stack *stack = malloc(sizeof(t_stack));
    if (!stack) return NULL;
    stack->top = NULL;
    stack->size = 0;
    return stack;
}

void push(t_stack *stack, char *data) {
    t_node *node = malloc(sizeof(t_node));
    if (!node) return;
    node->data = data;
    node->next = stack->top;
    stack->top = node;
    stack->size++;
}

char *pop(t_stack *stack) {
    if (stack->top == NULL) return NULL;
    t_node *node = stack->top;
    char *data = node->data;
    stack->top = node->next;
    free(node);
    stack->size--;
    return data;
}
