/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyl-syzygy <dyl-syzygy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 23:06:30 by dyl-syzygy        #+#    #+#             */
/*   Updated: 2025/02/18 23:13:54 by dyl-syzygy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

int	find_newline(char *str)
{
	char	*ptr;

	if (!str)
		return (-1);
	ptr = str;
	while (*ptr)
	{
		if (*ptr == '\n')
			return (ptr - str);
		ptr++;
	}
	return (-1);
}

void	*ft_memmove(void *dst, const void *src, size_t len)
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
