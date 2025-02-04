#include <fcntl.h>
#include "ft_get_next_line.h"
#include <stdlib.h>
#include <stdio.h>

#ifndef
    #define BUFFER 1024
#endif
typedef struct s_line
{
    char *content;
    struct s_line *next;
}t_line

ft_get_next_line_bonus(int fd)
{
    char memory[BUFFER + 1];
    char *line;

    if(!memory)
        store_chunks(memory, fd);
    if(!memory)
        return NULL;
    line = get_line(&memory);
    
}

int main(int argc, char **argv)
{
    if(argc != 3)
    {
        fprintf(stderr, "./usage file1 file2");
        return (1);
    }
    char *file_name1 = argv[1];
    char *file_name2 = argv[2];
    int fd1;
    int fd2;

    fd1 = open(file_name1, O_RDONLY);
    
    fd2 = open(file_name2, O_RDONLY);
    if (!fd1 || !fd2)
    {
        perror("Failed to open for either file1 or file2\n");
        close(fd1);
        close(fd2);
        return (0);
    }
    if(ft_get_next_line_bonus())
    {
        
    }
}