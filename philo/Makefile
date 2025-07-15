NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread -g3

SRC = philo.c init.c threads.c utils.c monitor.c routine.c cleanup.c fork_utils.c monitor_utils.c ft_atoi.c
OBJ_DIR = obj
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
DEPS = philo.h

all: $(NAME)

$(OBJ_DIR):
	mkdir -p $@

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

$(OBJ_DIR)/%.o: %.c $(DEPS) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f philo

re: fclean all

bonus:
	@echo "Run make in ./philo_bonus for the bonus version."

.PHONY: all clean fclean re bonus