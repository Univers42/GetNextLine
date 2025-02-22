CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address

GNL_PATH = ../
GNL_SRCS = $(GNL_PATH)get_next_line.c $(GNL_PATH)get_next_line_utils.c
GNL_BONUS_SRCS = $(GNL_PATH)get_next_line_bonus.c $(GNL_PATH)get_next_line_utils_bonus.c

BUFFER_SIZES = 1 2 4 8 16 32 64 128 256 512 1024 2048 4096 8192 16384 32768 65536 131072 262144 524288 1048576

all: tester tester_bonus

tester: main.o test_utils.o $(GNL_SRCS:.c=.o)
	$(CC) $(CFLAGS) -o tester main.o test_utils.o $(GNL_SRCS:.c=.o)

tester_bonus: main_bonus.o test_utils.o $(GNL_BONUS_SRCS:.c=.o)
	$(CC) $(CFLAGS) -o tester_bonus main_bonus.o test_utils.o $(GNL_BONUS_SRCS:.c=.o)

run_tests: tester tester_bonus
	@echo "  |_   _|        | | | |         | |   (_)            "
	@echo "    | | _ __  ___| |_| |__   __ _| |__  _ _ __   __ _ "
	@echo "    | || '_ \\/ __| __| '_ \\ / _\` | '_ \\| | '_ \\ / _\` |"
	@echo "  _| || | | \\__ \\ |_| | | | (_| | | | | | | | | (_| |"
	@echo "  \\___/_| |_|___/\\__|_| |_|\\__,_|_| |_|_|_| |_|\\__, |"
	@echo "                                                __/ |"
	@echo "                                               |___/ "
	@for size in $(BUFFER_SIZES); do \
		echo ""; \
		echo "Running tests with BUFFER_SIZE = $$size"; \
		$(CC) $(CFLAGS) -DBUFFER_SIZE=$$size -o tester main.o test_utils.o $(GNL_SRCS:.c=.o); \
		./tester; \
		$(CC) $(CFLAGS) -DBUFFER_SIZE=$$size -o tester_bonus main_bonus.o test_utils.o $(GNL_BONUS_SRCS:.c=.o); \
		./tester_bonus; \
	done
	@echo ""
	@echo "     ✨ All Tests Passed! ✨"
	@echo ""
	@echo "         .-=========-.       "
	@echo "         \\'-=======-'/       "
	@echo "         _|   .=.   |_       "
	@echo "        ((|  {{1}}  |))      "
	@echo "         \\|   /|\\   |/       "
	@echo "          \\__ '`' __/        "
	@echo "            _`) (`_          "
	@echo "          _/_______\\_        "
	@echo "         /___________\\       "
	@echo ""
	@echo "    🎉 Success Trophy 🎉     "
	@echo ""

clean:
	rm -f *.o tester tester_bonus

fclean: clean
	rm -f tester tester_bonus

re: fclean all

.PHONY: all run_tests clean fclean re
