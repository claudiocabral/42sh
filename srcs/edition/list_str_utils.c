/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_str_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 13:38:38 by jblazy            #+#    #+#             */
/*   Updated: 2018/03/07 13:38:39 by jblazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mysh.h>

/*
**	@return the prompt length of list.
*/

unsigned int		prompt_len(t_prompt *list)
{
	if (list->prompt_type == STANDARD)
		return (list->prompt_len);
	else if (list->prompt_type == MULTI_LINE)
		return (2);
	else if (list->prompt_type == QUOTE)
		return (7);
	else if (list->prompt_type == DQUOTE || list->prompt_type == BQUOTE)
		return (8);
	else if (list->prompt_type == HEREDOC)
		return (9);
	return (0);
}

/*
**	@return the length of list.
*/

unsigned int		list_len(t_prompt *list)
{
	unsigned int	i;
	t_prompt		*tmp;

	i = 0;
	tmp = list;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

/*
**	@return how many there is '\n' in list.
*/

unsigned int		list_nb_return(t_prompt *list)
{
	unsigned int nb;

	nb = 0;
	while (list)
	{
		if (list && list->c == RETURN)
			nb++;
		list = list->next;
	}
	return (nb);
}
