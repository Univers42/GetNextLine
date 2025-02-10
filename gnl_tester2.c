#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "get_next_line.h"

#define TEST_FILE "test.txt"
#define LARGE_FILE "large_test.txt"
#define MULTI_FD_COUNT 3
#define GREEN "\033[0;32m"
#define RED "\033[0;31m"
#define RESET "\033[0m"

// Utility function to create a test file
void create_test_file(const char *filename, const char *content) {
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        perror("Error creating test file");
        exit(1);
    }
    fprintf(fp, "%s", content);
    fclose(fp);
}

// Basic test
void test_basic() {
    printf("\nRunning Basic Test...\n");
    create_test_file(TEST_FILE, "Hello\nWorld\n42\n");

    int fd = open(TEST_FILE, O_RDONLY);
    if (fd < 0) { perror("open"); return; }

    char *line;
    line = get_next_line(fd);
    if (line && strcmp(line, "Hello\n") == 0)
        printf(GREEN "✅ Passed: Line 1\n" RESET);
    else
        printf(RED "❌ Failed: Line 1\n" RESET);
    free(line);

    line = get_next_line(fd);
    if (line && strcmp(line, "World\n") == 0)
        printf(GREEN "✅ Passed: Line 2\n" RESET);
    else
        printf(RED "❌ Failed: Line 2\n" RESET);
    free(line);

    line = get_next_line(fd);
    if (line && strcmp(line, "42\n") == 0)
        printf(GREEN "✅ Passed: Line 3\n" RESET);
    else
        printf(RED "❌ Failed: Line 3\n" RESET);
    free(line);

    close(fd);
}

// Test for multiple file descriptors
void test_multiple_fds() {
    printf("\nRunning Multi-FD Test...\n");
    create_test_file("file1.txt", "One\nTwo\nThree\n");
    create_test_file("file2.txt", "Alpha\nBeta\nGamma\n");

    int fd1 = open("file1.txt", O_RDONLY);
    int fd2 = open("file2.txt", O_RDONLY);
    if (fd1 < 0 || fd2 < 0) { perror("open"); return; }

    char *line1 = get_next_line(fd1);
    char *line2 = get_next_line(fd2);

    if (line1 && strcmp(line1, "One\n") == 0 && line2 && strcmp(line2, "Alpha\n") == 0)
        printf(GREEN "✅ Passed: Multi-FD Read\n" RESET);
    else
        printf(RED "❌ Failed: Multi-FD Read\n" RESET);
    
    free(line1);
    free(line2);
    close(fd1);
    close(fd2);
}

int main() {
    test_basic();
    test_multiple_fds();
    return 0;
}
