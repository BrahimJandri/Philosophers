NAME = philo
CC = gcc
CFLAGS = -Wall -Werror -Wextra
AR = ar rcs
RM = rm -f
LIBFT = ./libft/libft.a


SRC = philo.c

OBJ = $(SRC:.c=.o)

all = $(NAME)

$(NAME): $(OBJ)
	$(MAKE) -C ./libft
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT)

clean:
	$(MAKE) clean -C ./libft
	$(RM) $(OBJ)

fclean: clean
	$(MAKE) fclean -C ./libft
	$(RM) $(NAME)

re: fclean all

re_bonus: fclean bonus

.SECONDARY: $(OBJ)
.PHONY: all clean re fclean re_bonus