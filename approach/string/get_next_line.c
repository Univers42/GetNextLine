//#include "get_next_line.h"
//#include <string.h>

// Helper function to find newline position
//static int find_newline(char *str)
//{
//    int i = 0;
//    if (!str)
//        return -1;
//    while (str[i])
//    {
//        if (str[i] == '\n')
//            return i;
//        i++;
//    }
//    return -1;
//}
//
//// Helper function to join two strings and free the old memory
//static char *str_join(char *s1, char *s2)
//{
//    int i = 0, j = 0, len1 = 0, len2 = 0;
//    char *new_str;
//
//    if (s1)
//        while (s1[len1]) len1++;
//    while (s2[len2]) len2++;
//
//    new_str = malloc(len1 + len2 + 1);
//    if (!new_str)
//        return NULL;
//
//    while (i < len1)
//    {
//        new_str[i] = s1[i];
//        i++;
//    }
//    while (j < len2)
//    {
//        new_str[i++] = s2[j++];
//    }
//    new_str[i] = '\0';
//
//    free(s1);  // Free old memory
//    return new_str;
//}
//
//// Reads from fd and stores data in memory
//static char *store_chunks(int fd, char *memory)
//{
//    char buffer[BUFFER_SIZE + 1];
//    int bytes_read;
//    
//    while (find_newline(memory) == -1)  // Read only if there's no newline
//    {
//        bytes_read = read(fd, buffer, BUFFER_SIZE);
//        if (bytes_read <= 0)
//            return memory;  // Return whatever is stored (even NULL if nothing)
//
//        buffer[bytes_read] = '\0';  // Null-terminate
//        memory = str_join(memory, buffer);
//        if (!memory)
//            return NULL;
//    }
//    return memory;
//}
//
//// Extracts the next line from memory
//static char *get_line(char *memory)
//{
//    int i = 0;
//    char *line;
//    
//    if (!memory || !memory[0])
//        return NULL;
//
//    while (memory[i] && memory[i] != '\n')
//        i++;
//    
//    line = malloc(i + 2);  // +2 to include '\n' and '\0'
//    if (!line)
//        return NULL;
//
//    for (int j = 0; j <= i; j++)
//        line[j] = memory[j];
//    line[i + 1] = '\0';
//
//    return line;
//}
//
//// Keeps only the leftover part of memory after '\n'
//static char *get_leftover(char *memory)
//{
//    int i = 0, j = 0;
//    char *leftover;
//
//    while (memory[i] && memory[i] != '\n')
//        i++;
//    if (!memory[i])  // No newline found, free memory
//    {
//        free(memory);
//        return NULL;
//    }
//
//    leftover = malloc(sizeof(char) * (strlen(memory) - i));
//    if (!leftover)
//        return NULL;
//
//    i++;  // Skip past '\n'
//    while (memory[i])
//        leftover[j++] = memory[i++];
//    leftover[j] = '\0';
//10000000
//    free(memory);
//    return leftover;
//}
//
//// Main get_next_line function
//char *get_next_line(int fd)
//{
//    static char *memory;
//    char *line;
//
//    if (fd < 0 || BUFFER_SIZE <= 0)
//        return NULL;
//
//    memory = store_chunks(fd, memory);
//    if (!memory)
//        return NULL;
//
//    line = get_line(memory);
//    memory = get_leftover(memory);  // Update static memory with leftover
//
//    return line;
//}

#include "get_next_line.h"
#include <string.h>
#include <stdlib.h>
#include <string.h>

// Helper function to find newline position
static int find_newline(char *str)
{
    if (!str)
        return -1;
    
    char *ptr = str;
    while (*ptr)  // Iterate through the string using pointer
    {
        if (*ptr == '\n')
            return ptr - str;  // Return the index of the newline
        ptr++;
    }
    return -1;  // No newline found
}

// Optimized function to join strings with dynamic allocation
//static char *str_join(char *s1, char *s2)
//{
//    int len1 = (s1) ? strlen(s1) : 0;
//    int len2 = strlen(s2);
//    char *new_str = realloc(s1, len1 + len2 + 1); // Reallocate existing memory
//
//    if (!new_str)
//        return NULL;
//
//    memcpy(new_str + len1, s2, len2 + 1); // Append new content
//    return new_str;
//}

// Reads from fd and stores data in memory efficiently
static char *store_chunks(int fd, char *memory)
{
    char    *buffer;
    int     bytes_read;

    bytes_read = 1;
    buffer = malloc(BUFFER_SIZE + 1);
    if(!buffer)
        return NULL;
    do {
        bytes_read = read(fd, buffer, BUFFER_SIZE);
        if (bytes_read < 0)
        {
            free(buffer);
            return memory;
        }
        
        if (bytes_read == 0)
            break;  // End of file
            
        buffer[bytes_read] = '\0';
        memory = ft_strjoin(memory, buffer);
        if (!memory)
            return NULL;
            
    } while (find_newline(memory) == -1);
    free(buffer);
    return memory;
}

static char *get_line(char *memory)
{
    char *line;
    char *ptr = memory;
    
    if (!memory || !*memory)
        return NULL;

    // Move pointer until we find newline or the end of the string
    while (*ptr && *ptr != '\n')
        ptr++;

    // Allocate space for the line (including space for the newline and '\0')
    line = malloc(ptr - memory + 2);  // +2 for '\n' and '\0'
    if (!line)
        return NULL;

    // Copy the content of memory up to the newline
    memmove(line, memory, ptr - memory + 1);  // +1 to include the newline
    line[ptr - memory + 1] = '\0';  // Null-terminate the line

    return line;
}


// Keeps only the leftover part of memory after '\n'
static char *get_leftover(char *memory)
{
    char *ptr = memory;
    char *leftover;

    // Move the pointer until we find the newline or end of string
    while (*ptr && *ptr != '\n')
        ptr++;

    if (!*ptr)  // No newline found
    {
        free(memory);
        return NULL;
    }

    // Skip past the newline and duplicate the rest of the string
    leftover = strdup(ptr + 1);
    free(memory);
    return leftover;
}


// Main function to read lines
char *get_next_line(int fd)
{
    static char *memory;
    char *line;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return NULL;

    memory = store_chunks(fd, memory);
    if (!memory)
        return NULL;

    line = get_line(memory);
    memory = get_leftover(memory);
    return line;
}

//int main(void)
//{
//    int fd;
//    char *line;
//
//    printf("=== Testing regular file ===\n");
//    fd = open("formatted_file.txt", O_RDONLY);
//    if (fd == -1)
//    {
//        printf("Error opening test.txt\n");
//        return (1);
//    }
//
//    line = get_next_line(fd);
//    while (line != NULL)
//    {
//        printf("%s", line);
//        free(line);
//        line = get_next_line(fd);
//    }
//    printf("\n\033[42mBRAVO !! You have succeed !\033[0m");
//    free(line);
//    close(fd);

    // Test Case 2: Reading from stdin
    //printf("\n=== Testing stdin ===\n");
    //printf("Enter text (press Ctrl+D when finished):\n");
    //line = get_next_line(STDIN_FILENO);
    //while (line != NULL)
    //{
    //    printf("Received: %s", line);
    //    free(line);
    //    line = get_next_line(STDIN_FILENO);
    //}
    //free(line);  // Free the final NULL pointer
//
    //// Test Case 3: Multiple file descriptors
    //printf("\n=== Testing multiple files ===\n");
    //fd = open("test.txt", O_RDONLY);
    //int fd2 = open("test2.txt", O_RDONLY);
    //
    //if (fd == -1 || fd2 == -1)
    //{
    //    printf("Error opening test files\n");
    //    return (1);
    //}
//
    //// Read alternating lines from both files
    //line = get_next_line(fd);
    //char *line2 = get_next_line(fd2);
    //while (line != NULL && line2 != NULL)
    //{
    //    printf("File 1: %s", line);
    //    printf("File 2: %s", line2);
    //    free(line);
    //    free(line2);
    //    line = get_next_line(fd);
    //    line2 = get_next_line(fd2);
    //}
    
    // Clean up remaining lines if any
    ///while (line != NULL)
    ///{
    ///    printf("File 1: %s", line);
    ///    free(line);
    ///    line = get_next_line(fd);
    ///}
    //while (line2 != NULL)
    //{
    //    printf("File 2: %s", line2);
    //    free(line2);
    //    line2 = get_next_line(fd2);
    //}
    
    //free(line);
    ////free(line2);
    //close(fd);
    //close(fd2);

//    return (0);
//}