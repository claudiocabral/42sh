# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/21 19:57:39 by claudioca         #+#    #+#              #
#    Updated: 2017/12/17 16:19:27 by claudioca        ###   ########.fr        #
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

OBJS	=	objs/main.o \
			objs/shellma.o \
			objs/file/script_session.o \
			objs/signals/handlers.o \
			objs/execute/path.o \
			objs/execute/invoke.o \
			objs/execute/execute.o \
			objs/execute/command_name_lookup.o \
			objs/lexer/lexer.o \
			objs/lexer/expansion.o \
			objs/lexer/token.o \
			objs/lexer/token_identifier.o \
			objs/parser/parser.o \
			objs/IO/interactive_session.o \
			objs/IO/terminal_commands.o \
			objs/IO/terminal_movement.o \
			objs/IO/input_handler.o \
			objs/IO/setup.o \
			objs/builtins/setenv.o \
			objs/builtins/unsetenv.o \
			objs/builtins/cd.o \
			objs/builtins/echo.o \
			objs/builtins/pwd.o \
			objs/environment/environment.o


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
	$(CC) $(CFLAGS) $(OBJS) $(INC) -L$(LIBFT_PATH) -L$(PRINTF_PATH) \
		-ltermcap -lft -lftprintf -o $@


objs/%.o: srcs/%.c Makefile
	$(eval DIR := $(dir $@))
	[[ -d $(DIR) ]] || mkdir -p $(DIR)
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
