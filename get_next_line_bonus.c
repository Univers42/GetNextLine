#include "get_next_line_bonus.h"
static int	fill_buffer(int fd, t_fd_buffer *fd_buf)
{
	fd_buf->buffer_len = read(fd, fd_buf->buffer, BUFFER_SIZE);
	fd_buf->buffer_pos = 0;
	return (fd_buf->buffer_len);
}

static int	process_line(char **line, t_fd_buffer *fd_buf)
{
	int	i;

	i = 0;
	while (fd_buf->buffer_pos < fd_buf->buffer_len
		&& fd_buf->buffer[fd_buf->buffer_pos] != '\n')
	{
		*line = str_join(*line, &fd_buf->buffer[fd_buf->buffer_pos], 1);
		if (!*line)
			return (-1);
		fd_buf->buffer_pos++;
		i++;
	}
	if (fd_buf->buffer_pos < fd_buf->buffer_len
		&& fd_buf->buffer[fd_buf->buffer_pos] == '\n')
	{
		fd_buf->buffer_pos++;
		return (1);
	}
	return (i);
}

static int	handle_read(int fd, t_fd_buffer *fd_buf)
{
	if (fd_buf->buffer_pos == fd_buf->buffer_len)
	{
		if (fill_buffer(fd, fd_buf) <= 0)
			return (0);
	}
	return (1);
}

int	get_next_line(int fd, char **line)
{
	static t_fd_buffer	fd_buffers[FD_MAX];
	int					result;

	if (fd < 0 || fd >= FD_MAX || !line || BUFFER_SIZE <= 0)
		return (-1);
	*line = malloc(1);
	if (!*line)
		return (-1);
	(*line)[0] = '\0';
	while (handle_read(fd, &fd_buffers[fd]) > 0)
	{
		result = process_line(line, &fd_buffers[fd]);
		if (result != 0)
			return (result);
	}
	free(*line);
	return (0);
}
