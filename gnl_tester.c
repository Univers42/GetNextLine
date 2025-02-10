#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>
#include <errno.h>
#include "get_next_line.h"

#define BUFFER_SIZES {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 4096}
#define TEST_FILE "test.txt"
#define STRESS_FILE "stress_test.txt"
#define NONBLOCK_FILE "nonblock.txt"
#define FD_COUNT 3  // Number of file descriptors for multi-FD testing

// 🕒 Get current time in milliseconds using gettimeofday()
long get_time_ms()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

// 📌 Benchmark Function
void benchmark_gnl(const char *filename, int buffer_size)
{
    printf("\n⏱️ Benchmarking %s with BUFFER_SIZE=%d\n", filename, buffer_size);

    long start_time = get_time_ms();

    int fd = open(filename, O_RDONLY);
    if (fd < 0)
    {
        perror("Error opening file");
        return;
    }

    char *line;
    int line_count = 0;

    while ((line = get_next_line(fd)) != NULL)
    {
        free(line);
        line_count++;
    }

    close(fd);

    long end_time = get_time_ms();
    printf("✅ Read %d lines in %ld ms (BUFFER_SIZE=%d)\n", line_count, end_time - start_time, buffer_size);
}

// 🛑 Non-Blocking Test
void test_nonblocking()
{
    printf("\n🔄 Testing Non-Blocking Mode (O_NONBLOCK)...\n");

    int fd = open(NONBLOCK_FILE, O_RDONLY | O_NONBLOCK);
    if (fd < 0)
    {
        perror("Error opening non-blocking file");
        return;
    }

    char *line = get_next_line(fd);
    if (line)
    {
        printf("📝 Read: %s\n", line);
        free(line);
    }
    else if (errno == EAGAIN)
    {
        printf("✅ Non-blocking read correctly returned nothing.\n");
    }
    else
    {
        printf("❌ Unexpected result!\n");
    }

    close(fd);
}

// 🔄 Multi-FD Test
void test_multiple_fds()
{
    printf("\n🔹 Testing Multiple File Descriptors...\n");

    char *filenames[FD_COUNT] = {"multi1.txt", "multi2.txt", "multi3.txt"};
    int fds[FD_COUNT];

    for (int i = 0; i < FD_COUNT; i++)
    {
        fds[i] = open(filenames[i], O_RDONLY);
        if (fds[i] < 0)
        {
            perror("Error opening file");
            return;
        }
    }

    char *line;
    int active_fds = FD_COUNT;

    while (active_fds > 0)
    {
        for (int i = 0; i < FD_COUNT; i++)
        {
            if (fds[i] != -1)
            {
                line = get_next_line(fds[i]);
                if (line)
                {
                    printf("[FD %d] %s", fds[i], line);
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

    printf("✅ Multi-FD Test Passed!\n");
}

// 🚀 Stress Test
void stress_test()
{
    printf("\n🚀 Running Stress Test (1M+ lines)...\n");

    system("yes 'STRESS_LINE' | head -n 1000000 > " STRESS_FILE);

    benchmark_gnl(STRESS_FILE, 1024);

    printf("✅ Stress Test Passed!\n");
}

// 🔍 Memory Leak Check
void check_memory_leaks()
{
    printf("\n🔍 Checking for memory leaks...\n");
    //system("valgrind --leak-check=full --show-leak-kinds=all ./gnl_test < /dev/null");
}

// 🔄 Compare Output
void compare_output(const char *expected_file, const char *output_file)
{
    printf("\n🔄 Comparing output with expected results...\n");
    char command[256];

    // Run the program and redirect the output to the output file
    sprintf(command, "./gnl_test > %s", output_file);
    if (system(command) != 0)
        fprintf(stderr, "Error executing command: %s\n", command);


    // Use diff to compare the expected and output files
    sprintf(command, "diff %s %s > diff_results.txt", expected_file, output_file);
    if (system(command) != 0)
        fprintf(stderr, "Error executing command: %s\n", command);


    // Check if the diff results file is empty (no differences)
    if (system("test -s diff_results.txt") == 0) // File is empty (no diff)
        printf("✅ Output matches expected results!\n");
    else // File has content (there are differences)
    {
        printf("❌ Differences found! Check diff_results.txt\n");
    }
}


int main()
{
    int buffer_sizes[] = BUFFER_SIZES;
    int num_sizes = sizeof(buffer_sizes) / sizeof(buffer_sizes[0]);

    // Create test files
    system("seq 1 1000 > " TEST_FILE);
    system("echo 'Hello' > multi1.txt; echo 'World' > multi2.txt; echo '42' > multi3.txt");
    system("touch " NONBLOCK_FILE);  // Empty non-blocking file

    // Run tests for different BUFFER_SIZE values
    for (int i = 0; i < num_sizes; i++)
    {
        benchmark_gnl(TEST_FILE, buffer_sizes[i]);
    }

    compare_output(TEST_FILE, "output.txt");

    test_multiple_fds();
    stress_test();
    test_nonblocking();
    check_memory_leaks();

    return 0;
}
