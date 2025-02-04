#include "get_next_line.h"
#include <stdlib.h>

// ft_strlen: Returns the length of a string
size_t ft_strlen(const char *str)
{
    size_t len = 0;
    while (str[len])
        len++;
    return len;
}

// ft_strdup: Duplicates a string
char *ft_strdup(const char *s1)
{
    size_t len = ft_strlen(s1);
    char *copy = malloc(len + 1);  // +1 for the null terminator
    if (!copy)
        return NULL;
    for (size_t i = 0; i < len; i++)
        copy[i] = s1[i];
    copy[len] = '\0';  // Null-terminate the string
    return copy;
}

// ft_strchr: Locates the first occurrence of a character in a string
char *ft_strchr(const char *str, int c)
{
    while (*str)
    {
        if (*str == (char)c)
            return (char *)str;
        str++;
    }
    return (c == '\0') ? (char *)str : NULL;
}

// ft_strjoin: Concatenates two strings
char *ft_strjoin(char const *s1, char const *s2)
{
    size_t len1 = ft_strlen(s1);
    size_t len2 = ft_strlen(s2);
    char *result = malloc(len1 + len2 + 1);
    if (!result)
        return NULL;
    for (size_t i = 0; i < len1; i++)
        result[i] = s1[i];
    for (size_t i = 0; i < len2; i++)
        result[len1 + i] = s2[i];
    result[len1 + len2] = '\0';
    return result;
}


char *ft_substr(char const *s, unsigned int start, size_t len)
{
    if (!s)
        return NULL;
    size_t str_len = ft_strlen(s);
    if (start >= str_len)
        return ft_strdup("");
    if (len > str_len - start)
        len = str_len - start;
    char *substr = malloc(len + 1);
    if (!substr)
        return NULL;
    for (size_t i = 0; i < len; i++)
        substr[i] = s[start + i];
    substr[len] = '\0';
    return substr;
}

// ft_memcpy: Copies memory from one location to another
void *ft_memcpy(void *dest, const void *src, size_t n)
{
    unsigned char *d = dest;
    const unsigned char *s = src;
    while (n--)
        *d++ = *s++;
    return dest;
}
