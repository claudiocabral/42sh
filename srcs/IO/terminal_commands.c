/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_commands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/03 16:16:01 by claudioca         #+#    #+#             */
/*   Updated: 2018/03/21 18:50:23 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <term.h>
#include <io.h>
#include <ft_printf.h>

static char		*g_command_table[COMMAND_TABLE_SIZE];

static int		ft_putchar_stdin(int c)
{
	write(0, &c, 1);
	return (c);
}

int				check_table(void)
{
	int	i;

	i = 0;
	return (1);
}

int				init_command_table(void)
{
	g_command_table[CLEAR_BOTTOM] = tgetstr("cd", 0);
	g_command_table[HOME] = "\e[H";
	g_command_table[END] = "\e[F";
	g_command_table[INSERT] = tgetstr("IC", 0);
	g_command_table[MOVE_DOWN] = tgetstr("DO", 0);
	g_command_table[MOVE_UP] = tgetstr("UP", 0);
	g_command_table[MOVE_LEFT] = tgetstr("LE", 0);
	g_command_table[MOVE_RIGHT] = tgetstr("RI", 0);
	g_command_table[DELETE] = tgetstr("DC", 0);
	g_command_table[DELETE_KEY] = "\e[3~";
	g_command_table[ARROW_UP] = "\e[A";
	g_command_table[ARROW_DOWN] = "\e[B";
	g_command_table[ARROW_RIGHT] = "\e[C";
	g_command_table[ARROW_LEFT] = "\e[D";
	g_command_table[CTRL_ARROW_UP] = "\e[1;5A";
	g_command_table[CTRL_ARROW_DOWN] = "\e[1;5B";
	g_command_table[CTRL_ARROW_RIGHT] = "\e[1;5C";
	g_command_table[CTRL_ARROW_LEFT] = "\e[1;5D";
	g_command_table[HIDE_CURSOR] = tgetstr("vi", 0);
	g_command_table[SHOW_CURSOR] = tgetstr("ve", 0);
	g_command_table[STANDOUT] = tgetstr("so", 0);
	g_command_table[NO_STANDOUT] = tgetstr("se", 0);
	return (check_table());
}

int				terminal_compare_string(t_terminal_command command,
		char const *str)
{
	return (ft_strequ(g_command_table[command], str));
}

void			terminal_command(t_terminal_command command, int val)
{
	tputs(tgoto(g_command_table[command], 0, val), 1, &ft_putchar_stdin);
}
