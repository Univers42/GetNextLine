/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 18:45:45 by dlesieur          #+#    #+#             */
/*   Updated: 2025/02/04 19:11:23 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdarg.h>
#include <fcntl.h>
#include <stdarg.h>
#include <unistd.h>

typedef struct s_line 
{
    char *content;
    struct s_line *next;
}t_line;

void append(t_list **head, char *buf)
{
    t_list *new_node;
    t_list *last_node;

    new_node = find_last_node(*head);
    new_node = (t_list *)malloc(sizeof(t_list));
    if(!new_node)
        return ;
    if (last_node == NULL)
        *head = new_node;
    else
    {
        last_node->next = new_node;
        new_node->str_buf = buf;
        new_node->next = NULL;
    }
}
void create_list(t_line **list,  int fd)
{
    //scan line if \n present
    //feetch the new line
    while(!new_line(*list))
    {
        int     char_read;
        char    *buf;
        //get inside loop if there isn't new_line
        buf = malloc(BUFFER_SIZE + 1);
        if (buf == NULL)
            return ;
        char_read = read(fd, buf, BUFFER_SIZE);
        //once the file is done we free the buffer
        if (!char_read)
        {
            free(buf);
            return ;
        }
        buf[char_read] = '\0';
        append(list, buf);
    }
}
int main(void)
{
    static t_line *new_list;
    char *next_line;
    int fd;
    
    new_list = NULL;
    if(fd < 0 || BUFFER_SIZE < 0 || read(fd, &next_line , 0) < 0)
    {
        perror("you've get an error either on file descriptor, buffer_size or read");
        return NULL;
    }
    ft_lstnew(&new_list, fd);
    if(list == NULL)
        return NULL;
    next_line = get_line(list);
}