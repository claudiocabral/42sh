/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 10:31:11 by claudioca         #+#    #+#             */
/*   Updated: 2018/01/13 16:46:22 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IO_H
# define IO_H

# include <shellma.h>
# include <ring_buffer.h>
# include <ft_string.h>

# define COMMAND_TABLE_SIZE 64
# define STRING_SIZE 128

typedef enum	e_keys
{
	CTRL_A = 1,
	CTRL_B = 2,
	CTRL_C = 3,
	CTRL_D = 4,
	CTRL_E = 5,
	CTRL_F = 6,
	CTRL_G = 7,
	CTRL_H = 8,
	CTRL_I = 9,
	CTRL_J = 10,
	CTRL_K = 11,
	CTRL_L = 12,
	CTRL_M = 13,
	CTRL_N = 14,
	CTRL_O = 15,
	CTRL_P = 16,
	CTRL_Q = 17,
	CTRL_R = 18,
	CTRL_S = 19,
	CTRL_T = 20,
	CTRL_U = 21,
	CTRL_V = 22,
	CTRL_W = 23,
	CTRL_X = 24,
	CTRL_Y = 25,
	CTRL_Z = 26
}				t_keys;

typedef enum	e_terminal_command
{
	INSERT,
	MOVE_LEFT,
	MOVE_RIGHT,
	DELETE,
	DELETE_KEY,
	ARROW_UP,
	ARROW_DOWN,
	ARROW_LEFT,
	ARROW_RIGHT
}				t_terminal_command;

typedef struct	s_terminal
{
	t_ring_buffer	*history;
	t_string		*line;
	int				cursor;
	int				tty;
	char			prompt[128];
	int				prompt_size;
	struct termios	original;
	struct termios	custom;
}				t_terminal;

typedef int				(*t_input_handle)(t_terminal *, int character);

int				init_command_table(void);
int				handle_input(t_terminal *terminal, char c[16]);
void			print_prompt(t_terminal *terminal);
t_terminal		*get_terminal(t_terminal *terminal);
void			free_terminal(t_terminal *terminal);
int				setup_terminal(t_terminal *terminal, char const *prompt);
void			termios_toggle_isig(t_terminal *term, int toggle);
void			set_termios(struct termios *termios);
int				terminal_compare_string(t_terminal_command command,
														char const *str);
void			terminal_command(t_terminal_command command, int val);
int				terminal_bol(t_terminal *terminal, int c);
int				terminal_eol(t_terminal *terminal, int c);
int				terminal_cancel_line(t_terminal *terminal, int c);
int				terminal_move_left(t_terminal *terminal, int c);
int				terminal_move_right(t_terminal *terminal, int c);
int				terminal_exit(t_terminal *terminal, int c);
int				terminal_delete(t_terminal *terminal, int c);
int				terminal_delete_word(t_terminal *terminal, int c);
int				terminal_delete_until_eol(t_terminal *terminal, int c);
int				terminal_kill_line(t_terminal *terminal, int c);
int				terminal_cancel_line(t_terminal *terminal, int c);
int				history_previous(t_terminal *terminal, int c);
int				history_next(t_terminal *terminal, int c);
int				terminal_insert(t_terminal *terminal, int c);
int				terminal_eof(t_terminal *terminal, int c);
int				auto_complete(t_terminal *terminal, int c);
int				terminal_insert_string(t_terminal *terminal, char *str);
void			quit(t_terminal *terminal);
int				is_middle_of_unicode(unsigned char c);
int				cursor_is_middle_of_unicode(t_terminal *terminal);
int				get_letter_index(t_terminal *terminal);

#endif
