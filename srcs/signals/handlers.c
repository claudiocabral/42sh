/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 18:55:17 by claudioca         #+#    #+#             */
/*   Updated: 2017/12/01 19:00:55 by claudioca        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal_handlers.h>
#include <stdlib.h>
#include <io.h>

void	interrupt_handler(int sig)
{
	(void)sig;
	restore_terminal(get_termios());
	exit(0);
}
