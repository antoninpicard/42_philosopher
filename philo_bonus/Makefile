NAME = philo_bonus
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf

SRC = ./src/main_bonus.c ./src/ft_atoi_bonus.c ./src/utils.c\
	./src/philo_routine.c ./src/simulation_bonus.c

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
	@echo "\033[32mphilo_bonus compiled successfully\033[0m"

$(OBJDIR)/%.o: ./src/%.c ./includes/philo_bonus.h | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	$(RM) $(OBJDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
