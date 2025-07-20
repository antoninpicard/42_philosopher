NAME = philo_bonus
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf

SRC = ./sources_bonus/main_bonus.c ./sources_bonus/ft_atoi_bonus.c ./sources_bonus/utils.c\
	./sources_bonus/philo_routine.c ./sources_bonus/simulation_bonus.c

OBJDIR = obj
OBJ = $(SRC:./sources_bonus/%.c=$(OBJDIR)/%.o)


all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "philo_bonus compiled successfully"

$(OBJDIR)/%.o: ./sources_bonus/%.c ./includes_bonus/philo_bonus.h | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	$(RM) $(OBJDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
