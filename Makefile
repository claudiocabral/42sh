# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/21 19:57:39 by claudioca         #+#    #+#              #
#    Updated: 2018/01/05 11:15:43 by claudioca        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:=	minishell
CC		:=	cc
CFLAGS	:=	-Wextra -Werror -Wall
CDEBUG	:=	-g

LIBFT_PATH	:=	libft
PRINTF_PATH = 	ft_printf

DEPDIR := .deps
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.Td
POSTCOMPILE = @mv -f $(DEPDIR)/$*.Td $(DEPDIR)/$*.dep && touch $@

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
			objs/IO/terminal_insert.o \
			objs/IO/terminal_delete.o \
			objs/IO/auto_complete.o \
			objs/IO/history.o \
			objs/IO/input_handler.o \
			objs/IO/setup.o \
			objs/builtins/env.o \
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


objs/%.o: srcs/%.c $(DEPDIR)/%.dep Makefile
	$(eval DIR := $(dir $@))
	$(eval CURRENT_DEPDIR := $(DIR:objs/%=$(DEPDIR)/%))
	@[[ -d $(DIR) ]] || mkdir -p $(DIR)
	@[[ -d $(CURRENT_DEPDIR) ]] || mkdir -p $(CURRENT_DEPDIR)
	$(CC) -c $< -o $@ $(CFLAGS) $(INC) $(DEPFLAGS)
	$(POSTCOMPILE)

$(DEPDIR)/%.dep: ;
.PRECIOUS: $(DEPDIR)/%.dep

include $(wildcard $(OBJS:objs/%.o=$(DEPDIR)/%.dep))

fclean: clean
	make $(PRINTF_FCLEAN)
	make $(LIBFT_FCLEAN)
ifeq ($(shell [ -e $(NAME) ] && echo 1 || echo 0),1)
	rm -rf $(NAME)
endif

clean:
	make $(LIBFT_CLEAN)
	make $(PRINTF_CLEAN)
ifeq ($(shell [ -e $(DEPDIR) ] && echo 1 || echo 0),1)
	rm -rf $(DEPDIR)
endif
ifeq ($(shell [ -e objs ] && echo 1 || echo 0),1)
	rm -rf objs
endif

re:
	$(MAKE) fclean
	$(MAKE) all
