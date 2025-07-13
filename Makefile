NAME = get_next_line
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -I$(INC_DIR)
MAIN = get_next_line
UTILS = $(MAIN)_utils
INC_DIR = .
DEF_SIZE=1000
BUFF_FLAG= -DBUFFER_SIZE=$(DEF_SIZE)

# Conditional source selection using ifeq
COMPILE_MODE ?= normal
ifeq ($(COMPILE_MODE), bonus)
SRCS := $(MAIN)_bonus.c $(UTILS)_bonus.c
else
SRCS := $(MAIN).c $(UTILS).c
endif

# Generate object files from source files
OBJECTS := $(SRCS:.c=.o)

# Define macro for compilation
define compile_program
	$(CC) $(CFLAGS) $(BUFF_FLAG) $(1) main.c -o $(NAME)
endef

# Define macro for object compilation
define compile_objects
	$(CC) $(CFLAGS) -c $(1) -o $(2)
endef

# Default target
all: $(NAME)

# Main compilation rule
$(NAME): $(OBJECTS)
	$(call compile_program,$(OBJECTS))

# Pattern rule for object files
%.o: %.c
	$(call compile_objects,$<,$@)

# Bonus target
bonus:
	$(MAKE) COMPILE_MODE=bonus

# Clean object files
clean:
	$(RM) *.o

# Clean everything
fclean: clean
	$(RM) $(NAME)

# Rebuild everything
re: fclean all

# Phony targets
.PHONY: clean fclean all re bonus
