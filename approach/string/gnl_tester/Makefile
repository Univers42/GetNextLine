CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

GNL_PATH = ../
GNL_SRCS = $(GNL_PATH)get_next_line.c $(GNL_PATH)get_next_line_utils.c
GNL_BONUS_SRCS = $(GNL_PATH)get_next_line_bonus.c $(GNL_PATH)get_next_line_utils_bonus.c

all: tester
	./tester

bonus: tester_bonus
	./tester_bonus

both: tester tester_bonus
	./tester
	./tester_bonus

tester: main.o test_utils.o $(GNL_SRCS:.c=.o)
	$(CC) $(CFLAGS) -o tester main.o test_utils.o $(GNL_SRCS:.c=.o)

tester_bonus: main_bonus.o test_utils.o $(GNL_BONUS_SRCS:.c=.o)
	$(CC) $(CFLAGS) -o tester_bonus main_bonus.o test_utils.o $(GNL_BONUS_SRCS:.c=.o)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o

main_bonus.o: main_bonus.c
	$(CC) $(CFLAGS) -c main_bonus.c -o main_bonus.o

test_utils.o: test_utils.c
	$(CC) $(CFLAGS) -c test_utils.c -o test_utils.o

$(GNL_SRCS:.c=.o): $(GNL_SRCS)
	$(CC) $(CFLAGS) -c $< -o $@

$(GNL_BONUS_SRCS:.c=.o): $(GNL_BONUS_SRCS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o tester tester_bonus

fclean: clean
	rm -f tester tester_bonus

re: fclean all
