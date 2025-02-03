///* ************************************************************************** */
///*                                                                            */
///*                                                        :::      ::::::::   */
///*   get_next_line.h                                    :+:      :+:    :+:   */
///*                                                    +:+ +:+         +:+     */
///*   By: dyl-syzygy <dyl-syzygy@student.42.fr>      +#+  +:+       +#+        */
///*                                                +#+#+#+#+#+   +#+           */
///*   Created: 2025/01/30 23:33:39 by dyl-syzygy        #+#    #+#             */
///*   Updated: 2025/02/03 18:03:38 by dyl-syzygy       ###   ########.fr       */
///*                                                                            */
///* ************************************************************************** */
//
//#ifndef GET_NEXT_LINE_H
//# define GET_NEXT_LINE_H
//
//# include <stdlib.h>
//# include <unistd.h>
//#define BUFFER_SIZE 250
//
//char *get_next_line(int fd);
//char *ft_strchr(const char *str, int c);
//char *ft_strjoin(char *s1, char *s2);
//char *ft_strdup(const char *s1);
//size_t ft_strlen(const char *str);
//char *ft_substr(char const *s, unsigned int start, size_t len);
//void *ft_memcpy(void *dest, const void *src, size_t n);
//char	*get_next_line(int fd);
//
//size_t	ft_strclen(const char *s, int c);
//
//char	*ft_strchr(const char *s, int c);
//
//char	*ft_strndup(const char *s, size_t n);
//#endif


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

char	*get_next_line(int fd);

size_t	ft_strclen(const char *s, int c);

char	*ft_strchr(const char *s, int c);

char	*ft_strndup(const char *s, size_t n);

char	*ft_strjoin(char *s1, const char *s2);
void *ft_memmove(void *dst, const void *src, size_t n);
#endif