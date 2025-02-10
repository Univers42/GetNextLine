#include <pthread.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "get_next_line_bonus.h"

#define THREAD_COUNT 3   // Number of threads (1 per file)
#define TEST_LINES 100000  // Number of lines per thread

typedef struct s_thread_data
{
    int fd;
    int id;
} t_thread_data;

void *thread_function(void *arg)
{
    t_thread_data *data = (t_thread_data *)arg;
    char *line;
    int line_count = 0;

    while ((line = get_next_line(data->fd)) && line_count < TEST_LINES)
    {
        printf("[Thread %d] %s", data->id, line);  // Print with thread ID
        free(line);
        line_count++;
    }

    printf("[Thread %d] Finished reading %d lines.\n", data->id, line_count);
    close(data->fd);
    return NULL;
}

int main()
{
    pthread_t threads[THREAD_COUNT];
    t_thread_data thread_data[THREAD_COUNT];

    // Open multiple files
    char *filenames[THREAD_COUNT] = {"file1.txt", "file2.txt", "file3.txt"};

    for (int i = 0; i < THREAD_COUNT; i++)
    {
        thread_data[i].fd = open(filenames[i], O_RDONLY);
        if (thread_data[i].fd < 0)
        {
            perror("Error opening file");
            return 1;
        }
        thread_data[i].id = i + 1;
    }

    // Create threads
    for (int i = 0; i < THREAD_COUNT; i++)
    {
        pthread_create(&threads[i], NULL, thread_function, (void *)&thread_data[i]);
    }

    // Wait for threads to finish
    for (int i = 0; i < THREAD_COUNT; i++)
    {
        pthread_join(threads[i], NULL);
    }

    printf("All threads completed!\n");
    return 0;
}
