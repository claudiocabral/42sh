/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_globbing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 11:17:25 by jblazy            #+#    #+#             */
/*   Updated: 2018/06/13 11:17:28 by jblazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <globbing.h>

/*
** Check dominative context to proof
** execution loop.
** @return boolean
*/

t_bool	is_dominative(char cursor)
{
	return (cursor != '[' &&
			cursor != ']' &&
			cursor != '?');
}

/*
** Verify if
** @return boolean
*/

t_bool	is_dirwalk_needed(char cursor)
{
	return (cursor == '/');
}

/*
** Check dominative context to proof
** execution loop.
** @return boolean
*/

t_bool	have_valid_context(int err,
						char cursor)
{
	return (err == -1
		&& cursor != ',');
}

/*
** Check dominative context to proof
** execution loop.
** @return boolean
*/

t_bool	brackets_valid_fmt(char c)
{
	return (c != '\0' &&
			c != ',' &&
			c != '}');
}
