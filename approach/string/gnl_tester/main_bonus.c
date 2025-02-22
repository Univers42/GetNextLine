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

    const char *filenames[NUM_FILES] = {
        "test_cases/empty", "test_cases/one_line.txt", "test_cases/multi_lines.txt",
        "test_cases/no_newline.txt", "test_cases/big_file.txt", "test_cases/1char.txt",
        "test_cases/41_no_nl", "test_cases/41_with_nl", "test_cases/42_no_nl",
        "test_cases/42_with_nl", "test_cases/43_with_nl", "test_cases/big_line_with_nl",
        "test_cases/giant_line.txt", "test_cases/lines_around_10.txt", "test_cases/multi_lines.txt",
        "test_cases/multiple_line_with_nl", "test_cases/multiple_nl.txt", "test_cases/multiple_nlx5",
        "test_cases/nl", "test_cases/no_newline.txt", "test_cases/one_line_no_nl.txt",
        "test_cases/one_line.txt", "test_cases/only_nl.txt", "test_cases/variable_nls.txt",
        "test_cases/1-brouette.txt", "test_cases/2-otarie.txt", "test_cases/3-oneline.txt",
        "test_cases/4-u.txt", "test_cases/5-empty.txt", "test_cases/6-newline.txt",
        "test_cases/7-onechar.txt", "test_cases/8-twochar.txt", "test_cases/9-linew.txt",
        "test_cases/10-b.txt", "test_cases/11-bg.txt", "test_cases/12-bigben.txt"
    };

    const char *expected_outputs[NUM_FILES] = {
        "expected_output/empty", "expected_output/one_line.txt", "expected_output/multi_lines.txt",
        "expected_output/no_newline.txt", "expected_output/big_file.txt", "expected_output/1char.txt",
        "expected_output/41_no_nl", "expected_output/41_with_nl", "expected_output/42_no_nl",
        "expected_output/42_with_nl", "expected_output/43_with_nl", "expected_output/big_line_with_nl",
        "expected_output/giant_line.txt", "expected_output/lines_around_10.txt", "expected_output/multi_lines.txt",
        "expected_output/multiple_line_with_nl", "expected_output/multiple_nl.txt", "expected_output/multiple_nlx5",
        "expected_output/nl", "expected_output/no_newline.txt", "expected_output/one_line_no_nl.txt",
        "expected_output/one_line.txt", "expected_output/only_nl.txt", "expected_output/variable_nls.txt",
        "expected_output/1-brouette.txt", "expected_output/2-otarie.txt", "expected_output/3-oneline.txt",
        "expected_output/4-u.txt", "expected_output/5-empty.txt", "expected_output/6-newline.txt",
        "expected_output/7-onechar.txt", "expected_output/8-twochar.txt", "expected_output/9-linew.txt",
        "expected_output/10-b.txt", "expected_output/11-bg.txt", "expected_output/12-bigben.txt"
    };

    // Open all test files
    printf("%s>>> Opening files...%s\n", YELLOW, RESET);
    int successfully_opened = 0;
    for (int i = 0; i < NUM_FILES; i++)
    {
        fds[i] = open(filenames[i], O_RDONLY);
        if (fds[i] == -1)
            printf("%s❌ Failed to open: %s%s\n", RED, filenames[i], RESET);
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
    //  
    printf("\n%s>>> Running tests...%s\n", YELLOW, RESET);
    int active_fds = successfully_opened;
    char *line;
    FILE *expected_files[NUM_FILES];

    //iterates through all the files and opens the expected output files
    for (int i = 0; i < NUM_FILES; i++) {
        if (fds[i] != -1)
        {
            expected_files[i] = fopen(expected_outputs[i], "r");
            if (!expected_files[i])
            {
                printf("%s❌ Error: Could not open expected output file: %s%s\n", RED, expected_outputs[i], RESET);
                close(fds[i]);
                fds[i] = -1;
                active_fds--;
            }
        }
    }

    // Read from all FDs in a round-robin fashion
    while (active_fds > 0)
    {
        //iterates through all the files and read the lines
        for (int i = 0; i < NUM_FILES; i++)
        {
            if (fds[i] == -1) continue;

            line = get_next_line_bonus(fds[i]);
            if (line)
            {
                char expected_line[BUFFER_SIZE] = {0};
                if (fgets(expected_line, sizeof(expected_line), expected_files[i]))
                {
                    expected_line[strcspn(expected_line, "\n")] = '\0';
                    line[strcspn(line, "\n")] = '\0';

                    if (strcmp(line, expected_line) == 0)
                    {
                        printf("%s✅ Match: %s%s\n", GREEN, filenames[i], RESET);
                        passed_tests++;
                    }
                    else
                    {
                        printf("%s❌ Mismatch: %s%s\n", RED, filenames[i], RESET);
                        printf("Expected: %s\nGot: %s\n", expected_line, line);
                        failed_tests++;
                    }
                }
                free(line);
                total_tests++;
            }
            else
            {
                close(fds[i]);
                fds[i] = -1;
                fclose(expected_files[i]);
                active_fds--;
            }
        }
    }

    // Compare the output files with the expected files
    for (int i = 0; i < NUM_FILES; i++)
    {
        if (fds[i] != -1)
        {
            char command[BUFFER_SIZE];
            snprintf(command, sizeof(command), "diff -q %s %s", filenames[i], expected_outputs[i]);
            int result = system(command);
            if (result == 0)
            {
                printf("%s✅ Files match: %s and %s%s\n", GREEN, filenames[i], expected_outputs[i], RESET);
            }
            else
            {
                printf("%s❌ Files differ: %s and %s%s\n", RED, filenames[i], expected_outputs[i], RESET);
            }
        }
    }

    // Print final statistics
    printf("\n%s=== Test Summary ===%s\n", YELLOW, RESET);
    printf("Total tests run: %d\n", total_tests);
    printf("%sTests passed  : %d%s\n", GREEN, passed_tests, RESET);
    printf("%sTests failed  : %d%s\n", RED, failed_tests, RESET);
    printf("Success rate  : %.2f%%\n", (total_tests > 0) ? ((float)passed_tests / total_tests * 100) : 0);
}

int main()
{
    test_multiple_fds();
    return (0);
}
