#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#ifndef BUFFER_SIZE
#define BUFFER_SIZE 42
#endif

static char	*extract_line(char *buffer);
static void	shift_buffer(char *buffer);
static int	find_newline(const char *buffer);

/**
 * get_next_line - Reads a file line by line using a static buffer.
 * @fd: File descriptor to read from.
 * 
 * Return: A dynamically allocated string containing a line, or NULL if EOF.
 */
char *get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;
	ssize_t		bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (!find_newline(buffer))
	{
		bytes_read = read(fd, buffer + find_newline(buffer), BUFFER_SIZE - find_newline(buffer));
		if (bytes_read <= 0)
			break;
		buffer[bytes_read] = '\0';
	}
	if (!buffer[0])  // No data left to read
		return (NULL);
	line = extract_line(buffer);
	shift_buffer(buffer);
	return (line);
}

/**
 * extract_line - Extracts the next line from the buffer.
 * @buffer: The static buffer containing file content.
 * 
 * Return: A dynamically allocated string containing the next line.
 */
static char *extract_line(char *buffer)
{
	int		len = 0;
	char	*line;

	while (buffer[len] && buffer[len] != '\n')
		len++;
	if (buffer[len] == '\n')
		len++;
	line = (char *)malloc(len + 1);
	if (!line)
		return (NULL);
	for (int i = 0; i < len; i++)
		line[i] = buffer[i];
	line[len] = '\0';
	return (line);
}

/**
 * shift_buffer - Shifts the buffer content after extracting a line.
 * @buffer: The static buffer to shift.
 */
static void shift_buffer(char *buffer)
{
	int i = 0, j = 0;

	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	while (buffer[i])
		buffer[j++] = buffer[i++];
	buffer[j] = '\0';
}

/**
 * find_newline - Checks if there's a newline character in the buffer.
 * @buffer: The buffer to search.
 * 
 * Return: 1 if newline exists, 0 otherwise.
 */
static int find_newline(const char *buffer)
{
	for (int i = 0; buffer[i]; i++)
		if (buffer[i] == '\n')
			return (1);
	return (0);
}

int main()
{
	int fd = open("text.txt", O_RDONLY);
	char *line;

	if (fd < 0)
		return (1);
	while ((line = get_next_line(fd)))
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}
