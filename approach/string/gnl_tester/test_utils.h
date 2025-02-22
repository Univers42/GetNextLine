#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include <stdio.h>

// Basic test announcement
#define TEST_START() printf("\n🔄 %s\n", __func__)

// GNL test macro
#define TEST_GNL(fd, expected) do {                                             \
    char *line = get_next_line(fd);                                             \
    if (compare_output(expected, line) == 0) {                                  \
        printf("✅ Test passed: line matches expected output\n");               \
    } else {                                                                    \
        printf("❌ Test failed:\nExpected: %s\nGot: %s\n", expected, line);     \
    }                                                                           \
    free(line);                                                                 \
} while(0)

// Helper functions declaration
int compare_output(const char *expected, const char *actual);
void run_test(int fd, const char *expected);
int compare_files(const char *file1, const char *file2);

#endif
