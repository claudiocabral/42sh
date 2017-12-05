/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_commands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/03 16:16:01 by claudioca         #+#    #+#             */
/*   Updated: 2017/12/05 13:23:00 by claudioca        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <io.h>
#include <term.h>

static char	const	*g_command_table[COMMAND_TABLE_SIZE];

static int			ft_putchar_stdin(int c)
{
	write(0, &c, 1);
	return (c);
}

int					check_table(void)
{
	int	i;

	i = 0;
	while (i < COMMAND_TABLE_SIZE)
		if (g_command_table[i] == 0)
			return (0);
	return (1);
}

int					init_command_table(void)
{
	g_command_table[MOVE] = tgetstr("cm", 0);
	g_command_table[MOVE_LEFT] = tgetstr("LE", 0);
	g_command_table[MOVE_RIGHT] = tgetstr("RI", 0);
	g_command_table[MOVE_EOL] = tgetstr("nd", 0);
	g_command_table[DELETE] = tgetstr("dc", 0);
	g_command_table[DELETE_EOL] = tgetstr("kE", 0);
	g_command_table[NEW_LINE] = tgetstr("nw", 0);
	return (1);
	//return (check_table());
}

__attribute__((always_inline))
void		terminal_command_params(t_terminal_command command,
												int line, int col)
{
	tputs(tgoto(g_command_table[command], line, col), 1, &ft_putchar_stdin);
}

__attribute__((always_inline))
void		terminal_command(t_terminal_command command)
{
	tputs(g_command_table[command], 0, &ft_putchar_stdin);
}
