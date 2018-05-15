/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fallback.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 10:07:25 by ctrouill          #+#    #+#             */
/*   Updated: 2018/03/14 11:07:21 by ctrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mysh.h>

/*
** When callback is not defined for different
** and exotic signals, just call this function
** not avoid call ignore.
*/

void	fallback_callback(void)
{
	return ;
}
