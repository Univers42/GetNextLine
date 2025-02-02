#include "get_next_line.h"

char *get_next_line(int fd)
{
    static char *r;
    char *b, *l, *nr;
    int br;
    size_t i;

    if (fd < 0 || !(b = malloc(251)))
        return NULL;
    br = 1;
    while (br > 0)
    {
        if ((br = read(fd, b, 250)) < 0)
            return (free(b), NULL);
        *(b + br) = '\0';
        r = r ? ft_strjoin(r, b) : ft_strdup(b);
        i = 0;
        while (*(r + i) && *(r + i) != '\n')
            i++;
        if (*(r + i) == '\n')
            return (l = ft_substr(r, 0, i + 1), nr = ft_strdup(r + i + 1),
                    free(r), r = nr, free(b), l);
    }
    return (l = r ? ft_strdup(r) : NULL, free(r), r = NULL, free(b), l);
}
