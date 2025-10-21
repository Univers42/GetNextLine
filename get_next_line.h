/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 02:57:25 by dlesieur          #+#    #+#             */
/*   Updated: 2025/10/21 02:58:20 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <stdbool.h>
# include <errno.h>
# include <fcntl.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# define FD_MAX 10000
# define DFLT_CAP 64

typedef enum e_state
{
	ST_FILE_NOT_FOUND = -1,
	ST_OK = 0,
	ST_FOUND_NL,
	ST_INFO_BASE = 100,
	ST_FILLED,
	ST_SCANNING,
	ST_RESET_ALLOC,
	ST_RESET_PTR,
	ST_EOF,
	ST_ERR_BASE = 200,
	ST_ERR_ALLOC,
	ST_ERR_FATAL
}	t_state;

typedef struct s_file
{
	char	buf[BUFFER_SIZE];
	char	*cur;
	char	*end;
}	t_file;

typedef struct s_dynstr
{
	char	*buf;
	size_t	size;
	size_t	cap;
}	t_dynstr;

char	*get_next_line(int fd);
char	*get_next_line_bonus(int fd);
t_state	ensure_cap(char **line, size_t *cap, size_t need);
t_state	append_from_buffer(t_file *scan, t_dynstr *line);
t_state	refill(t_file *scan, int fd);
t_state	scan_nl(t_file *scan, t_dynstr *line, int fd);

static inline void	*ft_memmove(void *dst, const void *src, size_t n)
{
	const unsigned char	*s = (unsigned char *)src;
	unsigned char		*d;

	d = (unsigned char *)dst;
	if (d == s)
		return (dst);
	else if (d < s && n)
	{
		while (n--)
			*d++ = *s++;
	}
	else
	{
		d += n;
		s += n;
		while (n--)
			*--d = *--s;
	}
	return (dst);
}

static inline void	*ft_realloc(void *ptr, size_t old_cap, size_t new_cap)
{
	void	*tmp;
	size_t	select_size;

	if (new_cap)
	{
		tmp = malloc(new_cap);
		if (!tmp)
			return (NULL);
	}
	if (ptr && old_cap)
	{
		if (old_cap < new_cap)
			select_size = old_cap;
		else
			select_size = new_cap;
		ft_memmove(tmp, ptr, select_size);
		free(ptr);
	}
	return (tmp);
}

static inline char	*ft_strnchr(char *ptr, int c, size_t n)
{
	while (n--)
	{
		if (*ptr == c)
			return (ptr);
		ptr++;
	}
	return (NULL);
}

static inline char	*reset(t_dynstr *line, t_file *scan)
{
	if (line)
	{
		free(line->buf);
		line->buf = NULL;
		line->size = 0;
		line->cap = 0;
	}
	if (scan)
	{
		scan->cur = scan->buf;
		scan->end = scan->buf;
	}
	return (NULL);
}

#endif