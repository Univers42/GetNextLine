void read_file(int fd, const char *filename)
{
    char *line;

    printf("\nReading from %s:\n", filename);
    while ((line = get_next_line_bonus(fd)) != NULL)
    {
        printf("%s", line);  // Print the line
        free(line);  // Free the memory allocated by get_next_line_bonus
    }
}

int main()
{
    int fd1, fd2;

    // Open two files for reading
    fd1 = open("file1.txt", O_RDONLY);
    if (fd1 < 0)
    {
        perror("Error opening file1.txt");
        return 1;
    }

    fd2 = open("file2.txt", O_RDONLY);
    if (fd2 < 0)
    {
        perror("Error opening file2.txt");
        close(fd1);
        return 1;
    }

    // Read and print lines from the first file
    read_file(fd1, "file1.txt");

    // Read and print lines from the second file
    read_file(fd2, "file2.txt");

    // Close both files
    close(fd1);
    close(fd2);

    return 0;
}