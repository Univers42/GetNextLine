#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../get_next_line_bonus.h"
#include "test_utils.h"

#define NUM_FILES 48

/**
 * 
 * The files cannot be opened by the opener function, so I have to focus on that tomorrow.
 */
void test_multiple_fds()
{
    int fds[NUM_FILES];
    const char *filenames[NUM_FILES] = {
        "test_cases/empty.txt", "test_cases/one_line.txt", "test_cases/multi_lines.txt",
        "test_cases/no_newline.txt", "test_cases/big_file.txt", "test_cases/1char.txt",
        "test_cases/41_no_nl", "test_cases/41_no_nl copy 2", "test_cases/41_with_nl",
        "test_cases/42_no_nl", "test_cases/42_with_nl", "test_cases/43_no_nl",
        "test_cases/43_with_nl", "test_cases/big_line_with_nl", "test_cases/empty.txt",
        "test_cases/empty.txt", "test_cases/giant_line.txt", "test_cases/lines_around_10.txt",
        "test_cases/multi_lines.txt", "test_cases/multiple_line_no_nl", "test_cases/multiple_line_with_nl",
        "test_cases/multiple_nl.txt", "test_cases/multiple_nlx5", "test_cases/nl",
        "test_cases/no_newline.txt", "test_cases/one_line_no_nl.txt", "test_cases/one_line.txt",
        "test_cases/only_nl.txt", "test_cases/variable_nls.txt", "test_cases/1-brouette.txt",
        "test_cases/2-otarie.txt", "test_cases/3-oneline.txt", "test_cases/4-u.txt",
        "test_cases/5-empty.txt", "test_cases/6-newline.txt", "test_cases/7-onechar.txt",
        "test_cases/8-twochar.txt", "test_cases/9-linew.txt", "test_cases/10-b.txt",
        "test_cases/11-bg.txt", "test_cases/12-bigben.txt"
    };

    const char *expected_outputs[NUM_FILES] = {
        "expected_output/empty.txt", "expected_output/one_line.txt", "expected_output/multi_lines.txt",
        "expected_output/no_newline.txt", "expected_output/big_file.txt", "expected_output/1char.txt",
        "expected_output/41_no_nl", "expected_output/41_no_nl copy 2", "expected_output/41_with_nl",
        "expected_output/42_no_nl", "expected_output/42_with_nl", "expected_output/43_no_nl",
        "expected_output/43_with_nl", "expected_output/big_line_with_nl", "expected_output/empty.txt",
        "expected_output/empty.txt", "expected_output/giant_line.txt", "expected_output/lines_around_10.txt",
        "expected_output/multi_lines.txt", "expected_output/multiple_line_no_nl", "expected_output/multiple_line_with_nl",
        "expected_output/multiple_nl.txt", "expected_output/multiple_nlx5", "expected_output/nl",
        "expected_output/no_newline.txt", "expected_output/one_line_no_nl.txt", "expected_output/one_line.txt",
        "expected_output/only_nl.txt", "expected_output/variable_nls.txt", "expected_output/1-brouette.txt",
        "expected_output/2-otarie.txt", "expected_output/3-oneline.txt", "expected_output/4-u.txt",
        "expected_output/5-empty.txt", "expected_output/6-newline.txt", "expected_output/7-onechar.txt",
        "expected_output/8-twochar.txt", "expected_output/9-linew.txt", "expected_output/10-b.txt",
        "expected_output/11-bg.txt", "expected_output/12-bigben.txt"
    };

    // Open all test files
    for (int i = 0; i < NUM_FILES; i++)
    {
        fds[i] = open(filenames[i], O_RDONLY);
        if (fds[i] == -1)
        {
            printf("❌ Error opening file: %s\n", filenames[i]);
            return;
        }
    }

    printf("\n🔄 Testing Multiple File Descriptors:\n");
    int active_fds = NUM_FILES;
    char *line;
    int line_number[NUM_FILES] = {0};  // Track line index for each FD

    // Read from all FDs in a round-robin fashion
    while (active_fds > 0)
    {
        for (int i = 0; i < NUM_FILES; i++)
        {
            if (fds[i] == -1) continue;

            line = get_next_line_bonus(fds[i]);
            if (line)
            {
                printf("FD %d: %s\n", fds[i], line);

                // Write the output to a temporary file
                char temp_output_file[256];
                snprintf(temp_output_file, sizeof(temp_output_file), "outputs/temp_output_%d.txt", fds[i]);
                FILE *output = fopen(temp_output_file, "w");
                if (!output) {
                    printf("❌ Error opening output file\n");
                    free(line);
                    return;
                }
                fprintf(output, "%s", line);
                fclose(output);

                // Compare with expected output
                if (!compare_files(temp_output_file, expected_outputs[i]))
                {
                    printf("❌ MISMATCH on FD %d! Expected: [%s], Got: [%s]\n",
                           fds[i], expected_outputs[i], line);
                }
                else
                {
                    printf("✅ FD %d Line %d is correct\n", fds[i], line_number[i] + 1);
                }

                free(line);
                line_number[i]++;
            }
            else
            {
                close(fds[i]);
                fds[i] = -1;
                active_fds--;
            }
        }
    }

    printf("✅ Multi-FD test completed.\n");
}

int main(void)
{
    test_multiple_fds();
    return 0;
}