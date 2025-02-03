//#include "get_next_line.h"
//#include <stdlib.h>
//
//// ft_strlen: Returns the length of a string
//size_t ft_strlen(const char *str)
//{
//    size_t len = 0;
//    while (str[len])
//        len++;
//    return len;
//}
//
//// ft_strdup: Duplicates a string
//char *ft_strdup(const char *s1)
//{
//    size_t len = ft_strlen(s1);
//    char *copy = malloc(len + 1);  // +1 for the null terminator
//    if (!copy)
//        return NULL;
//    for (size_t i = 0; i < len; i++)
//        copy[i] = s1[i];
//    copy[len] = '\0';  // Null-terminate the string
//    return copy;
//}
//
//
//
//// ft_substr: Extracts a substring from a string
//char *ft_substr(char const *s, unsigned int start, size_t len)
//{
//    if (!s)
//        return NULL;
//    size_t str_len = ft_strlen(s);
//    if (start >= str_len)
//        return ft_strdup("");  // Return an empty string if start is beyond the string length
//    if (len > str_len - start)
//        len = str_len - start;
//    char *substr = malloc(len + 1);
//    if (!substr)
//        return NULL;
//    for (size_t i = 0; i < len; i++)
//        substr[i] = s[start + i];
//    substr[len] = '\0';  // Null-terminate the substring
//    return substr;
//}
//
//// ft_memcpy: Copies memory from one location to another
//
//
//#include "get_next_line.h"
//
//size_t	ft_strclen(const char *s, int c)
//{
//	size_t	i;
//
//	i = 0;
//	if (!s)
//		return (0);
//	while (s[i] && s[i] != c)
//		i++;
//	return (i);
//}
//
//char	*ft_strchr(const char *s, int c)
//{
//	size_t	i;
//
//	i = 0;
//	if (!s)
//		return (NULL);
//	while (s[i])
//	{
//		if (s[i] == c)
//			return ((char *)s + i);
//		i++;
//	}
//	return (NULL);
//}
//
//char	*ft_strndup(const char *s, size_t n)
//{
//	char	*dup;
//	size_t	i;
//
//	i = 0;
//	dup = (char *)malloc(n + 1);
//	if (!dup)
//		return (NULL);
//	while (s[i] && i < n)
//	{
//		dup[i] = s[i];
//		i++;
//	}
//	dup[i] = '\0';
//	return (dup);
//}
//
//char	*ft_strjoin(char *s1, const char *s2)
//{
//	size_t	i;
//	size_t	size;
//	char	*res;
//
//	i = 0;
//	size = 0;
//	if (s1)
//		size = ft_strclen(s1, '\0');
//	size += ft_strclen(s2, '\0') + 1;
//	res = (char *)malloc(size);
//	if (!res)
//		return (NULL);
//	if (s1)
//		while (s1[i])
//			*(res++) = s1[i++];
//	res -= ft_strclen(s1, '\0');
//	while (*s2)
//		res[i++] = *(s2++);
//	res[i] = '\0';
//	if (s1)
//		free(s1);
//	return (res);
//}

#include "get_next_line.h"


void *ft_memmove(void *dst, const void *src, size_t n)
{
    unsigned char *cpy_dest;
    const unsigned char *cpy_src;

    cpy_dest = (unsigned char *)dst;
    cpy_src = (const unsigned char *)src;

    // If destination is before the source, copy forward
    if (cpy_dest < cpy_src)
    {
        while (n--)
            *cpy_dest++ = *cpy_src++;
    }
    // If destination is after the source, copy backward
    else
    {
        cpy_dest += n;
        cpy_src += n;
        while (n--)
            *--cpy_dest = *--cpy_src;
    }

    return dst;
}
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

char	*ft_strjoin(char *s1, const char *s2)
{
	size_t	i;
	size_t	size;
	char	*res;

	i = 0;
	size = 0;
	if (s1)
		size = ft_strclen(s1, '\0');
	size += ft_strclen(s2, '\0') + 1;
	res = (char *)malloc(size);
	if (!res)
		return (NULL);
	if (s1)
		while (s1[i])
			*(res++) = s1[i++];
	res -= ft_strclen(s1, '\0');
	while (*s2)
		res[i++] = *(s2++);
	res[i] = '\0';
	if (s1)
		free(s1);
	return (res);
}