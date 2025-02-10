#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "get_next_line.h"

#define TEST_CASES 5
#define BUFFER_SIZES {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024}
#define TEST_FILES {"test_empty.txt", "test_short.txt", "test_long.txt", "test_special.txt", "test_multi_fd1.txt", "test_multi_fd2.txt"}

void run_test(const char *filename, int buffer_size) {
    printf("\nTesting file: %s with BUFFER_SIZE=%d\n", filename, buffer_size);
    int fd = open(filename, O_RDONLY);
    if (fd < 0) {
        perror("Error opening file");
        return;
    }
    
    char *line;
    int line_count = 0;
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
        line_count++;
    }
    close(fd);
    printf("Total lines read: %d\n", line_count);
}

void test_multiple_fds() {
    printf("\nTesting multiple file descriptors...\n");
    int fd1 = open("test_multi_fd1.txt", O_RDONLY);
    int fd2 = open("test_multi_fd2.txt", O_RDONLY);
    if (fd1 < 0 || fd2 < 0) {
        perror("Error opening files");
        return;
    }
    char *line1, *line2;
    while ((line1 = get_next_line(fd1)) || (line2 = get_next_line(fd2))) {
        if (line1) {
            printf("FD1: %s", line1);
            free(line1);
        }
        if (line2) {
            printf("FD2: %s", line2);
            free(line2);
        }
    }
    close(fd1);
    close(fd2);
    printf("Multiple FD test completed.\n");
}

int main() {
    int buffer_sizes[] = BUFFER_SIZES;
    const char *test_files[] = TEST_FILES;
    
    for (int i = 0; i < sizeof(buffer_sizes) / sizeof(int); i++) {
        for (int j = 0; j < TEST_CASES; j++) {
            run_test(test_files[j], buffer_sizes[i]);
        }
    }
    
    test_multiple_fds();
    
    printf("\nMemory Leak Check:\n");
    system("valgrind --leak-check=full --show-leak-kinds=all ./gnl_tester");
    
    return 0;
}