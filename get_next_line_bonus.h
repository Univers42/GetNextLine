#ifndef GNL_BONUS_H
#define GNL_BONUS_H

#include <stdlib.h>
#include <unistd.h>

#ifndef BUFFER_SIZE
	#define BUFFER_SIZE 42
#endif

#ifndef FD_MAX
	#define FD_MAX 1024  // Maximum number of FDs supported
#endif

typedef struct s_fd_buffer
{
	char	buffer[BUFFER_SIZE + 1];
	int		buffer_pos;
	int		buffer_len;
}	t_fd_buffer;

char 	*str_join(char *s1, char *s2, int len_s2);
int 	find_newline(char *str);
char 	*str_dup(char *s);
#endif