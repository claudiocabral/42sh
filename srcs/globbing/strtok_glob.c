/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strtok_glob.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfloure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 19:03:32 by gfloure           #+#    #+#             */
/*   Updated: 2018/06/11 00:09:18 by gfloure          ###   ########.fr       */
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
				return (str);
		if (m == 0)
			return (str);
		s = *++str;
	}
	return (NULL);
}

static void		love_spaghetty_code_mate(char **end, char c, char *ps)
{
	(*end)[0] = c;
	(*end)[1] = 0;
	*ps = '\0';
}

char			*strtok_glob(char *str, const char *delim, char *end, int i)
{
	static char	*s;
	char		*ps;
	char		*ret;

	s = (str) ? str : s;
	if (!s || *s == '\0' || (s = split_delimiters(s, (char*)delim)) == NULL)
		return (NULL);
	ps = s;
	while (*ps != '\0')
	{
		i = 0;
		while (delim[i])
			if (*ps == delim[i++])
			{
				love_spaghetty_code_mate(&end, *ps, ps);
				ret = s;
				s = split_delimiters(ps + 1, (char*)delim);
				return (ret);
			}
		++ps;
	}
	ret = s;
	s = ps;
	end[0] = 0;
	return (ret);
}
