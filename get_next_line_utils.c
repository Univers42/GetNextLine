#include "get_next_line.h"
    void ft_bzero(void *s, size_t n)
{
    char *ptr;

    ptr = (char *)s;
    while (n > 0)
    {
        *ptr = '\0';
        ptr++;
        n--;
    }
}

void *ft_calloc(size_t count, size_t size)
{
    void *ptr;

    ptr = malloc(count * size);
    if (!ptr)
        return (NULL);
    ft_bzero(ptr, count * size);
    return (ptr);
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


char *ft_strdup(const char *src)
{
    char *str;
    size_t len;

    len = 0;
    while (src[len])
        len++;
    str = malloc(len + 1);
    if (!str)
        return (NULL);
    while (*src)
        *str++ = *src++;
    *str = '\0';
    return (str - len);
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

void *ft_memcpy(void *dst, const void *src, size_t n)
{
    unsigned char *d;
    const unsigned char *s;
    
    if (!dst && !src)
        return (NULL);
    if (!n)
        return (dst);
        
    d = (unsigned char *)dst;
    s = (const unsigned char *)src;
    
    while (n-- > 0)
        *d++ = *s++;
        
    return (dst);
}

size_t ft_strlen(char *str)
{
    int i;

    i = 0;
    while(str[i])
        i++;
    return i;
}