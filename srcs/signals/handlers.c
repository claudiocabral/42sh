/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 18:55:17 by claudioca         #+#    #+#             */
/*   Updated: 2017/12/18 14:04:33 by claudioca        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal_handlers.h>
#include <stdlib.h>
#include <io.h>

int		interrupt_handler(int sig)
{
	static int	last_signal = 0;
	if (sig)
		last_signal = sig;
	return (last_signal);
}
