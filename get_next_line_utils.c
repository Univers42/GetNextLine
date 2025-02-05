/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 14:23:13 by dlesieur          #+#    #+#             */
/*   Updated: 2025/02/05 14:28:45 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int len_to_newline(t_list *list)
{
    
}

void copy_str(t_list *list, char *dest)
{
       int i = 0;
       while (list)
       {
       }
}

static void free_list(t_list **list)
{
    t_list *temp;
    
    while (*list)
    {
        temp = (*list)->next;
        free((*list)->new_line);
        free(*list);
        *list = temp;
    }
}

static int found_newline(t_list *list)
{
    while (list)
    {
        if (list->new_line && strchr(list->new_line, '\n'))
            return 1;
        list = list->next;
    }
    return 0;
}