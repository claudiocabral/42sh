/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactive_session.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 15:39:05 by claudioca         #+#    #+#             */
/*   Updated: 2017/12/01 19:21:41 by claudioca        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <libft.h>
#include <ft_printf.h>
#include <shellma.h>
#include <signal_handlers.h>
#include <io.h>

void		get_next_line(char **input, int buff_size)
{
	int	i;

	i = 0;
	while (read(0, *input + i, 1))
	{
		if (i >= buff_size - 2)
			buff_size = ft_realloc((void **)input, buff_size, buff_size * 2);
		write(1, *input + i, 1);
		if ((*input)[i++] == '\n')
			break ;
	}
	input[i] = 0;
}

static char	*prompt(void)
{
	char	*input;

	if (!(input = (char *)malloc(sizeof(char) * 2048)))
		interrupt_handler(0);
	ft_putstr("$> ");
	get_next_line(&input, 2048);
	return (input);
}

void		interactive_session(void)
{
	t_termios	termios;

	setup_terminal(&termios);
	while (1)
		execute(parse(lex(prompt())));
}
