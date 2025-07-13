/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 01:02:18 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/14 01:29:19 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

// Conditional header inclusion based on compile mode
#ifdef BONUS
 #include "get_next_line_bonus.h"
#else
 #include "get_next_line.h"
#endif

typedef void* t_addr;

typedef enum e_msg
{
	NOT_FOUND = 404,
} t_msg;

typedef struct s_line
{
	t_addr	mem;
	size_t	size;
}			t_line;

int main()
{
	int		fd;
	FILE	*fptr;
	t_line	line_data;
	char	*line;

	fptr = fopen("./register.txt", "w");
	if (!fptr)
	{
		perror("Error opening file");
		return 1;
	}
	fd = fileno(fptr);
	line = get_next_line(STDIN_FILENO);
	while (line)
	{
		line_data.mem = (t_addr)line;
		line_data.size = strlen((char*)line_data.mem);
		write(fd, line_data.mem, line_data.size);
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
	
	// Close file
	fclose(fptr);
	
	return 0;
}