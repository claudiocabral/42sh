/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_print.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 14:20:51 by ccabral           #+#    #+#             */
/*   Updated: 2018/03/19 14:30:34 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <io.h>
#include <environment.h>
#include <ft_printf.h>

int	print_prompt(t_terminal *terminal)
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

int	terminal_draw(t_terminal *terminal, int c)
{
	(void)
	terminal_begining(terminal, 0);
	print_prompt(terminal);
	terminal_write(terminal, c);
	terminal->cursor = terminal->line->size;
	return (1);
}
