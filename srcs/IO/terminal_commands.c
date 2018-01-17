/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_commands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/03 16:16:01 by claudioca         #+#    #+#             */
/*   Updated: 2018/01/17 13:28:40 by ccabral          ###   ########.fr       */
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
	g_command_table[HOME] = tgetstr("kh", 0);
	g_command_table[END] = "\e\x6";
	g_command_table[INSERT] = tgetstr("IC", 0);
	g_command_table[MOVE_DOWN] = tgetstr("DO", 0);
	g_command_table[MOVE_UP] = tgetstr("UP", 0);
	g_command_table[MOVE_LEFT] = tgetstr("LE", 0);
	g_command_table[MOVE_RIGHT] = tgetstr("RI", 0);
	g_command_table[DELETE] = tgetstr("DC", 0);
	g_command_table[DELETE_KEY] = tgetstr("kD", 0);
	if (g_command_table[DELETE_KEY])
		g_command_table[DELETE_KEY][1] = 91;
	g_command_table[ARROW_UP] = tgetstr("ku", 0);
	g_command_table[ARROW_DOWN] = tgetstr("kd", 0);
	g_command_table[ARROW_LEFT] = tgetstr("kl", 0);
	g_command_table[ARROW_RIGHT] = tgetstr("kr", 0);
	if (g_command_table[ARROW_UP])
		g_command_table[ARROW_UP][1] = 91;
	if (g_command_table[ARROW_DOWN])
		g_command_table[ARROW_DOWN][1] = 91;
	if (g_command_table[ARROW_LEFT])
		g_command_table[ARROW_LEFT][1] = 91;
	if (g_command_table[ARROW_RIGHT])
		g_command_table[ARROW_RIGHT][1] = 91;
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
