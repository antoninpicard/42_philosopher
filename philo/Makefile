NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread -g3

SRC = philo.c init.c threads.c utils.c monitor.c routine.c cleanup.c fork_utils.c monitor_utils.c ft_atoi.c
OBJ = $(SRC:.c=.o)
DEPS = philo.h

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o philo $(OBJ)

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	@rm -f philo

re: fclean all

bonus:
	@echo "Run make in ./philo_bonus for the bonus version."

.PHONY: all clean fclean re bonus