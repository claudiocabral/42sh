/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strtok_glob.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfloure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 19:03:32 by gfloure           #+#    #+#             */
/*   Updated: 2018/06/08 19:10:02 by gfloure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <globbing.h>
#include <ft_printf.h>

static char		*split_delimiters(char *str, char *delim)
{
	int			m;
	int			i;
	char		s;
	char		d;

	s = (str != NULL) ? *str : 0;
	while (s)
	{
		m = 0;
		i = 0;
		while ((d = delim[i++]) != '\0')
			if (s == d)
				m = 1;
		if (m == 0)
			return (str);
		s = *++str;
	}
	return (NULL);
}

char			*strtok_glob(char *str, const char *delim, char *end)
{
	static char	*s;
	char		*ps;
	char		*ret;
	int			i;

	s = (str) ? str : s;
	if (!s || *s == '\0' || (s = split_delimiters(s, (char*)delim)) == NULL)
		return (NULL);
	ps = s;
	while (*ps)
	{
		i = 0;
		while (delim[i])
			if (*ps == delim[i++])
			{
				end[0] = *ps;
				end[1] = 0;
				*ps = '\0';
				ret = s;
				s = split_delimiters(ps + 1, (char*)delim);
				return (ret);
			}
		++ps;
	}
	ret = s;
	s = ps;
	return (ret);
}
