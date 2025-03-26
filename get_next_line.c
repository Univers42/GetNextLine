/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 22:47:22 by dyl-syzygy        #+#    #+#             */
/*   Updated: 2025/02/25 20:47:06 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_store_chunks(int fd, char *memory)
{
	char	*buffer;
	char	*new_memory;
	t_ssize	bytes_read;

	bytes_read = 1;
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	while (ft_find_newline(memory) == -1)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(buffer), memory);
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		new_memory = ft_strjoin(memory, buffer);
		if (!new_memory)
			return (free(buffer), NULL);
		memory = new_memory;
	}
	return (free(buffer), memory);
}

static char	*ft_get_line(char *memory)
{
	char	*line;
	char	*ptr;

	if (!memory || !*memory)
		return (NULL);
	ptr = memory;
	while (*ptr && *ptr != '\n')
		ptr++;
	line = malloc((size_t)(ptr - memory + 2));
	if (!line)
		return (NULL);
	ft_memmove(line, memory, (size_t)(ptr - memory + 1));
	line[ptr - memory + 1] = '\0';
	return (line);
}

static char	*ft_get_leftover(char *memory)
{
	char	*ptr;
	char	*leftover;

	ptr = memory;
	while (*ptr && *ptr != '\n')
		ptr++;
	if (!*ptr)
		return (free(memory), NULL);
	leftover = ft_strndup(ptr + 1, (t_size)ft_strlen(ptr + 1));
	return (free(memory), leftover);
}

char	*get_next_line(int fd)
{
	static char	*memory;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	memory = ft_store_chunks(fd, memory);
	if (!memory)
		return (NULL);
	line = ft_get_line(memory);
	memory = ft_get_leftover(memory);
	return (line);
}

//int main(void)
//{
//    char *line;
//    int fd = open("test.txt", O_RDONLY);  // Example file
//
//    if (fd < 0)
//        return (1);
//
//    while ((line = get_next_line(fd)) != NULL)
//    {
//        printf("%s", line);
//        free(line); // Free each line after printing
//    }
//
//    close(fd);
//
//    return (0);
//}
//int main(void)
//{
//	int fd;
//	char *line;
//
//	printf("=== Testing regular file ===\n");
//	fd = open("long_line.txt", O_RDONLY);
//	if (fd == -1)
//	{
//		printf("Error opening test.txt\n");
//		return (1);
//	}
//
//	line = get_next_line(fd);
//	while (line != NULL)
//	{
//		printf("%s", line);
//		free(line);
//		line = get_next_line(fd);
//	}
//	printf("\n\033[42mBRAVO !! You have succeed !\033[0m");
//	free(line);
//	close(fd);
	// Test Case 2: Reading from stdin
	//printf("\n=== Testing stdin ===\n");
	//printf("Enter text (press Ctrl+D when finished):\n");
	//line = get_next_line(STDIN_FILENO);
	//while (line != NULL)
	//{
	//    printf("Received: %s", line);
	//    free(line);
	//    line = get_next_line(STDIN_FILENO);
	//}
	//free(line);  // Free the final NULL pointer
//
	//// Test Case 3: Multiple file descriptors
	//printf("\n=== Testing multiple files ===\n");
	//fd = open("test.txt", O_RDONLY);
	//int fd2 = open("test2.txt", O_RDONLY);
	//
	//if (fd == -1 || fd2 == -1)
	//{
	//    printf("Error opening test files\n");
	//    return (1);
	//}
//
	//// Read alternating lines from both files
	//line = get_next_line(fd);
	//char *line2 = get_next_line(fd2);
	//while (line != NULL && line2 != NULL)
	//{
	//    printf("File 1: %s", line);
	//    printf("File 2: %s", line2);
	//    free(line);
	//    free(line2);
	//    line = get_next_line(fd);
	//    line2 = get_next_line(fd2);
	//}

	// Clean up remaining lines if any
	///while (line != NULL)
	///{
	///    printf("File 1: %s", line);
	///    free(line);
	///    line = get_next_line(fd);
	///}
	//while (line2 != NULL)
	//{
	//    printf("File 2: %s", line2);
	//    free(line2);
	//    line2 = get_next_line(fd2);
	//}
	//free(line);
	////free(line2);
	//close(fd);
	//close(fd2);

//	return (0);
//}