# get_next_line 📖

A C function that reads a file line by line, one line at a time. This project teaches you about file descriptors, static variables, and memory management in C.

## What is get_next_line?

Imagine you have a huge text file (like a 10GB log file) and you want to read it line by line without loading everything into memory at once. That's exactly what `get_next_line` does!

In C, we don't have a built-in function like Python's `readline()` or JavaScript's line-by-line reading. So we build our own!

## Core Concepts

### Static Variables
The magic behind `get_next_line` lies in **static variables**. Unlike regular variables that "forget" their values when a function ends, static variables remember their state between function calls.

```c
char *get_next_line(int fd) {
    static char *buffer;  // This remembers leftover data between calls!
    // ... rest of the function
}
```

### File Descriptors
- `fd` = File Descriptor (just a number that represents an open file)
- `0` = stdin (keyboard input)
- `1` = stdout (terminal output)
- `2` = stderr (error output)
- `3+` = actual files you open

### Buffer Management
We read chunks of data into a buffer, extract one line, and keep the rest for the next call. It's like having a bucket that fills up with water (data) and you pour out one glass (line) at a time.

## Project Structure

```
get_next_line/
├── get_next_line.c          # Main function (mandatory)
├── get_next_line_utils.c    # Helper functions (mandatory)
├── get_next_line.h          # Header file (mandatory)
├── get_next_line_bonus.c    # Bonus version (handles multiple fds)
├── get_next_line_utils_bonus.c
├── get_next_line_bonus.h
├── main.c                   # Test program
├── Makefile                 # Build system
└── README.md               # This file
```

## ⚙️ How It Works

1. **First call**: Read data from file into buffer
2. **Find newline**: Look for `\n` character
3. **Extract line**: Copy everything up to `\n` (including it)
4. **Save leftovers**: Keep remaining data in static buffer
5. **Return line**: Give back the extracted line
6. **Next call**: Start with leftover data from step 4

```c
// Example usage:
int fd = open("file.txt", O_RDONLY);
char *line;

while ((line = get_next_line(fd)) != NULL) {
    printf("Line: %s", line);
    free(line);  // Don't forget to free!
}
close(fd);
```

## Getting Started

### Prerequisites
- GCC compiler
- Make utility
- Basic understanding of C pointers and memory management

### Compilation

**Normal version (single file descriptor):**
```bash
make
```

**Bonus version (multiple file descriptors):**
```bash
make bonus
```

**Clean up:**
```bash
make clean      # Remove object files
make fclean     # Remove everything
make re         # Rebuild everything
```

## 🎮 Running the Demo

Our `main.c` creates a simple program that:
1. Reads lines from standard input (keyboard)
2. Writes each line to a file called `register.txt`
3. Uses our custom `get_next_line` function

### Run the program:
```bash
./get_next_line
```

### Test with a file:
```bash
./get_next_line < test_file.txt
```

### Interactive test:
```bash
./get_next_line
# Type some lines:
Hello world!
This is line 2
End of input
# Press Ctrl+D to end input
```

Check `register.txt` to see your lines saved!

## 🔧 Technical Details

### Buffer Size
The `BUFFER_SIZE` macro defines how many bytes we read at once. You can change it during compilation:

```bash
gcc -D BUFFER_SIZE=1024 ...
```

### Memory Management
- Each call to `get_next_line` returns a `malloc`ed string
- **YOU MUST FREE** the returned line to avoid memory leaks
- The function handles its own internal memory management

### Error Handling
- Returns `NULL` when EOF is reached
- Returns `NULL` on read errors
- Handles invalid file descriptors gracefully

## 🌟 Bonus Features

The bonus version can handle multiple file descriptors simultaneously:

```c
int fd1 = open("file1.txt", O_RDONLY);
int fd2 = open("file2.txt", O_RDONLY);

char *line1 = get_next_line(fd1);  // Read from file1
char *line2 = get_next_line(fd2);  // Read from file2
char *line3 = get_next_line(fd1);  // Back to file1
```

## Common Issues

1. **Segmentation fault**: Usually forgot to free() returned lines
2. **Memory leaks**: Not freeing allocated memory
3. **Infinite loops**: Not handling EOF correctly
4. **Compilation errors**: Missing includes or wrong function signatures
5. **stack overflow**: Missing to handle really big messages for big buffer

## Learning Outcomes

After completing this project, you'll understand:
- How file I/O works in C
- Static variables and their use cases
- Dynamic memory allocation patterns
- Buffer management techniques
- Error handling in system calls

## Testing Tips

1. Test with different `BUFFER_SIZE` values (1, 10, 1000)
2. Test with empty files
3. Test with files ending with/without newlines
4. Test with very long lines
5. Test with binary files (should handle gracefully)

## Contributing

Feel free to suggest improvements or report bugs! This project is great for learning, so don't hesitate to experiment with the code.

---

*Happy coding! 🚀*

> **Note**: This project is part of the 42 School curriculum and focuses on understanding low-level file operations in C.