#include <stdlib.h> 

static char *str_dup(char *s)
{
    int len = 0;
    char *new_str;
    while (s[len])
        len++;
    new_str = malloc(len + 1);
    if (!new_str)
        return (NULL);
    for (int i = 0; i < len; i++)
        new_str[i] = s[i];

    new_str[len] = '\0';

    return (new_str);
}


static int find_newline(char *str)
{
    int i = 0;
    if (!str)
        return -1;
    while (str[i])
    {
        if (str[i] == '\n')
            return i;
        i++;
    }
    return -1;
}


static char *str_join(char *s1, char *s2, int len_s2)
{
    int len_s1 = 0;
    char *new_str;
    if (s1)
    {
        while (s1[len_s1])
            len_s1++;
    }
    new_str = malloc(len_s1 + len_s2 + 1);
    if (!new_str)
        return (NULL);
    int i = 0;
    for (; i < len_s1; i++)
        new_str[i] = s1[i];
    for (int j = 0; j < len_s2; j++, i++)
        new_str[i] = s2[j];
    new_str[i] = '\0';
    free(s1);

    return (new_str);
}
