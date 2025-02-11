#include "get_next_line.h"

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

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		if (s[i] == c)
			return ((char *)s + i);
		i++;
	}
	return (NULL);
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


//char	*ft_strjoin(char *s1, const char *s2)
//{
//    char *new_str, *ptr;
//    int len1 = 0, len2 = 0;
//
//    if (s1)
//        while (*(s1 + len1)) 
//            len1++;
//    while (*(s2 + len2)) 
//        len2++;
//
//    new_str = malloc(len1 + len2 + 1);
//    if (!new_str)
//        return NULL;
//
//    ptr = new_str;
//
//    while (s1 && *s1)  
//        *ptr++ = *s1++;
//    while (*s2)  
//        *ptr++ = *s2++;
//
//    *ptr = '\0';
//
//    free(s1 - len1);
//    return new_str;
//}

// Efficient string join with memory reallocation
char	*ft_strjoin(char *s1, const char *s2)
{
	size_t	len1 = (s1) ? ft_strclen(s1, '\0') : 0;
	size_t	len2 = ft_strclen(s2, '\0');
	char	*new_str = (char *)malloc(len1 + len2 + 1);
	size_t	i = 0, j = 0;

	if (!new_str)
		return (NULL);
	if (s1)
	{
		while (s1[i])
		{
			new_str[i] = s1[i];
			i++;
		}
		free(s1);
	}
	while (s2[j])
		new_str[i++] = s2[j++];
	new_str[i] = '\0';
	return (new_str);
}
