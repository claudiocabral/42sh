/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 18:56:24 by claudioca         #+#    #+#             */
/*   Updated: 2017/12/04 12:44:33 by claudioca        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_HANDLERS_H
# define SIGNAL_HANDLERS_H
# include <signal.h>

/*
** Core callbacks
*/

void	signal_init(void);
void	proc_signal_callback(int sig);

/*
** Regular callbacks
*/

void	sigint_callback(void);
void	sigquit_callback(void);
void	fallback_callback(void);
void	sigpipe_callback(void);

#endif
