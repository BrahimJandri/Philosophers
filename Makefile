NAME = philo
CC = cc
CFLAGS = -Wall -Werror -Wextra -fsanitize=thread
RM = rm -f

SRC = philo.c parsing.c init_philos.c philo_routine.c utils.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) -o $(NAME)	$(OBJ) $(LIBFT)

clean:
	@$(RM) $(OBJ)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean re fclean