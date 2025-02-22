#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include "../get_next_line.h"
#include "test_utils.h"



void display_success_message() {
    printf("\033[1;32m"); // Set text color to green
    printf("\n");
    printf("     ✨ All Tests Passed! ✨\n");
    printf("\n");
    printf("         .-=========-.       \n");
    printf("         \\'-=======-'/       \n");
    printf("         _|   .=.   |_       \n");
    printf("        ((|  {{1}}  |))      \n");
    printf("         \\|   /|\\   |/       \n");
    printf("          \\__ '`' __/        \n");
    printf("            _`) (`_          \n");
    printf("          _/_______\\_        \n");
    printf("         /___________\\       \n");
    printf("\n");
    printf("    🎉 Success Trophy 🎉     \n");
    printf("\n");
    printf("\033[0m"); // Reset text color
}

void test_file(const char *filename, const char *expected_output_file, bool *all_tests_passed)
{
    int fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        *all_tests_passed = false;
        return;
    }

    FILE *output = fopen("outputs/temp_output.txt", "w");
    if (!output) {
        close(fd);
        *all_tests_passed = false;
        return;
    }

    char *line;
    while ((line = get_next_line(fd)) != NULL)
    {
        fprintf(output, "%s", line); // Remove the extra newline character
        free(line);
    }

    fclose(output);
    close(fd);

    if (!compare_files("outputs/temp_output.txt", expected_output_file)) {
        *all_tests_passed = false;
    }
}

void run_tests_with_buffer_size(size_t buffer_size, bool *all_tests_passed)
{
    const char *test_files[][2] = {
        {"test_cases/empty.txt", "expected_output/empty.txt"},
        FILE *expected = fopen(expected_output_file, "r");
        if (expected) {
            char ch;
            while ((ch = getc(expected)) != EOF) {
                putchar(ch);
            }
            fclose(expected);
        }
        printf("\nActual output:\n");
        FILE *actual = fopen("outputs/temp_output.txt", "r");
        if (actual) {
            char ch;
            while ((ch = getc(actual)) != EOF) {
                putchar(ch);
            }
            fclose(actual);
        }
        printf("\n");
        *all_tests_passed = false;
    }
}

void run_tests_with_buffer_size(size_t buffer_size, bool *all_tests_passed)
{
    printf("\nRunning tests with BUFFER_SIZE = %zu\n", buffer_size);
    const char *test_files[][2] = {
        {"test_cases/empty.txt", "expected_output/empty.txt"},
        {"test_cases/one_line.txt", "expected_output/one_line.txt"},
        {"test_cases/multi_lines.txt", "expected_output/multi_lines.txt"},
        {"test_cases/no_newline.txt", "expected_output/no_newline.txt"},
        {"test_cases/big_file.txt", "expected_output/big_file.txt"},
        {"test_cases/1char.txt", "expected_output/1char.txt"},
        {"test_cases/41_no_nl", "expected_output/41_no_nl"},
        {"test_cases/41_no_nl copy 2", "expected_output/41_no_nl copy 2"},
        //{"test_cases/41_no_nl copy3", "expected_output/41_no_nl copy3"},
        {"test_cases/41_with_nl", "expected_output/41_with_nl"},
        {"test_cases/42_no_nl", "expected_output/42_no_nl"},
        {"test_cases/42_with_nl", "expected_output/42_with_nl"},
        {"test_cases/43_no_nl", "expected_output/43_no_nl"},
        //{"test_cases/43_no_nl_copy", "expected_output/43_no_nl_copy"},
        {"test_cases/43_with_nl", "expected_output/43_with_nl"},
        //{"test_cases/alternate_line_nl_no_nl", "expected_output/alternate_line_nl_no_nl"},
        //{"test_cases/alternate_line_with_nl", "expected_output/alternate_line_with_nl"},
        //{"test_cases/big_line_no_nl.txt", "expected_output/big_line_no_nl.txt"},
        {"test_cases/big_line_with_nl", "expected_output/big_line_with_nl"},
        {"test_cases/empty.txt", "expected_output/empty.txt"},
        {"test_cases/empty.txt", "expected_output/empty.txt"},
        {"test_cases/giant_line.txt", "expected_output/giant_line.txt"},
        {"test_cases/lines_around_10.txt", "expected_output/lines_around_10.txt"},
        {"test_cases/multi_lines.txt", "expected_output/multi_lines.txt"},
        {"test_cases/multiple_line_no_nl", "expected_output/multiple_line_no_nl"},
        {"test_cases/multiple_line_with_nl", "expected_output/multiple_line_with_nl"},
        {"test_cases/multiple_nl.txt", "expected_output/multiple_nl.txt"},
        {"test_cases/multiple_nlx5", "expected_output/multiple_nlx5"},
        {"test_cases/nl", "expected_output/nl"},
        {"test_cases/no_newline.txt", "expected_output/no_newline.txt"},
        {"test_cases/one_line_no_nl.txt", "expected_output/one_line_no_nl.txt"},
        {"test_cases/one_line.txt", "expected_output/one_line.txt"},
        {"test_cases/only_nl.txt", "expected_output/only_nl.txt"},
        {"test_cases/variable_nls.txt", "expected_output/variable_nls.txt"},
        {"test_cases/1-brouette.txt", "expected_output/1-brouette.txt"},
        {"test_cases/2-otarie.txt", "expected_output/2-otarie.txt"},
        {"test_cases/3-oneline.txt", "expected_output/3-oneline.txt"},
        {"test_cases/4-u.txt", "expected_output/4-u.txt"},
        {"test_cases/5-empty.txt", "expected_output/5-empty.txt"},
        {"test_cases/6-newline.txt", "expected_output/6-newline.txt"},
        {"test_cases/7-onechar.txt", "expected_output/7-onechar.txt"},
        {"test_cases/8-twochar.txt", "expected_output/8-twochar.txt"},
        {"test_cases/9-linew.txt", "expected_output/9-linew.txt"},
        {"test_cases/10-b.txt", "expected_output/10-b.txt"},
        {"test_cases/11-bg.txt", "expected_output/11-bg.txt"},
        {"test_cases/12-bigben.txt", "expected_output/12-bigben.txt"},
    };

    size_t num_tests = sizeof(test_files) / sizeof(test_files[0]);

    for (size_t i = 0; i < num_tests; i++) {
        test_file(test_files[i][0], test_files[i][1], all_tests_passed);
    }
}

int main(void)
{
    display_start_message();

    size_t buffer_sizes[] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288, 1048576};

    size_t num_buffer_sizes = sizeof(buffer_sizes) / sizeof(buffer_sizes[0]);

    bool all_tests_passed = true;

    for (size_t i = 0; i < num_buffer_sizes; i++) {
        run_tests_with_buffer_size(buffer_sizes[i], &all_tests_passed);
    }

    if (all_tests_passed) {
        display_success_message();
    }

    return 0;
}
