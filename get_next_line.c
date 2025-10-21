/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 00:55:37 by dlesieur          #+#    #+#             */
/*   Updated: 2025/10/21 03:00:02 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	init(t_file *scan);

char	*get_next_line(int fd)
{
	static t_file	scan;
	t_dynstr		line;
	t_state			st;

	line = (t_dynstr){NULL, 0, 0};
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (scan.cur == NULL || scan.end == NULL)
	{
		scan.cur = scan.buf;
		scan.end = scan.buf;
	}
	st = scan_nl(&scan, &line, fd);
	if (st == ST_ERR_ALLOC || st == ST_FILE_NOT_FOUND)
		return (reset(&line, &scan));
	if (st == ST_EOF)
	{
		if (line.size > 0)
			return (line.buf);
		return (reset(&line, &scan));
	}
	if (line.size == 0)
		return (reset(&line, NULL));
	return (line.buf);
}

char	*get_next_line_bonus(int fd)
{
	static t_file	*scan[FD_MAX] = {0};
	t_dynstr		line;
	t_state			st;

	line = (t_dynstr){NULL, 0, 0};
	if (fd < 0 || fd >= FD_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	init(scan[fd]);
	st = scan_nl(scan[fd], &line, fd);
	if (st == ST_ERR_ALLOC || st == ST_FILE_NOT_FOUND)
		return (reset(&line, scan[fd]));
	if (st == ST_EOF)
	{
		if (line.size > 0)
			return (line.buf);
		return (reset(&line, scan[fd]));
	}
	if (line.size == 0)
		return (reset(&line, NULL));
	return (line.buf);
}

static void	init(t_file *scan)
{
	if (!scan)
	{
		scan = malloc(sizeof(t_file));
		if (!scan)
			return (NULL);
		scan->cur = scan->buf;
		scan->end = scan->buf;
	}
}

__attribute__((weak))
int	main(int argc, char **argv)
{
	char	*line;
	int		fd;

	if (argc > 2)
		return (1);
	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd < 0)
			return (perror("open"), 1);
	}
	else
		fd = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (strcmp(line, "exit\n") == 0)
			break ;
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	if (argc == 2)
		close(fd);
	return (0);
}
