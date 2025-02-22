#!/bin/bash
echo "🔍 Running tests..."

make re
mkdir -p logs outputs test_cases expected_output

# Create dummy test files if they don't exist
echo -n "" > test_cases/empty.txt
echo "This is a single line." > test_cases/one_line.txt
echo -e "Line 1\nLine 2\nLine 3" > test_cases/multi_lines.txt
echo -n "No newline at end" > test_cases/no_newline.txt
head -c 100000 /dev/urandom > test_cases/big_file.txt

# Create expected output files
echo -n "" > expected_output/empty.txt
echo "This is a single line." > expected_output/one_line.txt
echo -e "Line 1\nLine 2\nLine 3" > expected_output/multi_lines.txt
echo -n "No newline at end" > expected_output/no_newline.txt
head -c 100000 /dev/urandom > expected_output/big_file.txt

# Debug information
echo "Contents of test_cases directory:"
ls -l test_cases

echo "Contents of expected_output directory:"
ls -l expected_output

./tester > logs/tester_log.txt
./tester_bonus > logs/tester_bonus_log.txt

echo "✅ Tests completed."

echo "🔬 Running Valgrind..."
valgrind --leak-check=full --track-origins=yes ./tester > logs/valgrind_tester_log.txt 2>&1
valgrind --leak-check=full --track-origins=yes ./tester_bonus > logs/valgrind_tester_bonus_log.txt 2>&1

echo "🧹 Check logs for memory leaks: logs/valgrind_tester_log.txt"
echo "🧹 Check logs for memory leaks: logs/valgrind_tester_bonus_log.txt"

echo "📦 Cleaning up..."
make fclean
