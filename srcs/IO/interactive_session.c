/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactive_session.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 15:39:05 by claudioca         #+#    #+#             */
/*   Updated: 2018/03/18 13:16:37 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <libft.h>
#include <ft_printf.h>
#include <shellma.h>
#include <signal_handlers.h>
#include <signal.h>
#include <term.h>
#include <environment.h>
#include <io.h>

void				quit(t_terminal *terminal)
{
	termios_toggle_isig(terminal, 1);
	write(STDIN_FILENO, "\n", 1);
	free_terminal(terminal);
	exit(0);
}

int					print_prompt(t_terminal *terminal)
{
	char const	*path;

	path = ft_getenv("PWD");
	if (ft_strcmp(path, "/"))
	{
		path = path ? ft_strrchr(path, '/') : 0;
		path = path ? path + 1 : 0;
	}
	if (terminal->prompt_pointer == terminal->prompt)
	{
		terminal->prompt_size = ft_dprintf(2, "%s%c%s", path ? path : "",
															path ? ' ' : 0,
															terminal->prompt);
	}
	else
		terminal->prompt_size = ft_dprintf(2, "%s", terminal->prompt_pointer);
	return (terminal->prompt_size);
}

void			set_termios(struct termios *termios)
{
	tcsetattr(STDIN_FILENO, TCSANOW, termios);
}

int	terminal_draw(t_terminal * terminal, int c)
{
	(void)
	terminal_begining(terminal, 0);
	print_prompt(terminal);
	terminal_write(terminal, c);
	terminal->cursor = terminal->line->size;
	return (1);
}

static char	const	*prompt(t_terminal *terminal)
{
	int		size;
	char	c[16];

	termios_toggle_isig(terminal, 0);
	set_termios(&(terminal->custom));
	history_load(terminal);
	print_prompt(terminal);
	while ((size = read(STDIN_FILENO, c, 16)))
	{
		if (size == -1)
		{
			ft_dprintf(2, "Unknown input error\n");
			quit(terminal);
		}
		c[size] = 0;
		if (handle_input(terminal, c, size) == 0)
			break ;
		string_copy(terminal->history->current, terminal->line);
	}
	history_append(terminal);
	string_clear(terminal->line);
	terminal_command(CLEAR_BOTTOM, 0);
	termios_toggle_isig(terminal, 1);
	set_termios(&(terminal->original));
	terminal->cursor = 0;
	terminal->line_number = 0;
	return (((t_string *)terminal->history->current)->buffer);
}

void				interactive_session(void)
{
	t_terminal	terminal;

	if (!setup_terminal(&terminal, "$> "))
		exit(1);
	while (1)
		process_input(prompt(&terminal));
}
