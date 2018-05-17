NAME = globbing
CC = cc
CCFLAGS = -Wall -Wextra -I. -I../libft/includes -g
CCFLAGSD = -Wall -Wextra -I. -I../libft/includes -g
SRC = main.c globbing.c

all:
	$(CC) $(CCFLAGS) $(SRC) -o $(NAME) -L../libft -lft
debug:
	$(CC) $(CCFLAGSD) $(SRC) -o $(NAME) -L../libft -lft
clean:
	rm $(NAME)
fclean: clean
re: fclean all
.PHONY: globbing
