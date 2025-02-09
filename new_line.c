#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 1024  // Preallocated read buffer size



//char *ft_strcpy(char *dest, char *buf)
//{
//    char *cpy;
//
//    cpy = dest;
//    while(*buf)
//        *dest++ = *buf++;
//    *dest = '\0';
//    return(cpy);
//}
ssize_t fill_buffer(int fd, char *dest, size_t max_len)
{
    static char buffer[BUFFER_SIZE];  // Persistent read buffer
    static size_t buf_pos = 0;        // Position in buffer
    static size_t buf_len = 0;        // Data length in buffer
    size_t dest_pos = 0;              // Position in destination buffer
    
    if (!dest || max_len == 0) return -1;  // Error handling

    while (dest_pos < max_len - 1) {
        // Read new data only if buffer is empty
        if (buf_pos >= buf_len) {
            buf_len = read(fd, buffer, BUFFER_SIZE);
            buf_pos = 0;

            if (buf_len <= 0) return buf_len; // EOF or error
        }

        // Copy characters to destination buffer until '\n' is found
        while (buf_pos < buf_len && dest_pos < max_len - 1) {
            char c = buffer[buf_pos++];
            dest[dest_pos++] = c;

            if (c == '\n') {
                dest[dest_pos] = '\0'; // Null-terminate string
                return dest_pos;       // Return bytes copied
            }
        }
    }
    dest[dest_pos] = '\0';  // Ensure null termination
    return dest_pos;         // Return bytes copied
}

int main() {
    int fd = open("to_fille_buff.txt", O_RDONLY);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    char line[256]; // Allocate space for one line
    while (fill_buffer(fd, line, sizeof(line)) > 0) {
        printf("Read line: %s", line);
    }

    close(fd);
    return 0;
}
