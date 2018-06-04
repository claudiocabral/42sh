/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouill <iomonad@riseup.net>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/03 18:56:41 by ctrouill          #+#    #+#             */
/*   Updated: 2018/06/04 02:51:34 by gfloure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOADER_H
# define LOADER_H

# include <mysh.h>

# define SH_RC "~/.42shrc"

char	*rc_loadable(const char *rc);
void	load_n_eval(const char *rc);

#endif
