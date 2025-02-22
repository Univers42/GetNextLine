#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include "../get_next_line_bonus.h"
#include "test_utils.h"

#define NUM_FILES 3

void test_multiple_fds()
{
    int fds[NUM_FILES];
    char *filenames[NUM_FILES] = {
        "test_cases/file1.txt",
        "test_cases/file2.txt",
        "test_cases/file3.txt"
    };

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

    while (active_fds > 0)
    {
        for (int i = 0; i < NUM_FILES; i++)
        {
            if (fds[i] == -1) continue;

            line = get_next_line_bonus(fds[i]);
            if (line)
            {
                printf("FD %d: %s\n", fds[i], line);
                free(line);
            }
            else
            {
                close(fds[i]);
                fds[i] = -1;
                active_fds--;
            }
        }
    }
}

int main(void)
{
    test_multiple_fds();
    return 0;
}
