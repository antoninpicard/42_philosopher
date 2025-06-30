NAME = philo_bonus

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread

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

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
