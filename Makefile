# **************************************************************************** #
#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/21 19:57:39 by claudioca         #+#    #+#              #
#    Updated: 2018/06/09 16:58:09 by ctrouill         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:=	42sh
ifeq (CC,)
CC		:= cc
endif

CFLAGS	:=	$(CFLAGS) -Wextra -Werror -Wall -march=native -Wshadow
CDEBUG	:=	-g

LIBFT_PATH	:=	libft
PRINTF_PATH = 	ft_printf

MAKEFLAGS += -j4 --no-print-directory

DEPDIR := .deps
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.Td
POSTCOMPILE = @mv -f $(DEPDIR)/$*.Td $(DEPDIR)/$*.dep && touch $@

include $(LIBFT_PATH)/libft.mk
include $(PRINTF_PATH)/printf.mk

MAIN_OBJ =	objs/main.o
FUZZ_OBJ =	objs/tests/fuzz_process_input.o
OBJS	=	objs/shellma.o \
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
			objs/execute/localvar.o \
			objs/execute/expand_localvar.o \
			objs/lexer/lexer.o \
			objs/lexer/lex.o \
			objs/lexer/lex_redirection.o \
			objs/lexer/lex_comment.o \
			objs/lexer/token.o \
			objs/lexer/token_get.o \
			objs/lexer/token_quote.o \
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
			objs/edition/autocompletion/auto_complete.o \
			objs/edition/autocompletion/auto_complete_printer.o \
			objs/edition/autocompletion/auto_complete_tools.o \
			objs/edition/autocompletion/auto_complete_adjust.o \
			objs/edition/autocompletion/possibilities_tools.o \
			objs/edition/autocompletion/autocompletion.o \
			objs/edition/autocompletion/move.o \
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
			objs/builtins/unset.o \
			objs/builtins/export.o \
			objs/builtins/print_export.o \
			objs/builtins/alias.o \
			objs/builtins/unalias.o \
			objs/builtins/print_alias.o \
			objs/builtins/alias_utils.o \
			objs/builtins/utils.o \
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
			objs/globbing/reducers.o \
			objs/globbing/yougotit.o \
			objs/globbing/strtok_glob.o \
			objs/config/loader.o \
			objs/environment/environment.o \
			objs/environment/prepare_env.o \
			objs/environment/prepare_localvar.o \
			objs/environment/prepare_alias.o


INC	=	-Iincludes \
		-I$(LIBFT_INCLUDES) \
		-I$(PRINTF_INCLUDES)

ifeq ($(ASAN), 1)
	DEBUG := 1
	#CDEBUG += -fsanitize=address
endif

ifeq ($(FUZZ), 1)
	CC = clang
	DEBUG := 1
	CDEBUG += -fsanitize=fuzzer,address,signed-integer-overflow
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

$(NAME): $(OBJS) $(MAIN_OBJ) $(LIBFT) $(PRINTF)
	$(CC) $(CFLAGS) $(OBJS) $(MAIN_OBJ) $(INC) -L$(LIBFT_PATH) -L$(PRINTF_PATH) \
		-l$(LIBTERMCAP) -lft -lftprintf -o $@

compile_fuzz: fuzz
	$(MAKE) fclean
	FUZZ=1 $(MAKE) fuzz

run_fuzz:
	FUZZ=1 $(MAKE) compile_fuzz
	./fuzz -artifact_prefix=./fuzz_log/ fuzz_log

fuzz:  $(OBJS) $(FUZZ_OBJ) $(LIBFT) $(PRINTF)
	mkdir -p fuzz_log
	$(CC) $(CFLAGS) $(OBJS) $(FUZZ_OBJ) $(INC) -L$(LIBFT_PATH) -L$(PRINTF_PATH) \
		-l$(LIBTERMCAP) -lft -lftprintf $(CDEBUG) -o $@


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
ifeq ($(shell [ -e fuzz ] && echo 1 || echo 0),1)
	rm -rf fuzz
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

# needed by dockerfile
test: run_fuzz

re:
	$(MAKE) fclean
	$(MAKE) all
