valgrind --leak-check=full --show-leak-kinds=all ./your_program
valgrind --tool=memcheck --track-origins=yes ./your_program
valgrind --tool=memcheck --undef-value-errors=yes ./your_program
valgrind --leak-check=full --show-leak-kinds=all --log-file=valgrind_output.txt ./your_program
valgrind --leak-check=full --show-leak-kinds=all --log-file=valgrind_output.txt ./your_program
gcc -fprofile-arcs -ftest-coverage your_program.c -o your_program
./your_program
gcov your_program.c
