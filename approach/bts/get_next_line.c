#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 4

typedef struct s_bst_node {
    char *data;
    struct s_bst_node *left;
    struct s_bst_node *right;
} t_bst_node;

// Function to create a new BST node
t_bst_node *new_bst_node(char *data) {
    t_bst_node *node = malloc(sizeof(t_bst_node));
    if (!node) return NULL;
    node->data = strdup(data);  // Copy the data
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Function to insert data into the BST
t_bst_node *insert_bst(t_bst_node *root, char *data) {
    if (root == NULL) {
        return new_bst_node(data);
    }

    // Insert based on lexicographical comparison (or any other criterion)
    if (strcmp(data, root->data) < 0) {
        root->left = insert_bst(root->left, data);
    } else {
        root->right = insert_bst(root->right, data);
    }
    return root;
}

// In-order traversal of the BST (to get sorted data)
void inorder_traversal(t_bst_node *root) {
    if (root == NULL) return;
    inorder_traversal(root->left);
    printf("%s", root->data);  // Print data of the node
    inorder_traversal(root->right);
}

// Function to free the BST
void free_bst(t_bst_node *root) {
    if (root == NULL) return;
    free_bst(root->left);
    free_bst(root->right);
    free(root->data);  // Free the data
    free(root);
}

// Function to get the next line (with BST)
char *get_next_line(int fd) {
    static char buffer[BUFFER_SIZE];
    int bytes_read;
    char *line = malloc(1);
    int line_len = 0;

    if (!line) return NULL;
    line[0] = '\0';

    while ((bytes_read = read(fd, buffer, BUFFER_SIZE - 1)) > 0) {
        buffer[bytes_read] = '\0';  // Null-terminate buffer

        // Add this chunk to the BST
        static t_bst_node *root = NULL;
        root = insert_bst(root, buffer);

        // Perform in-order traversal and get the full line
        inorder_traversal(root);
        
        // Here you would need to check for a newline and break
        // This is an overly simplified demonstration of how the BST is being used
    }

    return line;
}

int main(void) {
    int fd = open("text.txt", O_RDONLY);
    if (fd == -1) {
        printf("Error opening file\n");
        return 1;
    }

    char *next_line;
    while ((next_line = get_next_line(fd)) != NULL) {
        printf("Line: %s\n", next_line);
        free(next_line);  // Free allocated memory for line
    }

    close(fd);
    return 0;
}
