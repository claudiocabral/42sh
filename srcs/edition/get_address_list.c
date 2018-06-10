/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 11:26:42 by jblazy            #+#    #+#             */
/*   Updated: 2018/03/15 11:27:02 by jblazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mysh.h>

t_prompt	**get_address_list(t_prompt **list, char address)
{
	static t_prompt	**ref;

	if (address)
		ref = list;
	if (address == 2)
		ref = NULL;
	return (ref);
}
