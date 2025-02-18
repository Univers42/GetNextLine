/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyl-syzygy <dyl-syzygy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 23:26:55 by dyl-syzygy        #+#    #+#             */
/*   Updated: 2025/02/18 23:46:11 by dyl-syzygy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <string.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# define MAX_FILES 10000

typedef struct s_fd_list
{
	int					fd;
	char				*memory;
	struct s_fd_list	*next;
}	t_fd_list;

char		*get_next_line(int fd);
char		*ft_strndup(const char *s, size_t n);
char		*ft_strjoin(char *s1, const char *s2);
t_fd_list	*get_fd_node(t_fd_list **fd_list, int fd);
void		remove_fd_node(t_fd_list **fd_list, int fd);
size_t		ft_strclen(const char *s, int c);

#endif