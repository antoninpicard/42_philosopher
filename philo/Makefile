NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread
RM = rm -rf

SRC = ./src/main.c ./src/ft_atoi.c ./src/init_table.c\
	./src/simulation.c ./src/thinking.c ./src/forks.c\
	./src/print_status.c ./src/eating.c ./src/utils.c

OBJDIR = obj
OBJ = $(SRC:./src/%.c=$(OBJDIR)/%.o)


all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
		@echo "     _________"
	@echo "    / ======= \\"
	@echo "   / __________\\"
	@echo "  | ___________ |"
	@echo "  | | -       | |"
	@echo "  | |         | |"
	@echo "  | |_________| |________________________"
	@echo "  \\=____________/           anpicard    )"
	@echo "  / \"\"\"\"\"\"\"\"\"\"\" \\                      )"
	@echo " / ::::::::::::: \\                  =D-'"
	@echo "(_________________)"
	@echo "\033[32mphilo compiled successfully\033[0m"

$(OBJDIR)/%.o: ./src/%.c ./includes/philo.h | $(OBJDIR)
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
