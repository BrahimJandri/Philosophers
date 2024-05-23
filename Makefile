NAME = philo
CC = cc
CFLAGS = -Wall -Werror -Wextra -g3 #-fsanitize=thread
AR = ar rcs
RM = rm -f


SRC = philo.c check_args.c philo_monitoring.c philo_action.c utils.c philos_routine.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean re fclean