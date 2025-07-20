NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread
RM = rm -rf

SRC = ./sources/main.c ./sources/ft_atoi.c ./sources/init_table.c\
	./sources/simulation.c ./sources/thinking.c ./sources/forks.c\
	./sources/print_status.c ./sources/eating.c ./sources/utils.c

OBJDIR = obj
OBJ = $(SRC:./sources/%.c=$(OBJDIR)/%.o)


all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "philo compiled successfully"

$(OBJDIR)/%.o: ./sources/%.c ./includes/philo.h | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	$(RM) $(OBJDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

bonus:
	@echo "Run make in ./philo_bonus for the bonus version."

.PHONY: all clean fclean re bonus
