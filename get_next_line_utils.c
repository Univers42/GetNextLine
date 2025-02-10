#include "get_next_line.h"

size_t ft_strlen(char *s)
{
    size_t i = 0;
    while (s && s[i])
        i++;
    return i;
}

char *ft_strchr(char *s, int c)
{
    if (!s)
        return NULL;
    while (*s)
    {
        if (*s == (char)c)
            return (char *)s;
        s++;
    }
    return NULL;
}

char *ft_strdup(char *s)
{
    size_t len = ft_strlen(s);
    char *dup = (char *)malloc(len + 1);
    if (!dup)
        return NULL;
    for (size_t i = 0; i < len; i++)
        dup[i] = s[i];
    dup[len] = '\0';
    return dup;
}

char *ft_strjoin(char *s1, char *s2)
{
    size_t len1 = ft_strlen(s1);
    size_t len2 = ft_strlen(s2);
    char *joined = (char *)malloc(len1 + len2 + 1);
    if (!joined)
        return NULL;
    for (size_t i = 0; i < len1; i++)
        joined[i] = s1[i];
    for (size_t j = 0; j < len2; j++)
        joined[len1 + j] = s2[j];
    joined[len1 + len2] = '\0';
    free(s1);  // Free the previous storage to avoid memory leaks
    return joined;
}
