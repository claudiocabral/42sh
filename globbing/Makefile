NAME = globbing
CC = cc
CCFLAGS = -Wall -Wextra -pedantic -I. -g
CCFLAGSD = -Wall -Wextra -pedantic -I. -g -DDEBUG
SRC = main.c globbing.c linked.c expanders.c walker.c utils.c

all:
	$(CC) $(CCFLAGS) $(SRC) -o $(NAME)
debug:
	$(CC) $(CCFLAGSD) $(SRC) -o $(NAME)
clean:
	rm $(NAME)
fclean: clean
re: fclean all
.PHONY: globbing
