# **************************************************************************** #
#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/21 19:57:39 by claudioca         #+#    #+#              #
#    Updated: 2018/05/21 15:37:29 by ctrouill         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:=	42sh
ifeq (CC,)
CC		:=	cc
endif
CFLAGS	:=	-Wextra -Werror -Wall -march=native -Wshadow #-fsanitize=address
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
			objs/signals/fallback.o \
			objs/signals/sigint.o \
			objs/signals/signals.o \
			objs/signals/sigpipe.o \
			objs/signals/sigquit.o \
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
			objs/execute/execute_cleanup.o \
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
			objs/parser/check_errors.o \
			objs/edition/adjust_cursor.o \
			objs/edition/control.o \
			objs/edition/copy_paste.o \
			objs/edition/delete.o \
			objs/edition/free.o \
			objs/edition/get_list.o \
			objs/edition/history.o \
			objs/edition/history_file.o \
			objs/edition/list_create.o \
			objs/edition/list_print.o \
			objs/edition/list_str_utils.o \
			objs/edition/list_utils.o \
			objs/edition/mcbe.o \
			objs/edition/mcblr.o \
			objs/edition/move_cursor_down.o \
			objs/edition/move_cursor_up.o \
			objs/edition/move_history.o \
			objs/edition/read_input.o \
			objs/edition/return_string.o \
			objs/edition/selected_list_utils.o \
			objs/edition/term.o \
			objs/edition/utils.o \
			objs/edition/brackets.o \
			objs/edition/interactive_session.o \
			objs/heredoc/heredoc.o \
			objs/heredoc/heredoc_delim.o \
			objs/builtins/exit.o \
			objs/builtins/env.o \
			objs/builtins/setenv.o \
			objs/builtins/unsetenv.o \
			objs/builtins/cd.o \
			objs/builtins/cd_utils.o \
			objs/builtins/echo.o \
			objs/builtins/pwd.o \
			objs/environment/setenv.o \
			objs/environment/setup.o \
			objs/globbing/braks.o \
			objs/globbing/directory.o \
			objs/globbing/factory.o \
			objs/globbing/globbing.o \
			objs/globbing/init.o \
			objs/globbing/mnesia.o \
			objs/globbing/patterns.o \
			objs/globbing/predicate.o \
			objs/globbing/prepare.o \
			objs/globbing/yougotit.o \
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

llvm-checks:
	scan-build make

re:
	$(MAKE) fclean
	$(MAKE) all
