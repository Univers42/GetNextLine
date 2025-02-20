/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyl-syzygy <dyl-syzygy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 23:17:19 by dyl-syzygy        #+#    #+#             */
/*   Updated: 2025/02/20 12:15:38 by dyl-syzygy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*d;
	const unsigned char	*s;

	d = (unsigned char *)dst;
	s = (const unsigned char *)src;
	if (d == s)
		return (dst);
	if (d < s)
	{
		while (len--)
			*d++ = *s++;
	}
	else
	{
		d += len;
		s += len;
		while (len--)
			*--d = *--s;
	}
	return (dst);
}

static char	*store_chunks(int fd, char *memory)
{
	char	*buffer;
	int		bytes_read;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	while (ft_strclen(memory, '\n') == ft_strclen(memory, '\0'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
		{
			free(buffer);
			if (bytes_read == 0)
				return (memory);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		memory = ft_strjoin(memory, buffer);
		if (!memory)
			return (free(buffer), NULL);
	}
	return (free(buffer), memory);
}

static char	*get_line(char *memory)
{
	char	*line;
	size_t	newline_idx;

	if (!memory || !*memory)
		return (NULL);
	newline_idx = ft_strclen(memory, '\n');
	line = malloc(newline_idx + 2);
	if (!line)
		return (NULL);
	ft_memmove(line, memory, newline_idx + 1);
	line[newline_idx + 1] = '\0';
	return (line);
}

static char	*get_leftover(char *memory)
{
	char	*ptr;
	char	*leftover;

	ptr = memory;
	while (*ptr && *ptr != '\n')
		ptr++;
	if (!*ptr)
		return (free(memory), NULL);
	leftover = ft_strndup(ptr + 1, strlen(ptr + 1));
	return (free(memory), leftover);
}

char	*get_next_line(int fd)
{
	static t_fd_list	*fd_list = NULL;
	t_fd_list			*fd_node;
	char				*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	fd_node = get_fd_node(&fd_list, fd);
	if (!fd_node)
		return (NULL);
	fd_node->memory = store_chunks(fd, fd_node->memory);
	if (!fd_node->memory)
		return (remove_fd_node(&fd_list, fd), NULL);
	line = get_line(fd_node->memory);
	fd_node->memory = get_leftover(fd_node->memory);
	if (!line)
		remove_fd_node(&fd_list, fd);
	return (line);
}
