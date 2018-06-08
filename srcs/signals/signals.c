/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 08:36:48 by ctrouill          #+#    #+#             */
/*   Updated: 2018/04/19 15:48:39 by ctrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <mysh.h>

/*
** Signal balancer for several
** catchs
** @return @nil
*/

static void	signal_callback(int sig)
{
	if (sig == SIGINT)
		sigint_callback();
	else if (sig == SIGQUIT)
		sigquit_callback();
	//else if (sig == SIGPIPE)
	//	sigpipe_callback();
	else
		fallback_callback();
	signal_init();
}

/*
** Centralized signal handler
** @params sig:code sh:shell
** @return nil
*/

void		signal_init(void)
{
	signal(SIGINT, signal_callback);
	signal(SIGTSTP, signal_callback);
	signal(SIGQUIT, signal_callback);
	signal(SIGILL, signal_callback);
	signal(SIGTRAP, signal_callback);
	signal(SIGABRT, signal_callback);
	signal(SIGTERM, signal_callback);
}
