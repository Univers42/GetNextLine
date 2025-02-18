#include "get_next_line.h"

char *get_next_line(int fd) {
    static t_circular_list *list = NULL;
    static char buffer[BUFFER_SIZE];
    int bytes_read;
    char *line = malloc(1);
    int line_len = 0;

    if (!line) return NULL;
    line[0] = '\0';

    if (!list) {
        list = create_circular_list();
        if (!list) {
            free(line);
            return NULL;
        }
    }

    while ((bytes_read = read(fd, buffer, BUFFER_SIZE - 1)) > 0) {
        buffer[bytes_read] = '\0';

        char *chunk = strdup(buffer);
        if (!chunk) {
            free(line);
            return NULL;
        }
        append_to_circular_list(list, chunk);

        while (list->head != NULL) {
            char *data = dequeue_from_circular_list(list);

            for (int i = 0; data[i] != '\0'; i++) {
                line_len++;
                line = realloc(line, line_len + 1);
                if (!line) return NULL;

                line[line_len - 1] = data[i];
                line[line_len] = '\0';

                if (data[i] == '\n') {
                    free(data);
                    return line;
                }
            }
            free(data);
        }
    }

    if (bytes_read == 0 && line_len > 0) {
        return line;
    }

    free(line);
    return NULL;
}
