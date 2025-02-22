CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

GNL_PATH = ../
GNL_SRCS = $(GNL_PATH)get_next_line.c $(GNL_PATH)get_next_line_utils.c
GNL_BONUS_SRCS = $(GNL_PATH)get_next_line_bonus.c $(GNL_PATH)get_next_line_utils_bonus.c

BUFFER_SIZES = 1 2 4 8 16 32 64 128 256 512 1024 2048 4096 8192 16384 32768 65536 131072 262144 524288 1048576000000

all: $(BUFFER_SIZES)

$(BUFFER_SIZES):
	@echo "Compiling with BUFFER_SIZE=$@"
	@$(MAKE) tester BUFFER_SIZE=$@
	@./tester
	@$(MAKE) clean

bonus: $(BUFFER_SIZES)
	@echo "Compiling with BUFFER_SIZE=$@"
	@$(MAKE) tester_bonus BUFFER_SIZE=$@
	@./tester_bonus
	@$(MAKE) clean

both: $(BUFFER_SIZES)
	@echo "Compiling with BUFFER_SIZE=$@"
	@$(MAKE) tester BUFFER_SIZE=$@
	@./tester
	@$(MAKE) tester_bonus BUFFER_SIZE=$@
	@./tester_bonus
	@$(MAKE) clean

tester: main.o test_utils.o $(GNL_SRCS:.c=.o)
	$(CC) $(CFLAGS) -DBUFFER_SIZE=$(BUFFER_SIZE) -o tester main.o test_utils.o $(GNL_SRCS:.c=.o)

tester_bonus: main_bonus.o test_utils.o $(GNL_BONUS_SRCS:.c=.o)
	$(CC) $(CFLAGS) -DBUFFER_SIZE=$(BUFFER_SIZE) -o tester_bonus main_bonus.o test_utils.o $(GNL_BONUS_SRCS:.c=.o)

main.o: main.c
	$(CC) $(CFLAGS) -DBUFFER_SIZE=$(BUFFER_SIZE) -c main.c -o main.o

main_bonus.o: main_bonus.c
	$(CC) $(CFLAGS) -DBUFFER_SIZE=$(BUFFER_SIZE) -c main_bonus.c -o main_bonus.o

test_utils.o: test_utils.c
	$(CC) $(CFLAGS) -DBUFFER_SIZE=$(BUFFER_SIZE) -c test_utils.c -o test_utils.o

$(GNL_SRCS:.c=.o): $(GNL_SRCS)
	$(CC) $(CFLAGS) -DBUFFER_SIZE=$(BUFFER_SIZE) -c $< -o $@

$(GNL_BONUS_SRCS:.c=.o): $(GNL_BONUS_SRCS)
	$(CC) $(CFLAGS) -DBUFFER_SIZE=$(BUFFER_SIZE) -c $< -o $@

clean:
	rm -f *.o tester tester_bonus

fclean: clean
	rm -f tester tester_bonus

re: fclean all
