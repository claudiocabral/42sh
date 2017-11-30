# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/21 19:57:39 by claudioca         #+#    #+#              #
#    Updated: 2017/11/30 14:07:52 by claudioca        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:=	minishell
CC		:=	cc
CFLAGS	:=	-Wextra -Werror -Wall
CDEBUG	:=	-g

LIBFT_PATH	:=	libft/
PRINTF_PATH = 	ft_printf/

include $(LIBFT_PATH)/libft.mk
include $(PRINTF_PATH)/printf.mk

OBJS	=	objs/main.o

INC	=	-Iincludes \
		-I$(LIBFT_INCLUDES) \
		-I$(PRINTF_INCLUDES)

ifeq ($(ASAN), 1)
	DEBUG := 1
	CDEBUG += -fsanitize=address
endif

ifeq ($(DEBUG), 1)
	CFLAGS	+=	$(CDEBUG)
endif

.PHONY: all clean fclean re

all: $(NAME)

include $(LIBFT_PATH)/libft_rules.mk
include $(PRINTF_PATH)/printf_rules.mk

$(NAME): $(OBJS) $(LIBFT) $(PRINTF)
	$(CC) $(CFLAGS) $(OBJS) $(INC) -L$(LIBFT_PATH) -L$(PRINTF_PATH) -lft -lftprintf -o $@


objs/%.o: srcs/%.c Makefile
	@mkdir -p objs
	$(CC) -c $< -o $@ $(CFLAGS) $(INC)

fclean: clean
	make $(PRINTF_FCLEAN)
	make $(LIBFT_FCLEAN)
	rm -rf $(NAME)

clean:
	make $(LIBFT_CLEAN)
	make $(PRINTF_CLEAN)
	rm -rf objs

re:
	$(MAKE) fclean
	$(MAKE) all
