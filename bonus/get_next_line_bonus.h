#ifndef GET_NEXT_LINE_BONUS_H
#define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42  // Default buffer size
# endif

# define MAX_FD 1024  // Maximum number of file descriptors to track

char *get_next_line(int fd);
char *ft_strjoin(char *s1, char *s2);
char *ft_strdup(char *s);
char *ft_strchr(char *s, int c);
size_t ft_strlen(char *s);

#endif
