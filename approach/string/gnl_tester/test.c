#include "test_utils.h"
#include "get_next_line.h" // Ensure this header is available and includes the declaration of get_next_line
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <stdbool.h>

extern bool is_initializing;

int compare_output(const char *expected, const char *actual) {
    if (expected == NULL || actual == NULL) {
        return (expected == actual) ? 0 : -1;
    }
    return strcmp(expected, actual);
}

void run_test(int fd, const char *expected) {
    TEST_START();
    TEST_GNL(fd, expected);
}

int main(void) {
    is_initializing = false;
    signal(SIGSEGV, SIG_DFL); // Replace with appropriate signal handler if needed

    int fd;

    printf("[BUFFER_SIZE = %d]:\n", BUFFER_SIZE);

    printf("Invalid fd:\n");
    fd = open("files/empty", O_RDWR);
    run_test(1000, NULL);
    run_test(-1, NULL);
    close(fd);
    run_test(fd, NULL);

    printf("files/empty:\n");
    fd = open("files/empty", O_RDWR);
    run_test(fd, NULL);
    run_test(fd, NULL);
    close(fd);

    printf("files/nl:\n");
    fd = open("files/nl", O_RDWR);
    run_test(fd, "\n");
    run_test(fd, NULL);
    close(fd);

    printf("files/41_no_nl:\n");
    fd = open("files/41_no_nl", O_RDWR);
    run_test(fd, "01234567890123456789012345678901234567890");
    run_test(fd, NULL);
    close(fd);

    printf("files/41_with_nl:\n");
    fd = open("files/41_with_nl", O_RDWR);
    run_test(fd, "0123456789012345678901234567890123456789\n");
    run_test(fd, "0");
    run_test(fd, NULL);
    close(fd);

    printf("files/42_no_nl:\n");
    fd = open("files/42_no_nl", O_RDWR);
    run_test(fd, "012345678901234567890123456789012345678901");
    run_test(fd, NULL);
    close(fd);

    printf("files/42_with_nl:\n");
    fd = open("files/42_with_nl", O_RDWR);
    run_test(fd, "01234567890123456789012345678901234567890\n");
    if (BUFFER_SIZE == 42) {
        char c = 0;
        read(fd, &c, 1);
        if (c == '1') {
            printf("✅ Test passed: character matches expected output\n");
        } else {
            printf("❌ Test failed: character does not match expected output\n");
        }
        run_test(fd, NULL);
    } else {
        run_test(fd, "1");
        run_test(fd, NULL);
    }
    close(fd);

    printf("files/43_no_nl:\n");
    fd = open("files/43_no_nl", O_RDWR);
    run_test(fd, "0123456789012345678901234567890123456789012");
    run_test(fd, NULL);
    close(fd);

    printf("files/43_with_nl:\n");
    fd = open("files/43_with_nl", O_RDWR);
    run_test(fd, "012345678901234567890123456789012345678901\n");
    run_test(fd, "2");
    run_test(fd, NULL);
    close(fd);

    printf("files/multiple_nlx5:\n");
    fd = open("files/multiple_nlx5", O_RDWR);
    run_test(fd, "\n");
    run_test(fd, "\n");
    run_test(fd, "\n");
    run_test(fd, "\n");
    run_test(fd, "\n");
    run_test(fd, NULL);
    close(fd);

    printf("files/multiple_line_no_nl:\n");
    fd = open("files/multiple_line_no_nl", O_RDWR);
    run_test(fd, "01234567890123456789012345678901234567890\n");
    run_test(fd, "987654321098765432109876543210987654321098\n");
    run_test(fd, "0123456789012345678901234567890123456789012\n");
    run_test(fd, "987654321098765432109876543210987654321098\n");
    run_test(fd, "01234567890123456789012345678901234567890");
    run_test(fd, NULL);
    close(fd);

    printf("files/multiple_line_with_nl:\n");
    fd = open("files/multiple_line_with_nl", O_RDWR);
    run_test(fd, "9876543210987654321098765432109876543210\n");
    run_test(fd, "01234567890123456789012345678901234567890\n");
    run_test(fd, "987654321098765432109876543210987654321098\n");
    run_test(fd, "01234567890123456789012345678901234567890\n");
    run_test(fd, "9876543210987654321098765432109876543210\n");
    run_test(fd, NULL);
    close(fd);

    printf("files/alternate_line_nl_no_nl:\n");
    fd = open("files/alternate_line_nl_no_nl", O_RDWR);
    run_test(fd, "98765432109876543210987654321098765432109\n");
    run_test(fd, "\n");
    run_test(fd, "012345678901234567890123456789012345678901\n");
    run_test(fd, "\n");
    run_test(fd, "9876543210987654321098765432109876543210987\n");
    run_test(fd, "\n");
    run_test(fd, "012345678901234567890123456789012345678901\n");
    run_test(fd, "\n");
    run_test(fd, "98765432109876543210987654321098765432109");
    run_test(fd, NULL);
    close(fd);

    printf("files/alternate_line_nl_with_nl:\n");
    fd = open("files/alternate_line_nl_with_nl", O_RDWR);
    run_test(fd, "01234567890123456789012345678901234567890\n");
    run_test(fd, "\n");
    run_test(fd, "987654321098765432109876543210987654321090\n");
    run_test(fd, "\n");
    run_test(fd, "0123456789012345678901234567890123456789012\n");
    run_test(fd, "\n");
    run_test(fd, "987654321098765432109876543210987654321090\n");
    run_test(fd, "\n");
    run_test(fd, "01234567890123456789012345678901234567890\n");
    run_test(fd, NULL);
    close(fd);

    return 0;
}
