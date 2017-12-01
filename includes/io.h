/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 10:31:11 by claudioca         #+#    #+#             */
/*   Updated: 2017/12/01 19:00:46 by claudioca        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IO_H
# define IO_H

# include <termios.h>

typedef struct	s_termios
{
	struct termios	original;
	struct termios	custom;
}				t_termios;

void		setup_terminal(t_termios *termios);
void		restore_terminal(t_termios *termios);
t_termios	*get_termios(void);

#endif
