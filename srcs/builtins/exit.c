/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 13:02:39 by ccabral           #+#    #+#             */
/*   Updated: 2018/01/15 13:07:33 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <builtins.h>
#include <term.h>
#include <io.h>

int	builtin_exit(int argc, char **argv)
{
	t_terminal	*terminal;

	(void)argc;
	(void)argv;
	if ((terminal = default_terminal(0)))
	{
		termios_toggle_isig(terminal, 1);
		set_termios(&(terminal->original));
	}
	exit(0);
}
