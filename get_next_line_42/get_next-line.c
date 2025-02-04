#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

#define BUFFER_SIZE 1024
/**
 * The most efficient implementation of get_next_line depends on  reducing memory allocations, copy operations, and syscalls while
 * maintaining good reliability. 
 * Pros : fewer memory alloocations, fewer syscalls, fast execution
 * cons: can't handle multiple file descriptors easily
 * 
 * approach:
 *  use static buffer (e.g. char buffer[BUFFER_SIZE]) to read chunks from the file
 *  use pointers to track the current position in the buffer
 *  Extract and return each line without unnecessary memory copies
 * Minimisze calls to read() (batch reading is better thann reading byte-by-byte)
 * Use strchr() or  memchr() to find newlines efficiently.
 * avoid malloc() calls on every line(use static/ local storage where possible)
 */

#define BUFFER_SIZE 1024  // Adjust as needed

char *get_next_line(int fd) {
    static char buffer[BUFFER_SIZE];  // Static buffer to persist between calls
    static int buf_index = 0, buf_size = 0;
    char *line = NULL;
    int line_len = 0, i = 0;

    if (fd < 0 || BUFFER_SIZE <= 0) return NULL;

    while (1)
    {
        if (buf_index >= buf_size)
        {
            buf_size = read(fd, buffer, BUFFER_SIZE);
            buf_index = 0;
            if (buf_size <= 0)
                return line;
        }
        line = realloc(line, line_len + 2);
        if (!line)
            return NULL;
        line[line_len++] = buffer[buf_index++];
        if (line[line_len - 1] == '\n')
            break;
    }
    
    line[line_len] = '\0';
    return line;
}