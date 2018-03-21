/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 10:31:11 by claudioca         #+#    #+#             */
/*   Updated: 2018/03/21 11:48:15 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IO_H
# define IO_H

# include <shellma.h>
# include <ring_buffer.h>
# include <ft_string.h>
# include <dirent.h>

# define COMMAND_TABLE_SIZE 64
# define STRING_SIZE 128

typedef enum	e_input_mode
{
	NORMAL_INPUT,
	ESCAPE_INPUT,
	BACKSLASH_INPUT,
	QUOTE_INPUT,
	HEREDOC_INPUT,
}				t_input_mode;

typedef enum	e_terminal_command
{
	INSERT,
	MOVE_UP,
	MOVE_DOWN,
	MOVE_LEFT,
	MOVE_RIGHT,
	DELETE,
	DELETE_KEY,
	ARROW_UP,
	ARROW_DOWN,
	ARROW_LEFT,
	ARROW_RIGHT,
	CTRL_ARROW_UP,
	CTRL_ARROW_DOWN,
	CTRL_ARROW_LEFT,
	CTRL_ARROW_RIGHT,
	HOME,
	END,
	CLEAR_BOTTOM,
	SHOW_CURSOR,
	HIDE_CURSOR,
	TERMINAL_SENTINEL
}				t_terminal_command;

typedef struct	s_terminal
{
	struct termios	original;
	struct termios	custom;
	char			*prompt_pointer;
	t_ring_buffer	*history;
	t_string		*line;
	t_string		*clipboard;
	t_input_mode	input_mode;
	int				history_fd;
	int				line_position;
	int				line_number;
	int				number_of_lines;
	int				cursor;
	int				prompt_size;
	char			prompt[128];
	char			newline_prompt[16];
}				t_terminal;

typedef int				(*t_input_handle)(t_terminal *, int character);

int				init_command_table(void);
int				terminal_backslash(t_terminal *terminal, int c);
int				terminal_backslash_input(t_terminal *terminal,
												char c[16], int size);
int				handle_string_input(t_terminal *terminal, char c[16]);
int				handle_input(t_terminal *terminal, char c[16], int size);
int				handle_regular_input(t_terminal *terminal, int c);
int				print_prompt(t_terminal *terminal);
int				get_terminal_height(void);
int				get_terminal_width(void);
void			free_terminal(t_terminal *terminal);
int				setup_terminal(t_terminal *terminal, char const *prompt);
void			termios_toggle_isig(t_terminal *term, int toggle);
void			set_termios(struct termios *termios);
int				line_overflow(t_terminal *terminal, int index, int column,
																int target);
int				terminal_compare_string(t_terminal_command command,
														char const *str);
void			terminal_command(t_terminal_command command, int val);
int				terminal_adjust_insert(t_terminal *terminal, int index,
																int column);
int				terminal_draw(t_terminal *terminal, int c);
int				terminal_begining(t_terminal *terminal, int c);
int				terminal_write(t_terminal *terminal, int c);
int				terminal_noop(t_terminal *terminal, int c);
int				terminal_bol(t_terminal *terminal, int c);
int				terminal_eol(t_terminal *terminal, int c);
int				terminal_cancel_line(t_terminal *terminal, int c);
int				terminal_move_left(t_terminal *terminal, int c);
int				terminal_move_right(t_terminal *terminal, int c);
int				terminal_previous_word(t_terminal *terminal, int c);
int				terminal_next_word(t_terminal *terminal, int c);
int				terminal_exit(t_terminal *terminal, int c);
int				terminal_delete(t_terminal *terminal, int c);
int				terminal_delete_current(t_terminal *terminal, int c);
int				terminal_delete_word(t_terminal *terminal, int c);
int				terminal_delete_until_eol(t_terminal *terminal, int c);
int				terminal_kill_line(t_terminal *terminal, int c);
int				terminal_cancel_line(t_terminal *terminal, int c);
int				terminal_insert(t_terminal *terminal, int c);
int				terminal_insert_string(t_terminal *terminal, char *str);
int				terminal_eof(t_terminal *terminal, int c);
int				terminal_escape(t_terminal *terminal, int c);
int				terminal_is_at_newline(t_terminal *terminal);
int				history_open(t_terminal *terminal, int mode);
int				history_load(t_terminal *terminal);
int				history_append(t_terminal *terminal);
int				history_previous(t_terminal *terminal, int c);
int				history_next(t_terminal *terminal, int c);
int				dispatch_escape_string(t_terminal *terminal, char *str);
void			quit(t_terminal *terminal);
int				is_middle_of_unicode(unsigned char c);
int				cursor_is_middle_of_unicode(t_terminal *terminal);
int				get_letter_index(t_terminal *terminal);
int				auto_complete(t_terminal *terminal, int c);
void			auto_complete_push(t_array *array, char *base,
														char *candidate);
int				get_position_in_line(t_terminal *terminal, int index);
int				get_next_terminal_command(int fd, t_string *str);
int				print_options(t_array *array, t_terminal *terminal);
DIR				*get_dir(char *path, char **str);
void			search_dir(DIR *dir, char *str, t_array *array);
int				first_word(t_string *str);
int				is_separator(char c);
void			adjust_terminal(t_terminal *terminal, int nbr_lines);
int				choose_possibility(t_array *array, char *str,
											t_terminal *terminal);
int				is_at_newline(t_terminal *terminal, int index);
int				check_heredoc(char const *buffer, char const *last_line);
int				terminal_get_line(t_terminal *terminal);
char			*skip_white_spaces(char const *str);
int				is_open_bracket(char c);
char			get_closing_bracket(char c);
int				collect_heredocs(t_terminal *terminal);

#endif
