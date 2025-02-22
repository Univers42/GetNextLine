#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../get_next_line_bonus.h"
#include "test_utils.h"

#define NUM_FILES 36
#define GREEN "\033[0;32m"
#define RED "\033[0;31m"
#define YELLOW "\033[0;33m"
#define RESET "\033[0m"

void test_multiple_fds()
{
    int fds[NUM_FILES];
    int total_tests = 0;
    int passed_tests = 0;
    int failed_tests = 0;

    printf("\n%s=== GET_NEXT_LINE BONUS TESTER ===%s\n", YELLOW, RESET);
    printf("Testing %d different files simultaneously\n\n", NUM_FILES);

    // [Previous file arrays remain the same]
    const char *filenames[NUM_FILES] = {
        "test_cases/empty", "test_cases/one_line.txt", "test_cases/multi_lines.txt",
        "test_cases/no_newline.txt",
        "test_cases/big_file.txt",
        "test_cases/1char.txt",
        "test_cases/41_no_nl",
        "test_cases/41_with_nl",
        "test_cases/42_no_nl",
        "test_cases/42_with_nl",
        "test_cases/43_with_nl",
        "test_cases/big_line_with_nl",
        "test_cases/giant_line.txt",
        "test_cases/lines_around_10.txt",
        "test_cases/multi_lines.txt",
        "test_cases/multiple_line_with_nl",
        "test_cases/multiple_nl.txt",
        "test_cases/multiple_nlx5",
        "test_cases/nl",
        "test_cases/no_newline.txt",
        "test_cases/one_line_no_nl.txt",
        "test_cases/one_line.txt",
        "test_cases/only_nl.txt",
        "test_cases/variable_nls.txt",
        "test_cases/1-brouette.txt",
        "test_cases/2-otarie.txt",
        "test_cases/3-oneline.txt",
        "test_cases/4-u.txt",
        "test_cases/5-empty.txt",
        "test_cases/6-newline.txt",
        "test_cases/7-onechar.txt",
        "test_cases/8-twochar.txt",
        "test_cases/9-linew.txt",
        "test_cases/10-b.txt",
        "test_cases/11-bg.txt",
        "test_cases/12-bigben.txt"
    };

    const char *expected_outputs[NUM_FILES] = {
        "expected_output/empty", "expected_output/one_line.txt", "expected_output/multi_lines.txt"
        "exptected_output/no_newline.txt",
        "exptected_output/big_file.txt",
        "exptected_output/1char.txt",
        "exptected_output/41_no_nl",
        "exptected_output/41_with_nl",
        "exptected_output/42_no_nl",
        "exptected_output/42_with_nl",
        "exptected_output/43_with_nl",
        "exptected_output/big_line_with_nl",
        "exptected_output/giant_line.txt",
        "expected_output/lines_around_10.txt",
        "exptected_output/multi_lines.txt",
        "exptected_output/multiple_line_with_nl",
        "exptected_output/multiple_nl.txt",
        "exptected_output/multiple_nlx5",
        "exptected_output/nl",
        "exptected_output/no_newline.txt",
        "exptected_output/one_line_no_nl.txt",
        "exptected_output/one_line.txt",
        "exptected_output/only_nl.txt",
        "exptected_output/variable_nls.txt",
        "exptected_output/1-brouette.txt",
        "exptected_output/2-otarie.txt",
        "exptected_output/3-oneline.txt",
        "exptected_output/4-u.txt",
        "exptected_output/5-empty.txt",
        "exptected_output/6-newline.txt",
        "exptected_output/7-onechar.txt",
        "exptected_output/8-twochar.txt",
        "exptected_output/9-linew.txt",
        "exptected_output/10-b.txt",
        "exptected_output/11-bg.txt",
        "exptected_output/12-bigben.txt"
    };

    // Open all test files and count successful opens
    printf("%s>>> Opening files...%s\n", YELLOW, RESET);
    int successfully_opened = 0;
    for (int i = 0; i < NUM_FILES; i++)
    {
        fds[i] = open(filenames[i], O_RDONLY);
        if (fds[i] == -1)
        {
            printf("%s❌ Failed to open: %s%s\n", RED, filenames[i], RESET);
        }
        else
        {
            successfully_opened++;
            printf("%s✓ Opened: %s%s\n", GREEN, filenames[i], RESET);
        }
    }

    if (successfully_opened == 0)
    {
        printf("%s❌ No files could be opened. Aborting tests.%s\n", RED, RESET);
        return;
    }

    printf("\n%s>>> Starting tests with %d files...%s\n", YELLOW, successfully_opened, RESET);
    int active_fds = successfully_opened;
    char *line;
    int line_number[NUM_FILES] = {0};

    // Read from all FDs in a round-robin fashion
    while (active_fds > 0)
    {
        for (int i = 0; i < NUM_FILES; i++)
        {
            if (fds[i] == -1) continue;

            line = get_next_line_bonus(fds[i]);
            total_tests++;

            if (line)
            {
                printf("\n%s=== Testing FD %d (File: %s) ===%s\n", YELLOW, fds[i], filenames[i], RESET);
                printf("Line content: %s", line);

                // Compare with expected output
                char temp_output_file[256];
                snprintf(temp_output_file, sizeof(temp_output_file), "outputs/temp_output_%d.txt", fds[i]);
                FILE *output = fopen(temp_output_file, "w");
                if (!output) {
                    printf("%s❌ Error: Could not create temporary output file%s\n", RED, RESET);
                    free(line);
                    continue;
                }
                fprintf(output, "%s", line);
                fclose(output);

                if (!compare_files(temp_output_file, expected_outputs[i]))
                {
                    printf("%s❌ MISMATCH on FD %d, Line %d%s\n", RED, fds[i], line_number[i] + 1, RESET);
                    printf("Expected: %s\n", expected_outputs[i]);
                    printf("Got     : %s\n", line);
                    failed_tests++;
                }
                else
                {
                    printf("%s✅ Line %d is correct%s\n", GREEN, line_number[i] + 1, RESET);
                    passed_tests++;
                }

                free(line);
                line_number[i]++;
            }
            else
            {
                printf("%s📁 Finished reading file: %s%s\n", YELLOW, filenames[i], RESET);
                close(fds[i]);
                fds[i] = -1;
                active_fds--;
            }
        }
    }

    // Print final statistics
    printf("\n%s=== Test Summary ===%s\n", YELLOW, RESET);
    printf("Total tests run: %d\n", total_tests);
    printf("%sTests passed  : %d%s\n", GREEN, passed_tests, RESET);
    printf("%sTests failed  : %d%s\n", RED, failed_tests, RESET);
    printf("Success rate  : %.2f%%\n", (float)passed_tests / total_tests * 100);
}

int main(void)
{
    test_multiple_fds();
    return 0;
}
