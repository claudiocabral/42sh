/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 14:23:23 by ctrouill          #+#    #+#             */
/*   Updated: 2018/04/18 08:55:05 by ctrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SETUP_H
# define SETUP_H

# include <mysh.h>
# include <locale.h>

typedef struct			s_sh
{
	struct termios		new_term;
	char				*copy_str;
	t_histo				history;
	char				*heredoc_delim;
	t_infocompl			*completion;
}						t_sh;

t_sh					*g_sh;

void					exit_shell(t_sh *sh);
void					set_sh(t_sh *sh);
void					init_sh(t_sh *sh);

#endif
