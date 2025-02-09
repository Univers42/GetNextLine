#include "get_next_line.h"
static void ft_bzero(void *s, size_t n) {
    unsigned char *ptr = s;
    while (n--) {
        *ptr++ = 0;
    }
}

void *ft_calloc(size_t count, size_t size) {
    size_t total_size = count * size;
    void *ptr = malloc(total_size);
    if (!ptr)
        return NULL; // Return NULL if malloc fails
    ft_bzero(ptr, total_size); // Zero out allocated memory
    return ptr;
}

void *ft_memmove(void *dest, const void *src, size_t n) {
    unsigned char *d = (unsigned char *)dest;
    const unsigned char *s = (const unsigned char *)src;
    if (!dest && !src)
        return NULL; // Handle NULL pointers safely
    if (d < s) { 
        // Forward copy (safe when no overlap or dest is before src)
        while (n--)
            *d++ = *s++;
    } else if (d > s) { 
        // Backward copy (safe when overlapping)
        d += n;
        s += n;
        while (n--)
            *--d = *--s;
    }

    return dest;
}


char *ft_strndup(const char *s, size_t n) {
    size_t len = 0;
    
    // Find the length of the string (or limit to `n`)
    while (s[len] && len < n) {
        len++;
    }

    // Allocate memory for the new string (+1 for null-terminator)
    char *new_str = malloc(len + 1);
    if (!new_str) {
        return NULL;  // Return NULL if memory allocation fails
    }

    // Copy the first `len` characters into the new string
    for (size_t i = 0; i < len; i++) {
        new_str[i] = s[i];
    }

    new_str[len] = '\0';  // Null-terminate the new string
    return new_str;
}

char *ft_strchr(const char *s, int c) {
    while (*s) {
        if (*s == (char)c) {
            return (char *)s; // Return pointer to found character
        }
        s++;
    }
    // If 'c' is '\0', return a pointer to its position in the string
    return (c == '\0') ? (char *)s : NULL;
}


size_t ft_strlen(char *str)
{
    int i;

    i = 0;
    while(*str)
        i++;
    return (i);
}



char	*ft_substr(char *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		return (malloc(1));
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	str = malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = 0;
	return (str);
}



void	fill_str(char *res, char *s1, char *s2)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	while (s1[j])
		res[i++] = s1[j++];
	j = 0;
	while (s2[j])
		res[i++] = s2[j++];
	res[i] = '\0';
}

char	*ft_strjoin(char *s1, char *s2)
{
	char			*res;

	res = (char *) malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!res)
		return (NULL);
	fill_str(res, s1, s2);
	return (res);
}


char	*ft_strdup(char *s1)
{
	char			*dest;
	unsigned int	i;

	dest = (char *) malloc(ft_strlen(s1) + 1);
	if (!dest)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}