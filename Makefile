NAME = philo
CC = gcc
CFLAGS = -Wall -Werror -Wextra
AR = ar rcs
RM = rm -f

SRC =

OBJ = $(SRC:.c=.o)

all = $(NAME)

clean:
	$(RM) $(OBJ) $(OBJB)

fclean: clean
	$(RM) $(NAME)

re: fclean all

re_bonus: fclean bonus

.SECONDARY: $(OBJ)
.PHONY: all clean re fclean re_bonus