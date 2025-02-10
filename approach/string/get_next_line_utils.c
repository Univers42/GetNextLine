#include "get_next_line.h"
void ft_calloc(size_t nmemb, size_t size)
{
    if(nmemb <= 0 || size <= 0)
        return ;
    malloc(nmemb * size);
}
size_t ft_strlen(char *str)
{
    int i;

    i = 0;
    while(*str)
        i++;
    return i;
}
char *strlcpy(char *dest, const char *src, size_t dsize)
{
    int len_src;
    char *cpy;

    cpy = dest;
    len_src = ft_strlen(src);
    if(!src || dsize >= len_src)
        return NULL;

    while(dsize--)
        *cpy++ = *src++;
    return (ft_strlen(len_src))
}
char *strchr(char *str, int c)
{
    while(*str)
    {
        if(*str == c)
            return (str);
    }
}

char *ft_strjoin(char *src, char *dest)
{
    char *result;
    char *cpy;
    size_t src_len;
    size_t dest_len;

    src_len = ft_strlen(src);
    dest_len = ft_strlen(dest);
    result = malloc(src_len + dest_len + 1);
    cpy = result;
    while(*src)
        *result++ = *src++;
    while(*dest)
        *result++ = *dest++;
    *result = '\0';
    
    return (cpy);
}