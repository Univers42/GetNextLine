/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyl-syzygy <dyl-syzygy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 23:33:39 by dyl-syzygy        #+#    #+#             */
/*   Updated: 2025/01/30 23:53:25 by dyl-syzygy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
#define BUFFER_SIZE 250
// Function declarations for get_next_line and utility functions
char *get_next_line(int fd);
char *ft_strchr(const char *str, int c);
char *ft_strjoin(char const *s1, char const *s2);
char *ft_strdup(const char *s1);  // Declare ft_strdup
size_t ft_strlen(const char *str); // Declare ft_strlen
char *ft_substr(char const *s, unsigned int start, size_t len);
void *ft_memcpy(void *dest, const void *src, size_t n);

#endif
