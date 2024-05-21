NAME = philo
CC = gcc
CFLAGS = -Wall -Werror -Wextra -g3 -fsanitize=address
AR = ar rcs
RM = rm -f


SRC = philo.c check_args.c create_thread.c data_init.c

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