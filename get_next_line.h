/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 23:33:39 by dyl-syzygy        #+#    #+#             */
/*   Updated: 2025/02/01 13:56:59 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
#define BUFFER_SIZE 250
// Function declarations for get_next_line and utility functions
char    *get_next_line(int fd);
char    *ft_strchr(const char *str, int c);
char    *ft_strjoin(char const *s1, char const *s2);
char    *ft_strdup(const char *s1);  // Declare ft_strdup
char    *ft_substr(char const *s, unsigned int start, size_t len);
void    *ft_memcpy(void *dest, const void *src, size_t n);
size_t  ft_strlen(const char *str); // Declare ft_strlen

#endif
