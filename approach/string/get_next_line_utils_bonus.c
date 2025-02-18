/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+    */
/*   By: dyl-syzygy <dyl-syzygy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 23:17:19 by dyl-syzygy        #+#    #+#             */
/*   Updated: 2025/02/18 23:39:23 by dyl-syzygy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strclen(const char *s, int c)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

char	*ft_strndup(const char *s, size_t n)
{
	char	*dup;
	size_t	i;

	i = 0;
	dup = (char *)malloc(n + 1);
	if (!dup)
		return (NULL);
	while (s[i] && i < n)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*ft_strjoin(char *s1, const char *s2)
{
	int		len2;
	int		len1;
	char	*new_str;
	char	*ptr;

	len1 = 0;
	len2 = 0;
	if (s1)
	{
		while (*(s1 + len1))
			len1++;
	}
	while (*(s2 + len2))
		len2++;
	new_str = malloc(len1 + len2 + 1);
	if (!new_str)
		return (NULL);
	ptr = new_str;
	while (s1 && *s1)
		*ptr++ = *s1++;
	while (*s2)
		*ptr++ = *s2++;
	*ptr = '\0';
	free(s1 - len1);
	return (new_str);
}

t_fd_list	*get_fd_node(t_fd_list **fd_list, int fd)
{
	t_fd_list	*current;
	t_fd_list	*new_node;

	current = *fd_list;
	while (current)
	{
		if (current->fd == fd)
			return (current);
		current = current->next;
	}
	new_node = malloc(sizeof(t_fd_list));
	if (!new_node)
		return (NULL);
	new_node->fd = fd;
	new_node->memory = NULL;
	new_node->next = *fd_list;
	*fd_list = new_node;
	return (new_node);
}

void	remove_fd_node(t_fd_list **fd_list, int fd)
{
	t_fd_list	*prev;
	t_fd_list	*current;

	prev = NULL;
	current = *fd_list;
	while (current)
	{
		if (current->fd == fd)
		{
			if (prev)
				prev->next = current->next;
			else
				*fd_list = current->next;
			free(current->memory);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}
