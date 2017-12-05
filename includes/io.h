/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 10:31:11 by claudioca         #+#    #+#             */
/*   Updated: 2017/12/05 21:28:35 by claudioca        ###   ########.fr       */
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
	MOVE = 0,
	MOVE_DOWN = 1,
	MOVE_LEFT = 2,
	MOVE_RIGHT = 3,
	MOVE_EOL = 4,
	DELETE = 5,
	DELETE_EOL = 6,
	NEW_LINE = 7
}				t_terminal_command;

typedef struct	s_terminal
{
	t_string		*line;
	t_ring_buffer	*history;
	int				cursor;
	int				tty;
	char			*prompt;
	int				prompt_size;
	struct termios	original;
	struct termios	custom;
}				t_terminal;

int				init_command_table(void);
int				handle_input(t_terminal *terminal, char c);
int				setup_terminal(t_terminal *terminal, char const *prompt);
void			set_termios(struct termios *termios);
char const		*get_terminal_command(t_terminal_command command);
void			terminal_BOL(t_terminal *terminal);
void			terminal_command(t_terminal_command command);
void			terminal_command_params(t_terminal_command command,
													int line, int col);

#endif
