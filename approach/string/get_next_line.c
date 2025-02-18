#include "get_next_line.h"

static int find_newline(char *str)
{
    if (!str)
        return -1;
    
    char *ptr = str;
    while (*ptr)
    {
        if (*ptr == '\n')
            return ptr - str;
        ptr++;
    }
    return -1;
}

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
    while (*ptr && *ptr != '\n')
        ptr++;
    line = malloc(ptr - memory + 2);
    if (!line)
        return NULL;
    memmove(line, memory, ptr - memory + 1); 
    line[ptr - memory + 1] = '\0';

    return line;
}

static char *get_leftover(char *memory)
{
    char *ptr = memory;
    char *leftover;

    while (*ptr && *ptr != '\n')
        ptr++;

    if (!*ptr)
    {
        free(memory);
        return NULL;
    }
    leftover = strdup(ptr + 1);
    free(memory);
    return leftover;
}


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

int main(void)
{
    int fd;
    char *line;

    printf("=== Testing regular file ===\n");
    fd = open("long_line.txt", O_RDONLY);
    if (fd == -1)
    {
        printf("Error opening test.txt\n");
        return (1);
    }

    line = get_next_line(fd);
    while (line != NULL)
    {
        printf("%s", line);
        free(line);
        line = get_next_line(fd);
    }
    printf("\n\033[42mBRAVO !! You have succeed !\033[0m");
    free(line);
    close(fd);

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

    return (0);
}