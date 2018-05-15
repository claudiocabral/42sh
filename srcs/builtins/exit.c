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
#include <mysh.h>

int	builtin_exit(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	reset_sh(g_sh);
	if (g_sh->history.fd_history != -1)
		close(g_sh->history.fd_history);
	exit(0);
}
