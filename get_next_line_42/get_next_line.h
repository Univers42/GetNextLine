/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 11:47:54 by dlesieur          #+#    #+#             */
/*   Updated: 2025/02/04 15:22:33 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

#include <stdlib.h>
#include <unistd.h>

#ifndef BUFFER_SIZE
    #define BUFFER_SIZE 1024  // Ensure BUFFER_SIZE is defined only once
#endif

typedef struct s_line
{
    char *content;
    struct s_line *next;
} t_line;

// Function prototypes
int contains_newline(char *str);
size_t bitwise_strlen(char *str, char stop);
char *ft_strndup(char *src, size_t n);
void store_chunks(int fd, t_line **head);
char *extract_line(t_line **head);
void free_list(t_line **head);
char *get_next_line(int fd);

#endif
