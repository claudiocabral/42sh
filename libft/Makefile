# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ccabral <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/08/24 13:19:14 by ccabral           #+#    #+#              #
#    Updated: 2018/05/11 11:41:27 by ctrouill         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include libft.mk

CC				:=	cc
CDEBUG			:=	-g
CFLAGS			:=	-Wall -Wextra -Werror

ifeq ($(DEBUG), 1)
	CFLAGS += $(CDEBUG)
endif

NAME := $(LIBFT)

.PHONY: all clean fclean re

all: $(NAME)

include libft_rules.mk

clean: $(LIBFT_CLEAN)

fclean: $(LIBFT_FCLEAN)

re:
	$(MAKE) $(LIBFT_FCLEAN)
	$(MAKE) all
