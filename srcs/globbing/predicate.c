/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   predicate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 12:53:07 by ctrouill          #+#    #+#             */
/*   Updated: 2018/06/13 01:59:44 by gfloure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <globbing.h>
#include <lexer.h>
#include <ft_printf.h>

void	sorry_ctrouill(const char *needle, size_t i, int *backup)
{
	*backup == 0 ? get_quote(needle[i]) : 0;
	*backup == needle[i] ? get_quote(0) : 0;
	*backup = get_quote(-42);
}

/*
** Trivial predicate to determine
** if the current token need to
** be deglobed the concat to original
** string
*/

t_bool	needs_globbing(const char *needle, size_t i)
{
	size_t	y;
	int		backup;

	if (ft_strcmp(needle, "$?") == 0)
		return (FALSE);
	y = ft_strchri(needle, '=');
	backup = get_quote(-42);
	while (i <= ft_strlen(needle) && needle[i] && (needle[i] != '\0'))
	{
		if (needle[i] == '\\')
			i++;
		else
		{
			if (needle[i] == '\'' || needle[i] == '"' || needle[i] == '`')
				sorry_ctrouill(needle, i, &backup);
			if ((needle[i]) && (needle[i] == 0x2a || needle[i] == 0x5b ||
				needle[i] == 0x7b || needle[i] == 0x3f) &&
				(y && i < y) && get_quote(-42) == 0)
				return (TRUE);
		}
		i++;
	}
	return (FALSE);
}
