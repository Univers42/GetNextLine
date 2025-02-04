/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 11:47:54 by dlesieur          #+#    #+#             */
/*   Updated: 2025/02/04 12:56:44 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GNL_H
#define GNL_h

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#ifndef BUFFER_SIZE
    # define BUFFER_SIZE 255
#endif
typedef struct s_list
{
    char            *content;
    struct s_list   *next;
}                   t_list;
typedef unsigned long int t_size;

ft_strjoin();
ft_strlcpy();
ft_strlcpy();
#endif