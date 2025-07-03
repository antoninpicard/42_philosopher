NAME = philo_bonus

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread -g3

SRCS = philo_bonus.c \
    	init_bonus.c \
    	process_bonus.c \
    	routine_bonus.c \
    	monitor_bonus.c \
    	utils_bonus.c \
    	cleanup_bonus.c \
    	philo_process_bonus.c \
    	philo_monitor_utils_bonus.c \
    	ft_atoi.c

OBJ_DIR = obj
OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

all: dir $(NAME)

dir:
	mkdir -p $(OBJ_DIR)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

$(OBJ_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all dir clean fclean re
