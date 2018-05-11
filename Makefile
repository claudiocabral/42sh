# **************************************************************************** #
#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/21 19:57:39 by claudioca         #+#    #+#              #
#    Updated: 2018/01/15 11:16:39 by ccabral          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:=	42sh
ifeq (CC,)
CC		:=	cc
endif
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
			objs/execute/collect_args.o \
			objs/execute/dispatch_branch.o \
			objs/execute/redirection.o \
			objs/execute/redirection_aggregator.o \
			objs/execute/pipe.o \
			objs/execute/builtins.o \
			objs/execute/path_entry.o \
			objs/execute/path.o \
			objs/execute/invoke.o \
			objs/execute/execute.o \
			objs/execute/expansion.o \
			objs/execute/command_name_lookup.o \
			objs/lexer/lexer.o \
			objs/lexer/lex.o \
			objs/lexer/lex_redirection.o \
			objs/lexer/token.o \
			objs/lexer/token_get.o \
			objs/lexer/token_identifier.o \
			objs/parser/parser.o \
			objs/parser/pipeline.o \
			objs/parser/redirection.o \
			objs/parser/match.o \
			objs/IO_bis/adjust_cursor.o \
			objs/IO_bis/control.o \
			objs/IO_bis/copy_paste.o \
			objs/IO_bis/delete.o \
			objs/IO_bis/free.o \
			objs/IO_bis/get_list.o \
			objs/IO_bis/history.o \
			objs/IO_bis/history_file.o \
			objs/IO_bis/list_create.o \
			objs/IO_bis/list_print.o \
			objs/IO_bis/list_str_utils.o \
			objs/IO_bis/list_utils.o \
			objs/IO_bis/mcbe.o \
			objs/IO_bis/mcblr.o \
			objs/IO_bis/move_cursor_down.o \
			objs/IO_bis/move_cursor_up.o \
			objs/IO_bis/move_history.o \
			objs/IO_bis/read_input.o \
			objs/IO_bis/return_string.o \
			objs/IO_bis/selected_list_utils.o \
			objs/IO_bis/term.o \
			objs/IO_bis/utils.o \
			objs/builtins/exit.o \
			objs/builtins/env.o \
			objs/builtins/setenv.o \
			objs/builtins/unsetenv.o \
			objs/builtins/cd.o \
			objs/builtins/cd_utils.o \
			objs/builtins/echo.o \
			objs/builtins/pwd.o \
			objs/environment/setenv.o \
			objs/environment/environment.o \
			objs/environment/prepare_env.o


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

OS = $(shell uname -s)

ifeq ($(OS),Linux)
    LIBTERMCAP = ncurses
else
    LIBTERMCAP = termcap
endif

.PHONY: all clean fclean re

all: $(NAME)

include $(LIBFT_PATH)/libft_rules.mk
include $(PRINTF_PATH)/printf_rules.mk

$(NAME): $(OBJS) $(LIBFT) $(PRINTF)
	$(CC) $(CFLAGS) $(OBJS) $(INC) -L$(LIBFT_PATH) -L$(PRINTF_PATH) \
		-l$(LIBTERMCAP) -lft -lftprintf -o $@


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
	$(MAKE) $(PRINTF_FCLEAN)
	$(MAKE) $(LIBFT_FCLEAN)
ifeq ($(shell [ -e $(NAME) ] && echo 1 || echo 0),1)
	rm -rf $(NAME)
endif

clean:
	$(MAKE) $(LIBFT_CLEAN)
	$(MAKE) $(PRINTF_CLEAN)
ifeq ($(shell [ -e $(DEPDIR) ] && echo 1 || echo 0),1)
	rm -rf $(DEPDIR)
endif
ifeq ($(shell [ -e $(NAME).dSYM ] && echo 1 || echo 0),1)
	rm -rf $(NAME).dSYM
endif
ifeq ($(shell [ -e objs ] && echo 1 || echo 0),1)
	rm -rf objs
endif

re:
	$(MAKE) fclean
	$(MAKE) all
