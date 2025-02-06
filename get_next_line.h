#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char *get_next_line(int fd);
char *ft_strjoin(char *s1, char const *s2);
char *ft_strdup(const char *src);
char *ft_strchr(const char *s, int c);
void *ft_calloc(size_t count, size_t size);
size_t	ft_strclen(const char *s, int c);
char	*ft_strndup(const char *s, size_t n);
void *ft_memcpy(void *dst, const void *src, size_t n);
size_t ft_strlen(char *str);
#endif