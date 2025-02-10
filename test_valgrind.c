#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "get_next_line.h"

#define DEFAULT_BUFFER_SIZE 32

void run_test(int fd, const char *filename)
{
    printf("\n📂 Testing file: %s\n", filename);
    char *line;
    int line_count = 0;

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("[%d] %s", line_count++, line);
        free(line);
    }

    close(fd);
    printf("✅ Finished reading %s\n", filename);
}

int main(int argc, char **argv)
{
    if (argc < 3)
    {
        printf("Usage: %s <BUFFER_SIZE> <file1> [file2] ...\n", argv[0]);
        return 1;
    }

    int buffer_size = atoi(argv[1]);
    if (buffer_size <= 0)
    {
        printf("❌ Invalid BUFFER_SIZE. Using default: %d\n", DEFAULT_BUFFER_SIZE);
        buffer_size = DEFAULT_BUFFER_SIZE;
    }

    printf("🚀 Running GNL Tester with BUFFER_SIZE = %d\n", buffer_size);

    for (int i = 2; i < argc; i++)
    {
        int fd = open(argv[i], O_RDONLY);
        if (fd < 0)
        {
            perror("Error opening file");
            continue;
        }
        run_test(fd, argv[i]);
    }

    printf("\n🔍 Running Valgrind Memory Check...\n");
    system("valgrind --leak-check=full --show-leak-kinds=all ./gnl_tester 32 test.txt");

    return 0;
}
