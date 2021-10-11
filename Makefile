NAME = pipex

SRC = pipex.c utils1.c utils2.c utils3.c utils4.c

OBJ = $(SRC:.c=.o)

RM = rm -rf

$(NAME): $(OBJ)
	${RM} pipex
	@gcc -g -Wall -Wextra -Werror -o $(NAME) $(OBJ)

all: $(NAME)

clean:
	${RM} ${OBJ}

fclean: clean
	${RM} ${NAME}

re:	fclean all

.PHONY: all clean fclean re
