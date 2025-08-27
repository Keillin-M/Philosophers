NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -pthread

# Colors for output
GREEN = \033[0;32m
BLUE = \033[0;34m
RED = \033[0;31m
YELLOW = \033[0;33m
NC = \033[0m

# Verbose mode control
ifdef VERBOSE
    QUIET =
else
    QUIET = @
endif

# Directories
SRC_DIR = src
INCLUDE_DIR = include
OBJ_DIR = obj
INCLUDES = -I$(INCLUDE_DIR)

# Source files
SRCS = $(SRC_DIR)/philo.c \
	$(SRC_DIR)/utils.c \

# object files
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(OBJ_DIR) $(NAME)

$(NAME): $(OBJS)
	$(QUIET)$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)✓ $(NAME) built successfully!$(NC)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@echo "$(YELLOW)Compiling:$(NC) $<"
	$(QUIET)$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	$(QUIET)mkdir -p $(OBJ_DIR)

clean:
	@echo "$(RED)Cleaning object files..$(NC)"
	$(QUIET)rm -rf $(OBJ_DIR)

fclean: clean
	@echo "$(RED)Removing $(NAME)..$(NC)"
	$(QUIET)rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
