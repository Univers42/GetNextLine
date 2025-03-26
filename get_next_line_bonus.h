/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 23:26:55 by dyl-syzygy        #+#    #+#             */
/*   Updated: 2025/02/25 21:15:31 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef long			t_ssize;
typedef unsigned long	t_size;
typedef struct s_fd_list
{
	t_size				fd;
	char				*memory;
	struct s_fd_list	*next;
}	t_fd_list;

char		*get_next_line(int fd);
char		*ft_strndup(const char *s, size_t n);
char		*ft_strjoin(char *s1, const char *s2);
t_fd_list	*ft_get_fd_node(t_fd_list **fd_list, t_size fd);
void		ft_remove_fd_node(t_fd_list **fd_list, t_size fd);
size_t		ft_strclen(const char *s, int c);

#endif
