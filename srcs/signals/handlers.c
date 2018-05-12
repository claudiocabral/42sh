/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 18:55:17 by claudioca         #+#    #+#             */
/*   Updated: 2018/01/12 14:04:28 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal_handlers.h>
#include <stdlib.h>
#include <io.h>

void		interrupt_handler(int sig)
{
	//static int	last_signal = 0;
	//int			tmp;

	(void)sig;
	//if (sig)
	//	last_signal = sig;
	//else
	//{
	//	//tmp = last_signal;
	//	last_signal = 0;
	//	//return (tmp);
	//}
	//return (last_signal);
}
