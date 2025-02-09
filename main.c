#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>


char *to_fill_buff(int fd)
{
    
}
int main(void)
{
    int fd1, fd2;
    char buffer[100];
    char buffer_2[200];
    ssize_t bytes_read;
    ssize_t bytes_read2;
    // when we open a file teh linux assign automatically the file descriptor
    //!👉🏽if fd1.txt is the first file open; then fd1 = 3 (since 0,1,2 are reserved for stdin, stdout, stderr)
    fd1 = open("fd.txt", O_RDONLY);
    if(fd1 < 0)
    {
        perror("Error opening file");
        return 1;
    }
    fd2 = open("text.txt", O_RDONLY);
    if(fd2 < 0)
    {
        perror("Error opening file");
        return 2;
    }


    printf("File descriptor: %d\n", fd1);
    bytes_read = read(fd1, buffer, sizeof(buffer) - 1);
    if(bytes_read < 0)
    {
        perror("Error reading file");
        close(fd1);
        return 3;
    }
    buffer[bytes_read] = '\0';
    printf("Read %zd bytes: %s \n", bytes_read, buffer);
    
    //?Normally if got it well, I'll have 4 because it's the second file descriptor I open, acknowledging that I didn't close yet the first file descriptor
    printf("\n\n Print file descriptor %d\n", fd2);
    //*Why buffer - 1 ? it's because we dont the EOF character
    bytes_read2 = read(fd2, buffer_2, sizeof(buffer_2) - 1);
    if(bytes_read2 < 0)
    {
        perror("Error reading file");
        //to avoid leaks problem
        close(fd1);
        close(fd2);
        return 4;
    }
    buffer_2[bytes_read2] = '\0';
    printf("Read %zd bytes: %s \n", bytes_read2, buffer_2);
    sleep(100);
    close(fd1);
    close(fd2);
    printf("Closed file descriptor: %d\n", fd1);
    printf("Close file desccriptor: %d\n", fd2);
    return (0);
}
