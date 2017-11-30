include printf.mk

CC		:=	cc
CFLAGS	:=	-Wextra -Werror -Wall
CDEBUG	:=	-g

NAME := $(PRINTF)

ifeq ($(DEBUG), 1)
	CFLAGS	+=	$(CDEBUG)
endif

.PHONY: all clean fclean re

include printf_rules.mk

all: $(NAME)

fclean: $(PRINTF_FCLEAN)

clean: $(PRINTF_CLEAN)

re: fclean all
